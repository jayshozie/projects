# 🚀 Jayshozie's Systems Programming Portfolio

This repository serves as a central collection and version control manager
(using Git submodules) for my low-level systems programming curriculum.

### Why submodules?

Each project (e.g., [yacc](./c-mastery-projects/yet-another-cat-clone)) is a
completely separate repository, allowing for independent versioning, branching
and clear history tracking.

---

## 🏗️ Project Containers

| Icon | Module Name | Description | Key Focus |
| :---: | :--- | :--- | :--- |
| **🧠** | [**C-Systems-Fundamentals**](./c-mastery-projects) | Core C projects focusing on manual memory management, pointer arithmetic, and concurrency primitives (Mutexes, Queues). | C Mastery & Concurrency |
| **🌐** | [**Networking**](./networking) | Low-level networking projects built with POSIX sockets, demonstrating different I/O and server architectures. | I/O Multiplexing & Sockets |

---

## 💻 Projects by Container

### 🧠 C-Systems-Fundamentals

* **[`yacc` (Yet Another Cat Clone)](./c-mastery-projects/yacc):** A
re-implementation of the GNU Coreutils utility `cat` to master the **Standard
I/O** and **Syscall** interfaces (`read`/`write`) and I/O buffering techniques.
Version v2.0 implements `cat` with `stdio`, with version v3.0 I implemented the
entire project using `syscalls`.
(Current Version: v3.0)

* **[`jayshell`](./c-mastery-projects/jayshell):** A shell interpreter written
in C as a study project. It uses `readline` for its initial shell loop, it can
do basic command parsing with `strtok()`, it has support for external commands
using `fork()` and `execvp()`, and lastly it has 2 basic built-in commands,
`exit` and `cd` (without `~` support, yet).
(Current Version: v1.0)

### 🌐 Networking

* **[`Iterative-Blocking-TCP-Example`](./networking/iterative-blocking-tcp-example):**
A simple server/client system demonstrating the **blocking I/O model**—where the
server processes a single client at a time. At this point the server
automatically shuts down after the connected client disconnects, but the server
waiting again for another connection can be easily implemented in v2.0.
(Current Version: v1.0)
* **[`IOMUX-Chat-System-in-C`](./networking/iomux-chat-system-in-c):** A
multi-client chat server using **I/O Multiplexing (`select` / `poll`)** to
synchronously manage multiple connections within a single process. I'm still
working on it, a stable version release doesn't exist yet.
(Current Version: N/A)
* **[`Socket Programming Utilities`](./networking/socket-programming):** A
directory of small tests I've done with the subject. It doesn't include any
necessary stuff, I just used this to understand the socket interface in C.

---

## 📖 Curriculum and Resources

These projects are guided by the goal of kernel development and are supported by
the following resources:

* **System Calls:** *Advanced Programming in the UNIX Environment* (APUE) / *The
Linux Programming Interface* (TLPI)
* **Architecture:** *Computer Systems: A Programmer's Perspective* (CS:APP)
* **Networking Theory:** *Computer Networking: a Top-Down Approach* (K&R)

## 🤝 Contribution

Contributions and feedback are always welcome. Please feel free to open an Issue
or PR in the respective submodule's repository.
