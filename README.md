    # philosophers

    Dining Philosophers implemented with pthreads and mutexes: spawn philosophers, manage forks, detect starvation, and stop cleanly.

    ## Project Overview
    - What it does: simulates philosophers eating/sleeping/thinking with shared forks, enforcing timing rules and termination on death or meal quota.
    - Use cases: concurrency primitives, deadlock avoidance, timing control.
    - Problem solved: coordinate fork access without deadlocks and detect starvation.

    ## Architecture & Design
    - Data structures (philo.h):
      - `t_philo`: per-philosopher state (id, left/right fork indices, last_meal timestamp, eaten_count, thread, shared config).
      - `t_data`: global config (counts, timings), arrays of forks (mutexes), `print` mutex, `dead` flag, start time.
    - Workflow:
      1) Parse args (philo.c) → validate positive ints and optional must_eat.
      2) Init forks (mutex per fork) and create threads.
      3) Routine (routine.c): stagger start for odd ids, then loop: take forks (ordered by id parity), `print_status`, eat → sleep → think.
      4) Monitor (monitoring.c): loops over philosophers, checks `last_meal` vs `time_to_die`, sets `dead` flag, and stops when death or all met `must_eat`.

    ## Core Concepts (with code)
    - Stagger start to reduce contention:
    ```c
    // routine.c
    if (philo->id % 2 == 0)
        usleep(1500);
    ```
    - Fork acquisition order prevents circular wait:
    ```c
    // routine.c
    pthread_mutex_lock(philo->left);
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(philo->right);
    print_status(philo, "has taken a fork");
    ```
    - Death detection and stop condition:
    ```c
    // monitoring.c
    if (get_time() - philo[i].last_meal > data->time_to_die) {
        print_status(&philo[i], "died");
        data->dead = 1;
    }
    if (data->must_eat != -1 && count_finished == data->nb_philo)
        data->dead = 1;
    ```

    ## Code Walkthrough
    1) `main`: validate args, allocate `t_data`, `t_philo` array, init mutexes, set start time.
    2) Spawn philosopher threads with `routine`: loop while `dead` not set; lock forks, eat (update `last_meal`), sleep, think.
    3) Start monitor thread (`monitoring`): watch `last_meal` and optional meal quotas; sets `dead` flag to stop loops.
    4) Join all threads; destroy mutexes; free memory.

    ## Installation & Setup
    - Depends on pthreads (POSIX). Build with `make` to produce `philo`.
    - Run: `./philo nb_philo time_die time_eat time_sleep [must_eat]` (times in ms).

    ## Usage Guide
    - Example: `./philo 5 800 200 200 5` (5 philosophers, die after 800ms without eating, eat 200ms, sleep 200ms, stop after each eats 5 times).
    - Outputs timestamped logs guarded by `print` mutex to avoid interleaving.

    ## Technical Deep Dive
    - Time utils: `get_time` returns ms since epoch; `ft_usleep` busy-waits in short slices for more precise timing than plain `usleep`.
    - Shared flags: `dead` read under `print`/fork mutex protection to keep memory visibility simple; logs stop after death flag.
    - Edge cases: 1 philosopher grabs one fork and dies after `time_to_die`; even/odd fork order avoids deadlock for n>1.

    ## Improvements & Future Work
    - Add condition variables to avoid busy-waiting in `ft_usleep`.
    - Add CLI validation feedback for overflow/invalid numbers.
    - Provide per-philosopher timing stats on exit.

    ## Author
    Oualid Obbad (@oualidobbad)