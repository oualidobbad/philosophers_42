    # philosophers_42

    Dining philosophers implemented with pthreads, focusing on deadlock avoidance and starvation detection.

    ## Architecture
    - Threads: one per philosopher plus a monitor (or time checks inside loop) watching `last_meal` timestamps.
    - Sync: one mutex per fork; optional print mutex to serialize output.
    - Strategy: ordered fork pickup (e.g., even takes right then left, odd takes left then right) to avoid circular wait.

    ## Build & Run
    - `make` → builds `philo`.
    - Usage: `./philo 5 800 200 200 [must_eat]` (args: count, time_to_die, time_to_eat, time_to_sleep, optional meals target).

    ## Technical Notes
    - Timing: typically uses `gettimeofday`-based ms timestamps; avoid busy waits by short sleeps while checking elapsed time.
    - Termination: stop when any philosopher dies or when all reach `must_eat` count.
    - Output must remain ordered and free of interleaved lines; protect with a dedicated mutex.

    ## Testing Ideas
    - Minimal counts (1, 2 philosophers) to ensure edge logic works; large counts to stress timing.
    - Use small time_to_die to force deaths and verify monitor behavior.

    ## Author
    Oualid Obbad (@oualidobbad)