# Data Structures in Go

This repository contains implementations of various data structures in Go. These implementations are designed to be simple, efficient, and easy to understand.

## Table of Contents

- [Introduction](#introduction)
- [Data Structures](#data-structures)
  - [Binary Tree](#binary-tree)
  - [Heap](#heap)
  - [List](#list)
  - [Ring](#ring)
  - [Doubly Linked List](#doubly-linked-list)
  - [Hash Table](#hash-table)
  - [Linked List](#linked-list)
  - [Queue](#queue)
  - [Stack](#stack)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This repository provides implementations for common data structures in Go. Each data structure is implemented in its own file for modularity and ease of use.

## Data Structures

### Binary Tree

- **File:** `binTree.go`
- **Description:** Implementation of a binary tree data structure. Supports standard operations like insertion, deletion, and traversal.

### Heap

- **File:** `conHeap.go`
- **Description:** Implementation of a heap data structure. Supports operations like insertion, deletion, and heapification.

### List

- **File:** `conList.go`
- **Description:** Implementation of a list data structure. Supports operations like addition, removal, and iteration.

### Ring

- **File:** `conRing.go`
- **Description:** Implementation of a ring (circular list) data structure. Supports operations typical of a circular list.

### Doubly Linked List

- **File:** `doublyLList.go`
- **Description:** Implementation of a doubly linked list data structure. Supports operations like addition, removal, and traversal in both directions.

### Hash Table

- **File:** `hashTable.go`
- **Description:** Implementation of a hash table data structure. Supports operations like insertion, deletion, and searching.

### Linked List

- **File:** `linkedList.go`
- **Description:** Implementation of a singly linked list data structure. Supports operations like addition, removal, and traversal.

### Queue

- **File:** `queue.go`
- **Description:** Implementation of a queue data structure. Supports standard queue operations like enqueue and dequeue.

### Stack

- **File:** `stack.go`
- **Description:** Implementation of a stack data structure. Supports standard stack operations like push and pop.

## Usage

To use any of the data structures, simply import the corresponding file into your Go project and instantiate the data structure as needed.

Example of using the binary tree:

```go
package main

import (
    "fmt"
    "path/to/your/repo/binTree"
)

func main() {
    tree := binTree.New()
    tree.Insert(10)
    tree.Insert(20)
    fmt.Println(tree.Search(10)) // Output: true
}
```
