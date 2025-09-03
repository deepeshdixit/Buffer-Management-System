Buffer Management System | Database Management Systems | Self-Project
This project is a self-implemented buffer management system designed for database queries. The primary goal was to explore and implement different page replacement algorithms to minimize expensive disk I/O operations and optimize query performance.

Features
Buffer Pool Management: Core components for managing a fixed-size buffer pool in memory to cache disk pages.

Multiple Eviction Policies: Implements and provides tools to test three different page replacement strategies:

Least Recently Used (LRU): A common algorithm that evicts the page that has not been used for the longest time.

Most Recently Used (MRU): A counter-intuitive strategy that evicts the most recently used page.

Clock: An approximation of LRU that provides a second chance for pages, identified as the most optimal strategy for selection queries in this project's analysis.

Pinned Block Mechanism: A pin_count mechanism is used to ensure that pages actively being used by a query are not evicted from the buffer pool.

Query Simulation: The project simulates SELECT and JOIN database queries to test the efficiency of the implemented strategies.

Performance Analysis: Tracks and reports the total number of disk I/O operations to quantify and compare the performance of each buffer management strategy.

Getting Started
Prerequisites
A C++ compiler that supports the C++20 standard (e.g., g++ or clang++).

make build tool.

Building and Running
Clone the Repository:

Bash

git clone https://github.com/deepeshdixit/Buffer-Management-System.git
cd Buffer-Management-System
Generate Binary Data Files: The project needs binary data files for queries. Run the table command to generate these from the provided CSVs.

Bash

make table
Run a Query: Use the make command to compile and run the desired query. For example, to run the select query:

Bash

make run_select
Project Structure
files/: Contains the raw CSV data and the generated binary data files.

include/: Contains all C++ source (.cpp, .inl) and header (.hpp) files.

bin/: Contains the compiled executable programs.

obj/: Contains the intermediate object (.o) files.

Technology Stack
Language: C++20

Build System: Make

Version Control: Git

Note: This project was a self-learning exercise conducted in March-April 2025.