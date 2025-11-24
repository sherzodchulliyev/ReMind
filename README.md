# ReMind — C++ Flashcard Study Tool

**ReMind** is a distraction-free, terminal-based application designed to help students master subjects through "Active Recall." It allows users to build custom flashcard decks, save them permanently, and review them using a smart feedback system that prioritizes mistakes.

---

## Table of Contents
- [Project Overview](#project-overview)
- [Key Features](#key-features)
- [Project Structure](#project-structure)
- [How to Compile & Run](#how-to-compile--run)
- [Authors](#authors)

---

## Project Overview

We built ReMind to solve the problem of bloated, web-based study tools. It is lightweight, fast, and runs entirely in the command line. It utilizes **Parallel Vectors** to manage data dynamically and custom **File I/O** logic to ensure your study data is saved between sessions.

## Key Features

* **Dynamic Deck Management:** Uses STL Vectors to allow adding an unlimited number of flashcards.
* **Smart Review Session:** * Calculates your accuracy percentage (Accuracy = Correct / Total).
    * **Mistake Loop:** The program detects cards you answered 'n' (no) to and offers an immediate, focused review session for just those specific mistakes.
* **Robust Input Handling:** Implements advanced buffer management (using `cin.ignore` and `getline`) to prevent the common C++ issue of skipping inputs when switching between numbers and strings.
* **Persistent Storage:** Automatically checks for existing user files and saves/loads decks using a custom delimiter format.

---

## Project Structure

The project follows a modular architecture to separate logic from execution:

* **`main.cpp`**: The entry point. It handles user authentication, file existence checks, and the main menu `while(true)` loop.
* **`functions.h`**: A header file containing the core logic implementations:
    * `addFlashcards()`: Logic to input cards and handle "0" to exit.
    * `reviewFlashcards()`: The quiz algorithm, score calculation, and "Mistake Review" vector logic.
    * `saveToFile()` / `loadFromFile()`: Handles `.txt` parsing.
    * `displayMessage()`: UI element helper.
* **`*_flashcard.txt`**: The output files where your decks are stored.

---

## How to Compile & Run

You need a C++ compiler (like g++).

**1. Open your terminal.**
**2. Navigate to the project folder.**
**3. Run the program:**
```bash
./remind
```

# Authors
- Sherzod Chulliev
- Ruslan Rajabov
---
