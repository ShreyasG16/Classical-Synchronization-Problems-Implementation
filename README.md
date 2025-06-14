# Classical Synchronization Problems in C++

This project demonstrates the implementation of three classical synchronization problems using C++11 threads , `mutex` and `condition_variable`.

## 🧵 Implemented Problems

### 1. Producer-Consumer
- Simulates a bounded buffer with **multiple producers and consumers**.
- Synchronization achieved using a **custom counting semaphore** built with `mutex` and `condition_variable`, rather than relying on POSIX semaphores.
- Prevents race conditions and ensures safe access to a shared queue.
- Highlights how condition variables eliminate unnecessary busy-waiting by safely unlocking and relocking during wait.

### 2. Reader-Writer
- Models the **first-reader preference** strategy using `mutex` for shared counters and writer control.
- A second version is also added to **prevent writer starvation**, offering better fairness and more realism than standard textbook examples.

### 3. Dining Philosophers
- Simulates five philosophers eating and thinking in a loop.
- Textbook versions risk **deadlock**; this solution uses a global `table_lock` along with individual fork `mutex`es to ensure no two adjacent philosophers block each other.
- Simple yet effective strategy to maintain **deadlock freedom** with minimal locking overhead.

## 💻 Tools & Technologies

- **Language:** C++11
- **Threading Primitives:** `thread`, `mutex`, `condition_variable`
- **Platform:** Linux (Tested on Ubuntu 22.04)

## 📁 File Structure

```
.
├── pcProblemSol.cpp        # Producer-Consumer Problem
├── rwProblemSol.cpp        # Reader-Writer Problem (Reader Preference)
├── rwProblemSolFinal.cpp   # Reader-Writer Problem (Fairness with Writer Starvation Prevention) (with starvation fix)
├── dinningPhilosopher.cpp  # Dining Philosophers Problem
├── .gitignore
└── README.md
```

## 🚀 How to Compile & Run

```bash
# Compile
g++ pcProblemSol.cpp -o pcProblemSol 
g++ rwProblemSol.cpp -o rwProblemSol
g++ rwProblemSolFinal.cpp -o rwProblemSolFinal
g++ dinningPhilosopher.cpp -o diningPhilosopher

# Run
./pcProblemSol
./rwProblemSol
./rwProblemSolFinal
./diningPhilosopher
```

## 🧠 Relevance to Embedded & Systems Programming

- Manually implemented synchronization mechanisms.
- Resource sharing management under concurrent environments.
- Careful design to avoid deadlock and starvation.
- Simulates real-world contention to test system robustness.
- Lightweight thread management suitable for constrained systems.
