# Compresso 🚀  
A C++ File Compression & Decompression Tool using Huffman Encoding

## 📌 Overview
**Compresso** is a command-line based file compression tool written in **C++** that uses **Huffman Encoding** to reduce file size efficiently.  
It supports both **compression** and **decompression** of files while preserving original data integrity.

This project is designed to demonstrate:
- Data Structures (Trees, Priority Queues)
- Greedy Algorithms (Huffman Coding)
- File Handling in C++
- Bit-level I/O operations

---

## ✨ Features
- 📉 Compress files using Huffman Encoding
- 📂 Decompress compressed files back to original
- ⚡ Efficient bit-level storage
- 🧠 Frequency-based encoding
- 💻 Cross-platform (Windows/Linux/Mac)

---

## 🗂️ Project Structure
Compresso/
│
├── compress.cpp # Compression logic
├── decompress.cpp # Decompression logic
├── huffman.cpp # Huffman tree implementation
├── huffman.h # Huffman header
├── bitio.h # Bit-level input/output handling
├── main.cpp # Entry point
└── README.md # Project documentation


---

## 🛠️ Requirements
- C++17 or later
- GCC / Clang / MSVC
- Any OS (Windows, Linux, macOS)

---

## ⚙️ Build Instructions

### 🔹 Compile (Windows / Linux / Mac)
```bash
g++ -std=c++17 main.cpp compress.cpp decompress.cpp huffman.cpp -o compresso

▶️ Usage
🔹 Compress a file
./compresso compress input.txt output.huff

🔹 Decompress a file
./compresso decompress output.huff restored.txt

📊 How It Works

Reads input file and calculates character frequencies

Builds a Huffman Tree using a priority queue

Generates binary codes for each character

Writes compressed data using bit-level I/O

Decompression reverses the process using the stored tree

🎯 Learning Outcomes

Understanding Huffman Coding

Implementing trees and priority queues

File I/O and binary data handling

Writing modular and scalable C++ code

📌 Future Improvements

Add file header metadata

Improve compression ratio

Add folder compression

Add CLI help flags

Performance optimization

👨‍💻 Author

Mohd Azam Siraj
GitHub: https://github.com/azam-109

⭐ If you like this project

Give it a ⭐ on GitHub — it really helps!
