# 🧑‍🎓 Philosophers Project - 42

<p align="center">
  <img src="https://github.com/leogaudin/42_project_badges/raw/main/badges/push_swap_bonus.webp" />
</p>

Welcome to Philosophers, a project at 42 that explores multithreading and synchronization. In this project, you'll implement a simulation of philosophers sitting at a table, thinking, eating, and sleeping while ensuring no philosopher starves. This project focuses on thread management and mutual exclusion using mutexes (for the mandatory part) and semaphores (for the bonus part).

---

## 📋 Project Overview

| **Category**            | **Functions**                                                                                           |
|-------------------------|--------------------------------------------------------------------------------------------------------|
| **Mandatory Program**    | `philo` - Implement the philosopher simulation with threads and mutexes.                                |
| **Bonus Program**        | `philo_bonus` - Implement the philosopher simulation with processes and semaphores. |
| **Utility Functions**    | `malloc`, `free`, `usleep`, `gettimeofday`, `pthread_create`, `pthread_join` ...                       |

---

## 🚀 Key Features

1. **Philosopher Simulation**:
   - Philosophers take turns thinking, eating, and sleeping.
   - Each philosopher needs two forks to eat: one to their left and one to their right.
   
2. **Thread Management (Mandatory)**:
   - The philosophers are represented as threads.
   - Forks are shared between philosophers, and mutexes are used to prevent data races when accessing forks.

3. **Process Management (Bonus)**:
   - Philosophers are implemented as processes instead of threads.
   - Forks are managed using semaphores to synchronize access.

4. **Avoid Starvation**:
   - Philosophers should never starve, and a philosopher dies if they don't eat within a specified time.
    
5. **Real-Time Logging**:
   - The state changes of philosophers (e.g., taking a fork, eating, sleeping, dying) are logged with timestamps.


---

## 🗂️ File Structure

| **File**                | **Description**                                                                                        |
|-------------------------|--------------------------------------------------------------------------------------------------------|
| `Makefile`              | Automates the compilation process. Run `make` to generate the `philo` or `philo_bonus` executable.     |
| `philo.h`               | Header file with function prototypes and necessary includes for the mandatory part.                    |
| `philo_bonus.h`         | Header file with function prototypes and necessary includes for the bonus part.                        |
| `philo.c`               | Main program for the mandatory part (thread-based simulation).                                         |
| `philo_bonus.c`         | Main program for the bonus part (process-based simulation).                                            |
| `utils.c`               | Utility functions like memory management, logging, etc.                                                |

---

## 🔧 Compilation Instructions

Use the **Makefile** to compile the project.

- **Compile the project(mandatory):**
  ```bash
  make
  ```
- **Compile the project(bonus):**
  ```bash
  make bonus
  ```
- **Clean the project (remove object files):**
  ```bash
  make clean
  ```
- **Full cleanup (remove all generated files):**
  ```bash
  make fclean
  ```
- **Recompile after cleaning:**
  ```bash
  make re
  ```
  ---

## 💻 Usage

Once compiled, you can use the `philo` and `philo_bonus` programs as follows:

## Running the Mandatory Program:

To start the philosopher simulation with threads:
```bash
./philo 5 800 200 200
```
- `5` is the number of philosophers.
- `800` is the time to die (in milliseconds).
- `200` is the time to eat (in milliseconds).
- `200` is the time to sleep (in milliseconds).
  
## Running the Bonus Program:

```bash
./philo_bonus 5 800 200 200
```

## 🧪 Testing

You can test the functionality of both the mandatory and bonus programs by using various input cases.

For example:
```bash
./philo 5 800 200 200
./philo_bonus 5 800 200 200
```
Sample output: For philosopher number 1, the output might look like:
```bash
timestamp_in_ms 1 has taken a fork
timestamp_in_ms 1 is eating
timestamp_in_ms 1 is sleeping
```
---

## 🤝 Contributing

If you'd like to contribute to this project, feel free to fork the repository, make your changes, and submit a pull request!
