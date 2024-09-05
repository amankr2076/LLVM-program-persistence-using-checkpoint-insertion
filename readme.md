Course Name - Compiler Design Lab CS 320/321
Course Instructor - Dr. Manojit Ghose

Certainly! Below is a revised README formatted for GitHub (Markdown) for our LLVM Pass project. This version includes slight modifications for better readability and navigation on GitHub.

---

# Project LLVM Pass

## Overview
This project focuses on creating an LLVM pass that inserts checkpoints after every function call in a given C++ application. This enhancement aims to make the system persistent, enabling recovery and continuation from the last checkpoint in case of a failure. This document outlines the necessary steps to set up the environment, compile the required components, and execute the program.

## Prerequisites
- **LLVM:** The LLVM Compiler Infrastructure provides a suite of tools and libraries for constructing compiler backends. Make sure LLVM is installed and properly configured on your system. The `llvm-config` utility should be accessible from the command line.
- **Clang:** A compiler front end for C, C++, Objective-C, and Objective-C++ programming languages. Clang must be installed to compile C++ applications into LLVM IR (Intermediate Representation).

## Installation Steps
1. **Install LLVM and Clang:**
   - **Linux:** Use the package manager to install LLVM and Clang. For Ubuntu:
     ```bash
     sudo apt-get install llvm clang
     ```
   - **Mac:** Use Homebrew to install LLVM:
     ```bash
     brew install llvm
     ```
   - **Other Operating Systems:** Refer to the [official LLVM download page](http://llvm.org/releases/download.html) for detailed installation instructions.

2. **Verify Installation:**
   Ensure both LLVM and Clang are correctly installed by checking their versions:
   ```bash
   llvm-config --version
   clang --version
   ```

## Compiling and Running the Project
1. **Compile the LLVM Pass:**
   Navigate to your project directory and compile the LLVM pass to a shared object file:
   ```bash
   clang++ -fPIC -shared -o insert-checkpoint.so insert-checkpoint.cpp $(llvm-config --cxxflags --ldflags --libs core)
   ```
   Note: The output file will be `insert-checkpoint.dylib` for Mac and `insert-checkpoint.so` for Linux/Windows.

2. **Compile the C++ Application to LLVM IR:**
   Compile the C++ application (`many_fun.cpp`) to LLVM IR (`many_fun.ll`):
   ```bash
   clang -S -emit-llvm many_fun.cpp -o many_fun.ll
   ```

3. **Run the LLVM Pass on the LLVM IR File:**
   Apply the LLVM pass to the LLVM IR file. If the first command doesn't work due to issues with the legacy pass manager, try alternative commands:
   ```bash
   opt -S -enable-new-pm=0 -load=./insert-checkpoint.so -insert-checkpoint many_fun.ll -o output.ll
   ```

4. **Compile the Perform Checkpoint Function:**
   Compile `perform_checkpoint.cpp` to an object file:
   ```bash
   clang++ -c perform_checkpoint.cpp -o perform_checkpoint.o
   ```

5. **Link and Execute the Program:**
   Link the `output.ll` file with the `perform_checkpoint.o` object file, and compile to an executable:
   ```bash
   clang++ output.ll perform_checkpoint.o -o output
   ./output
   ```

## Expected Outcome
Upon successful execution, the program will insert checkpoints after every function call, as indicated by messages printed to the terminal and entries in the `program_state.txt` file. This file logs the function names and battery levels at each checkpoint.

## College Name
College Name - Indian Institute of Information Technology Guwahati 
B.Tech CSE 3rd Year 
## Team Members
- Aman Kumar (2101027)
- Abhishek Kumar (2101012)
- Harsh Rajput (2101081)

The team has contributed to various aspects of this project, including the design of the LLVM pass, implementation of the checkpoint mechanism, and ensuring the robustness of the system's persistence feature.

---

"# LLVM-program-persistence-using-checkpoint-insertion" 
