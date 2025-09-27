# Student Comprehensive Evaluation System

A C++-based student management system that supports student information entry, query, modification, deletion, sorting, and score analysis.

## Features
- **Data Input**: Manual entry or batch import from text files.
- **Information Management**: Add, modify, delete student records (unique ID verification).
- **Search Functions**: Precise search (by ID, name, score, etc.) and fuzzy search.
- **Sorting**: Sort by student ID, average exam score, or comprehensive evaluation score (ascending/descending).
- **Score Calculation**: Automatically compute average exam scores and comprehensive evaluation scores (with weighted calculation).
- **Data Export**: Save results to text files (intermediate and final outputs).

## Tech Stack
- Language: C++ (C++11 or higher)
- Build Tool: Makefile (Linux/macOS) / MinGW (Windows)
- Dependencies: Standard C++ Libraries (no third-party libraries required)

## Quick Start

### Prerequisites
- C++ compiler (GCC, Clang, or MSVC)
- Make (for Linux/macOS) or MinGW (for Windows)

### Build & Run
1. Clone the repository
   ```bash
   git clone https://github.com/your-username/student-comprehensive-evaluation-system.git
   cd student-comprehensive-evaluation-system
