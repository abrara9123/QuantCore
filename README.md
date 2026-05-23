# QuantCore

A high-performance thread pool implementation in C++17, built as a foundation for fintech systems such as order processing engines and risk calculators.

## Status

Work in progress. The core `TaskQueue` is complete. The `ThreadPool` is partially implemented — this project is being paused while I deepen my C++ concurrency fundamentals before returning to finish it properly.

## What's Built

### `TaskQueue.h`
A thread-safe task queue built with:
- `std::mutex` + `std::lock_guard` for data race protection
- `std::condition_variable` for efficient thread sleeping and waking
- `std::function<void()>` to store any callable task

Methods:
- `push(task)` — adds a task and notifies a waiting worker
- `pop(task)` — non-blocking pop, returns false if empty
- `waitPop(task)` — blocks until a task is available, then pops it
- `empty()` — checks if the queue has tasks
- `stop()` — signals all waiting threads to wake up and exit

### `ThreadPool.h`
A worker thread pool that:
- Spawns N worker threads on construction
- Each worker runs an infinite loop calling `waitPop` and executing tasks
- Supports task submission via `addTask()`
- Shuts down cleanly via the destructor

## What's Left

- [ ] Graceful shutdown and thread joining
- [ ] `std::future` / `std::promise` support for getting results back from tasks
- [ ] Priority queue support
- [ ] Work stealing for low-latency scheduling
- [ ] Monte Carlo pricing engine built on top of the thread pool

## Concepts Learned

- `std::thread` — spawning and managing OS threads
- `std::mutex` + `std::lock_guard` — preventing data races
- `std::condition_variable` — efficient thread sleeping and waking
- `std::function` + lambdas — storing and passing arbitrary callables
- RAII — automatic resource management via lock guards

## Build

```bash
mkdir build && cd build
cmake ..
make
./QuantCore
```

## Why This Project

Thread pools are core infrastructure in fintech systems — trading platforms, risk engines, and order management systems all rely on efficient concurrent task execution. This project was built to understand those fundamentals from the ground up in C++.

## Tech Stack

- C++17
- CMake
- Standard library concurrency primitives only (no third-party dependencies)
