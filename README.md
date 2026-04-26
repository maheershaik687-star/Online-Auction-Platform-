# Online-Auction-Platform


# 📘 Online Auction System (C Project)

## 📌 Project Title
Online Auction System using Heap, Linked List, and DAG

---

## 👨‍💻 Team Members
- Shaik Maheer
- Nanjala Vikram Karthikeya

---

## ❓ Problem Statement
Design and implement an Online Auction System that allows:
- Registration of players (bidders)
- Adding auction items
- Placing bids on items
- Tracking the highest bid efficiently
- Managing bid dependencies using a Directed Acyclic Graph (DAG)
- Preventing invalid bid dependencies (cycles)

---

## 🧠 Data Structures Used

### 1. Linked List
- Used to store players and items
- Supports dynamic memory allocation

### 2. Max Heap
- Stores bids efficiently
- Allows quick access to highest bid (O(1))

### 3. Directed Acyclic Graph (DAG)
- Represents bid dependencies
- Prevents cycles using DFS

### 4. Arrays
- Used for adjacency matrix representation

---

## ⚙️ Algorithm Explanation

### 🔹 Add Player
- Create new node
- Insert into linked list

### 🔹 Add Item
- Create item node
- Initialize heap and DAG

### 🔹 Place Bid
- Check if player exists
- Insert bid into heap
- Maintain heap property using heapify-up
- Assign Bid ID

### 🔹 Heap Operation
- Parent = (i - 1) / 2
- Swap if child > parent

### 🔹 DAG Dependency
- Add edge between bids
- Run DFS to detect cycle
- Reject if cycle exists

### 🔹 Cycle Detection
- Use visited[] and recursion stack
- Detect back edge

---






### sample ouput
<img width="684" height="382" alt="image" src="https://github.com/user-attachments/assets/5fa2993c-77fb-42ce-bb12-7cdd7d65aafa" />





 
