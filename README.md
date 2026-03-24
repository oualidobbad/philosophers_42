# philosophers_42

## Description
Dining philosophers concurrency exercise using pthreads.

## Features
- Mutex-protected forks; timing/starvation checks.
- Configurable philosopher counts and timings.

## Technologies Used
- C, pthreads, Makefile.

## Installation
- Run `make` to build `philo`.

## Usage
- `./philo 5 800 200 200 [must_eat]` to simulate.

## Example
- `./philo 4 410 200 200` runs four philosophers.

## Technical Notes
- pthreads + mutex per fork; to avoid deadlock, odd philosophers pick right then left (or ordered pickup strategy).
- Timing uses gettimeofday; monitor thread checks starvation by comparing last_meal vs time_to_die.
- Respect 42 rules: no busy waits, protect shared writes (stdout) with a print mutex.

## Author
- Oualid Obbad (@oualidobbad)