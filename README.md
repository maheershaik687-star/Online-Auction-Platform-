# Online-Auction-Platform

# 🏆 Online Auction System (DSA Project)



## 📖 Abstract
This project implements an Online Auction System using core Data Structures 
such as Linked List, Max Heap, and Directed Acyclic Graph (DAG). 
It efficiently manages players, items, and bidding processes while ensuring 
no cyclic dependencies in bid relationships.

## 🎯 Objectives
- To implement real-time bidding using Heap
- To manage users dynamically using Linked List
- To prevent invalid bid dependencies using DAG
- To simulate real-world auction platforms

## ⚙️ Features
- Add Players
- Add Auction Items
- Place Bids (Max Heap)
- Track Highest Bid
- Bid Dependency Graph (DAG)
- File Storage System


## 🧠 Data Structures Used

| Data Structure | Purpose |
|---------------|--------|
| Linked List | Store players & items |
| Max Heap | Maintain highest bid |
| DAG | Manage bid dependencies |
| Arrays | Store heap & graph |

## 🏗️ System Architecture

Player → Item → Bids (Heap) → DAG (Dependencies)

Flow:
1. Player registers
2. Item is added
3. Player places bid
4. Heap updates highest bid
5. DAG validates dependencies

## 💻 Code Structure

- Player Management
- Item Management
- Heap Operations
- DAG Cycle Detection
- File Handling
- Menu Driven Interface


## 🔬 Methodology

- Heap is used to maintain highest bid efficiently (O(log n))
- DAG is used to prevent cyclic dependencies using DFS
- Linked List allows dynamic memory management

  ## 📊 Results

- Efficient bid retrieval
- No cyclic dependency errors
- Dynamic user/item handling

## 🔮 Future Work

- Web-based UI
- Database integration
- Real-time bidding system
- Authentication system


## 📚 References

- Data Structures by Cormen
- GeeksforGeeks
- Online Auction Systems Research Papers



 
