# ScholarNet
This is project involves implementing data structures and algorithms for ScholarNet a social network for afffiliations.

**Goal:** 
- Create a program where one can enter and search for information about affiliations and their publications.Publications refer to each other,which chains publications together.
- Practice how to use ready made data structures and algorithms of STL.
- Write efficient algorithms and estimate their performance.
- Produce code that is as efficient as possible in terms of command counts.

**Task:** Implementing the class to datastructures which would store the required information in its datastructures, and whose methods implement the required functionality.Main program and the graphical user interface were provided.

**Functionalities**

**Affiliation Management**

- Retrieve the count of affiliations
- Add , retrieve and update affiliatiopns with details like name ,coordinates and type.
- Get affiliations alphabetically and sorted by distance.

**Publication Management**
- Add publications with ID's names ,years and affiliations.
- Establish relationships between publications through references.
- Associate affiliations with publications.

  **Search Operations**
  - Retrieve information about affiliations ,publications and their relationships.
  - Find affiliations by their coordinates.
  - Discover publications from a particular affiliation

**Performance testing** - Evaluate the performance of operations using the provided perftest command. Which starts by clearing the data structure and adding n1 random affiliations and publications using random_add() which is then executed 'repeat' times.The command count is measured and if a test takes longer than timeout seconds it is halted.

**Development Environment**
- Implemented the project on a linux desktop environment ,utilizing tools such as QtCreator and GCC for C++ development which allowed access to command counters. 


