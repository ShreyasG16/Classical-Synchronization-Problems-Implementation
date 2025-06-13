# Classical Synchronization Problems in C++

This project demonstrates the implementation of three classical synchronization problems using C++11 threading primitives. It showcases low-level concurrency control mechanisms by implementing custom semaphore using C++ mutex and condition_variable.

## 🧵 Implemented Problems

### 1. Producer-Consumer
- Simulates a bounded buffer with two producers and two consumers.
- Synchronization achieved using a **custom counting semaphore** built with `mutex` and `condition_variable`.
- Prevents race conditions and ensures safe access to a shared queue using a binary `mutex`.

### 2. Reader-Writer
- Models the first-reader preference strategy.
- Synchronization logic uses two `mutex` objects to protect shared counters and writer access.
- Ensures that multiple readers can read concurrently, while writers get exclusive access.

### 3. Dining Philosophers
- Simulates five philosophers trying to eat without causing deadlock.
- Uses one `mutex` per fork and a global `table_lock` to ensure deadlock prevention.
- Each philosopher runs in a infinite loop to simulate **continuous contention**, which:
  - Tests robustness of deadlock prevention
  - Validates fairness across all philosophers
  - Demonstrates system behavior under high concurrency pressure


## 💻 Tools & Technologies

- **Language:** C++11
- **Threading Primitives:** `thread`, `mutex`, `condition_variable`
- **Platform:** Linux (Tested on Ubuntu 22.04)

## 📁 File Structure

```
.
├── pcProblemSol.cpp        # Producer-Consumer Problem
├── rwProblemSol.cpp        # Reader-Writer Problem
├── dinningPhilosopher.cpp  # Dining Philosophers Problem
├── .gitignore
└── README.md
```

## 🚀 How to Compile & Run

```bash
# Compile
g++ pcProblemSol.cpp -o pcProblemSol
g++ rwProblemSol.cpp -o rwProblemSol
g++ dinningPhilosopher.cpp -o diningPhilosopher

# Run
./pcProblemSol
./rwProblemSol
./diningPhilosopher
```

## 🧠 Relevance to Embedded & Systems Programming

- Manually implemented synchronization mechanisms.
- Resource sharing control under concurrent environments.
- Careful design to avoid deadlock and starvation.
- Lightweight thread management suitable for constrained systems.

