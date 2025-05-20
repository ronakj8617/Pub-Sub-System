# 🛰️ Pub-Sub Server in Modern C++

A lightweight, multithreaded Publish–Subscribe (Pub-Sub) server built in modern C++ using [Crow](https://github.com/CrowCpp/crow), [Boost.Asio](https://www.boost.org/doc/libs/1_82_0/doc/html/boost_asio.html), and CMake.

> Think of this as a minimal in-memory message broker to understand the internals of Pub-Sub systems like Kafka, but built with C++ and web-ready REST endpoints.

---

## 📌 Features

- 🧵 Thread-safe Topic Management
- 🔔 Real-time Message Publishing and Subscribing
- 🌐 RESTful API with Crow (Flask-like C++ web framework)
- ⚡ Boost.Asio-powered async networking
- 🛠️ Clean and modular CMake-based build
- 🔁 GitLab CI/CD ready

---

## 🚀 Getting Started

### 🔧 Prerequisites

- C++17 compatible compiler (e.g., `g++`, `clang++`)
- CMake ≥ 3.14
- Boost libraries: `system`, `thread`
- Git

#### Ubuntu/Debian

```bash
sudo apt update
sudo apt install -y g++ cmake libboost-all-dev

```
---
#### 📥 Clone the Repository
```
git clone https://gitlab.com/ronakj8617/Pub-Sub-System.git
cd Pub-Sub-System
```

### 🛠️ Build Instructions

```bash
# Clean and build
mkdir -p build
cd build
cmake ..
make

# Run the server
./pubsub
```

### 📡 API Endpoints

``` 
| Method | Endpoint        | Description                       |
| ------ | --------------- | ----------------------------------|
| POST   | /ping           | Test the connection               |
| POST   | /subscribe      | Subscribe a client to a topic     |
| POST   | /publish        | Publish a message to a topic      |
| GET    | /messages       | Retrieve all messages of a topic  |

```

### 📁 Project Structure

``` graphql
Pub-Sub-System/
├── src/
│   ├── main.cpp              # Crow web server and endpoint handlers
│   └── TopicManager.cpp      # Core Pub-Sub logic
├── include/
│   └── cors.h                # Cross-Origin Resource Sharing setup
├── external/
│   └── crow/                 # Crow web framework (cloned from GitHub)
├── CMakeLists.txt            # CMake build configuration
├── publish.html              # Optional frontend UI for testing
└── README.md

```

### License
This project is open source and available under the MIT License.

### 🙋‍♂️ Author
Ronak Parmar
Built as part of systems-level and backend engineering research/practice.
Feel free to fork, contribute, or get in touch!