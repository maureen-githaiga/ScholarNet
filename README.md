# ScholarNet

This project involves implementing data structures and algorithms for **ScholarNet**, a social network for affiliations and their publications.

---

## 🎯 Goal

Create a program to:

- Enter and search for information about **affiliations** and their **publications**.  
- Track how publications reference each other, creating chains of related publications.  
- Practice using ready-made data structures and algorithms from the C++ STL.  
- Write efficient algorithms and estimate their performance.  
- Produce code optimized for minimal command counts and efficient execution.

---

## 🛠️ Task Overview

Implement a class `datastructures` that:

- Stores required information within its data structures.  
- Implements methods to support the needed functionalities.  

> **Note:** The main program and graphical user interface (GUI) are provided.

---

## 🔍 Functionalities

### Affiliation Management

- Retrieve the count of affiliations.  
- Add, retrieve, and update affiliations with details such as:  
  - Name  
  - Coordinates  
  - Type  
- Retrieve affiliations sorted alphabetically or by distance.

### Publication Management

- Add publications with:  
  - IDs  
  - Names  
  - Years  
  - Affiliations  
- Establish reference relationships between publications.  
- Associate affiliations with publications.

### Search Operations

- Retrieve detailed information about affiliations, publications, and their relationships.  
- Find affiliations by geographic coordinates.  
- Discover publications from a specific affiliation.

### Performance Testing

- Evaluate the performance of operations using the provided `perftest` command.  
- `perftest` clears the data structure, adds a specified number of random affiliations and publications, and executes repeated commands to measure command counts.  
- Tests terminate early if execution exceeds a defined timeout.

---

## 💻 Development Environment

- Implemented on a **Linux desktop**.  
- Used **Qt Creator** and **GCC** for C++ development.  
- Leveraged tools for measuring command counts and performance profiling.

---

## 📂 Repository Structure

- `datastructures.cc` / `.hh` – Implementation of core data structures.  
- `mainprogram.cc` / `.hh` – Main program logic.  
- `mainwindow.cc` / `.hh` / `.ui` – GUI components.  
- `prg1.pro` – Qt project file.  
- Folders for example data, test cases, and optimization tests.

---

## 🚀 How to Run

1. Build the project using Qt Creator or `qmake` and `make`.  
2. Launch the main program to interact with ScholarNet’s GUI.  
3. Use the CLI or GUI to add affiliations, publications, and perform searches.  
4. Run performance tests with the `perftest` command.

---

## 📝 Notes

- Focus on efficient algorithm design and minimal resource usage.  
- Aim for code clarity and maintainability alongside performance.

---
