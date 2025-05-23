# 🛰️ Pub-Sub Server in Modern C++

A multithreaded Publish–Subscribe (Pub-Sub) server built in modern C++ using:

- [Crow](https://github.com/CrowCpp/crow) – Flask-like C++ web framework
- [Boost.Asio](https://www.boost.org/doc/libs/1_82_0/doc/html/boost_asio.html) – for asynchronous networking
- [GoogleTest](https://github.com/google/googletest) – unit testing
- [Catch2](https://github.com/catchorg/Catch2) – behavior-driven testing
- [Doxygen](https://www.doxygen.nl/) – auto-generated documentation
- [CMake](https://cmake.org/) – modern build system

> ⚙️ A minimal, in-memory message broker to understand Pub-Sub internals like Kafka, built with modern C++ and RESTful APIs.

---

## 📌 Features

- 🧵 **Thread-safe Topic Management**
- 🔔 **Real-time Message Publishing and Subscribing**
- 🌐 **RESTful API with Crow**
- ⚡ **Async Networking with Boost.Asio**
- 🧪 **Unit & BDD Testing with GoogleTest and Catch2**
- 📚 **Doxygen-based API Documentation**
- 🛠️ **Modular CMake Build**
- 🔁 **CI/CD Ready (e.g., GitLab)**

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
```

# 🧪 Running Tests
```bash
    ctest
```

# 📚 Generate Documentation
```bash
    cmake --build . --target doc_doxygen
```

# Run the server
```bash
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
│   ├── main.cpp              # Crow server & routing
│   └── TopicManager.cpp      # Topic-based pub-sub logic
├── include/
│   └── cors.h                # CORS setup for REST API
├── external/
│   ├── crow/                 # Crow web framework
│   └── ...                   # Other dependencies (e.g., Catch2)
├── tests/
│   ├── gtests/               # GoogleTest unit tests
│   └── catch2/               # Catch2-based specs
├── CMakeLists.txt            # Build configuration
├── publish.html              # Optional frontend UI
├── Doxyfile                  # Doxygen config
└── README.md

```

### License
This project is open source and available under the MIT License.

### 🙋‍♂️ Author
Ronak Parmar
Built as part of systems-level and backend engineering research/practice.
Feel free to fork, contribute, or get in touch!
