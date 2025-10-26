<p align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/1/18/C_Programming_Language.svg" alt="C Logo" width="100" height="100"/>
  <img src="https://upload.wikimedia.org/wikipedia/commons/1/18/ISO_C%2B%2B_Logo.svg" alt="C++ Logo" width="100" height="100"/>
</p>

# ECM2433 - The C Family Coursework

## Module Information
- **Module**: ECM2433 The C Family  
- **Module Leader**: Richard Everson  
- **Academic Year**: 2024/25  
- **Submission Deadline**: Tuesday, 11th March 2025  
- **Assessment Weight**: 30% of module grade  
- **Author**: Khelifi Mohamed Yacine  

## Overview
This repository contains solutions for the **ECM2433: The C Family Continuous Assessment** at the University of Exeter. The coursework demonstrates advanced programming in **C**, focusing on algorithm design, modular programming, and statistical simulation.

The assignment consists of three main exercises:
1. **Word Lengths & Histograms**
2. **Anagrams**
3. **Patience (Card Game Simulation)**

## Project Structure
```
C family coursework/
│
├── first/
│   ├── histogram.c
│   ├── demo_histogram.c
│   ├── wordlengths.c
│   └── dracula.txt
│
├── second/
│   ├── anagram.c
│   ├── anaquery.c
│   ├── histogram.c
│   ├── words.txt
│   └── Makefile
│
├── third/
│   ├── patience.c
│   ├── pstatistics.c
│   ├── patience.h
│   ├── phistogram.txt
│   ├── lose.txt
│   ├── win.txt
│   └── Makefile
│
└── declaration.png
```

## Part 1 - Word Lengths & Histograms

### Description
Implementation of word length analysis and histogram generation for text files.

### Key Features
- `histogram()` and `histogram_lengths()` functions  
- Word length distribution analysis  
- Visual histogram output using asterisks  

### Usage
```bash
cd first
gcc histogram.c demo_histogram.c -o demo_histogram
gcc wordlengths.c -o wordlengths
./demo_histogram
./wordlengths dracula.txt
```

### Example Output
```
Word Length Distribution:
1:  ** (2.5%)
2:  ******* (7.8%)
3:  ************ (12.1%)
...
```

## Part 2 - Anagrams

### Description
Linked list-based anagram detection system using sorted string keys.

### Programs
- `anagram.c` - Finds all anagram sets in a dictionary  
- `anaquery.c` - Interactive anagram lookup tool  

### Compilation
```bash
cd second
make
```

### Usage
```bash
./anagram
./anaquery
```

### Example Session
```bash
$ ./anaquery
Enter a word: orchestra
Anagrams: carthorse

Enter a word: listen
Anagrams: silent, enlist
```

### Features
- Histogram of log₁₀(V) anagram distributions  
- Efficient linked list implementation  
- Interactive query system  

## Part 3 - Patience Card Game Simulation

### Description
Simulation of the Patience card game to estimate winning probabilities under specific rules.

### Core Functions
- `addto11()` - Rule checking for cards summing to 11  
- `jqk()` - Rule checking for J, Q, K sequences  
- `play(deck, verbose)` - Single game simulation  
- `many_plays(N)` - Multiple game simulations  

### Compilation
```bash
cd third
make
```

### Usage
```bash
./patience        # Single game with verbose output
./pstatistics     # 10,000+ simulations with statistics
```

### Output Files
- `win.txt` - Example winning game  
- `lose.txt` - Example losing game  
- `phistogram.txt` - Histogram of remaining cards  

### Example Output
```
Game result: WIN
Cards remaining: 0
Probability estimate: 0.1245
```

## Compilation Instructions

### Prerequisites
- GCC compiler  
- GNU Scientific Library (GSL)  

### Build Commands
```bash
# Part 1
cd first
gcc histogram.c demo_histogram.c -o demo_histogram
gcc wordlengths.c -o wordlengths

# Part 2
cd ../second
make

# Part 3
cd ../third
make
```

## Academic Declaration

### GenAI Usage
- ☑️ I have not used any GenAI tools in preparing this coursework  
- ☑️ All non-original material has been clearly identified  

### Marking Criteria
- ✅ Algorithm correctness  
- ✅ Code implementation accuracy  
- ✅ Clarity, efficiency, and structure  
- ✅ Proper documentation and formatting  
- ✅ Correct memory allocation and deallocation  

## Learning Outcomes

### Technical Skills
- C data structures (arrays, pointers, linked lists)  
- Modular programming and Makefiles  
- Statistical simulation and visualization  
- File I/O and user interaction  
- Program testing and validation  

### Programming Concepts
- Algorithm design and analysis  
- Memory management in C  
- Code organization and modularity  
- Statistical analysis implementation  
- Interactive program design  

## Author Information
**Khelifi Mohamed Yacine**  
BSc Computer Science, University of Exeter  
Email: khelifimohamedyacine@outlook.com  

---

*This coursework submission demonstrates proficiency in C programming and algorithmic problem solving as part of the ECM2433 module requirements.*
