# Block-Based File Merge System (C)

## Overview

This project implements a block-based file merging system in C that merges two sorted binary files into a single sorted output file.

The system simulates how large-scale data processing systems and database engines handle data stored on disk. Instead of loading entire files into memory, the program processes data block by block, which improves efficiency when working with large datasets.

This approach is commonly used in:

- Database storage engines
- External sorting algorithms
- Big data processing systems
- File system utilities

The program reads blocks of records from two sorted input files and merges them into a third output file while maintaining the correct order based on a key field.

## Project Motivation

Modern database systems and large-scale data tools cannot load entire datasets into memory when data is too large.  

Instead, they use external memory algorithms, processing data in small chunks (blocks) read from disk.

This project demonstrates a simplified version of this concept using:

- Binary file storage
- Block buffering
- Sorted file merging
- Disk-based data processing

## File Structure

Each file consists of multiple blocks, and each block contains a fixed number of records.

File layout:
```
+----------------------+
| Block 0              |
| Records              |
+----------------------+
| Block 1              |
| Records              |
+----------------------+
| Block 2              |
| Records              |
+----------------------+
| ...                  |
+----------------------+
```
Each block is read and written as a single unit using binary file operations.

## Data Structures

### Record Structure

Each record represents a data entry with a sorting key.

typedef struct {
    int cle;
    int data;
} Tenreg;

Fields:

- cle: Sorting key used to order records
- data: Additional data associated with the record

The field cle determines the position of the record in the sorted order.

### Block Structure

Records are grouped into blocks for efficient disk access.

typedef struct {
    Tenreg records[MAXR_REC];
    int NB;
} Tbloc;

Fields:

- records: Array of records inside the block
- NB: Number of records currently stored in the block

Each block can store up to 10 records (MAXR_REC). Blocks reduce disk access operations by reading and writing multiple records at once.

## Core Concepts Implemented

### Block-Based File Processing

Instead of handling records one by one, the program processes data in blocks.

Advantages:

- Reduces disk I/O operations
- Improves performance for large files
- Simulates how real database systems operate internally

### Binary File Operations

Low-level file operations are used:

- fopen() for file handling
- fread() for reading blocks
- fwrite() for writing blocks

Example:

fread(buffer, sizeof(Tbloc), 1, file);

This reads an entire block from disk into memory.

## Merge Algorithm

The core of the program is the sorted merge algorithm.

Steps:

1. Open two sorted binary input files.
2. Load the first block from each file into memory buffers.
3. Compare records from both buffers using their sorting key (cle).
4. Insert the smallest record into an output buffer.
5. When the output buffer is full, write it to the output file.
6. Load new blocks when a buffer becomes empty.
7. Continue until both input files are fully processed.
8. Write any remaining records to the output file.

This ensures the resulting file remains fully sorted.

## Buffer Management

Three buffers are used during execution:

- buf1: Stores blocks from the first file
- buf2: Stores blocks from the second file
- buf3: Temporary buffer used to build the output block

Indexes track the current position inside each buffer:

- j1 -> index inside buffer1
- j2 -> index inside buffer2
- j3 -> index inside output buffer

## Example Workflow

Program execution:

1. Open two sorted binary files:

   - file_patientA.bin
   - file_patientB.bin

2. Merge the files into:

file_patientTotal.bin

3. The output file contains all records sorted by the key cle.

Example output:

Files merged successfully into 'file_patientTotal.bin'.

## Computational Complexity

The merge operation runs in:

O(n + m)

Where:

- n = number of records in file1
- m = number of records in file2

This is optimal for merging two sorted datasets.

## Educational Value

This project demonstrates important concepts:

- External merge algorithms
- Disk-based data processing
- File organization techniques
- Binary file manipulation
- Memory-efficient data processing

These concepts are widely used in:

- Database management systems
- Big data frameworks
- Search engines
- Data processing pipelines

## Technologies Used

- C Programming Language
- Binary File I/O
- Data Structures
- External Memory Algorithms

## Author

imlouli abderrahmane
cyber security Engineering Student  
Interested in Cybersecurity, Systems Programming, and Low-Level Data Structures  

This project was developed as part of my learning process to understand how large datasets are processed directly on disk using efficient algorithms.
