# DoubleHashingDB

## Overview

DoubleHashingDB is a project that implements a hash table using the double hashing technique. This project is based on the data structure and aims to provide an efficient way to handle collisions in hash tables.

## Features

- **Double Hashing**: Implements double hashing to resolve collisions in the hash table.
- **Efficient Lookups**: Provides efficient lookup, insertion, and deletion operations.

## Hash Table with Double Hashing

Double hashing is a collision resolution technique in open addressing hash tables. When a collision occurs, double hashing uses a secondary hash function to calculate the interval between probes. This ensures that the sequence of probes is different for different keys, reducing the likelihood of clustering.

### Primary Hash Function

The primary hash function is used to determine the initial position of the key in the hash table.

### Secondary Hash Function

The secondary hash function is used to calculate the step size for probing. The step size is added to the initial position to find the next position in case of a collision.

### Example

```cpp
// Example of double hashing
int hash1(int key) {
    return key % tableSize;
}

int hash2(int key) {
    return prime - (key % prime);
}

int doubleHash(int key, int i) {
    return (hash1(key) + i * hash2(key)) % tableSize;
}
```

## Installation

To install and run the project, follow these steps:

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/DoubleHashingDB.git
    ```
2. Navigate to the project directory:
    ```sh
    cd DoubleHashingDB
    ```
3. Build the project using your preferred build system, for example:
   ```sh
    g++ -o main main.cpp
   ```

## Docker

To run the project using Docker, follow these steps:

1. Build the Docker image:
    ```sh
    docker build -t doublehashingdb .
    ```
2. Run the Docker container:
    ```sh
    docker run -it --rm doublehashingdb
