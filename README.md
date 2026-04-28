# Inverted-Search-System
## 📌 Description
This project implements an inverted indexing system that maps words to their corresponding file locations, enabling faster search compared to traditional linear search.

## 🚀 Features
- Search words across multiple files
- Fast lookup using indexing
- Dynamic memory management
- Efficient data retrieval

## 🛠️ Technologies Used
- C Programming
- Linked Lists
- File Handling
- Hashing

## ⚙️ How It Works
- Reads multiple text files
- Breaks content into words
- Stores words in hash table
-  word points to list of file references

## ⚠️ Challenges Faced
- Handling collisions in hashing
- Managing dynamic memory allocation
- Avoiding duplicate entries
- Efficient traversal of linked lists

## 💡 Key Learnings
- Inverted indexing concept
- Hash table implementation
- Search optimization techniques
- Memory management in C

## ▶️ How to Run
1 gcc *.c -o search
2 ./search file1.txt file2.txt
