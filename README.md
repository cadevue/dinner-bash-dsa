# Background 📚
This project is part of my CS101 Refresher. More details on [my website](https://www.cadevue.com)!

# About This Project 🧱
This program is part of my Computer Science Study at Bandung Institute of Technology. The specific course related to this project is IF2110 Algorithm and Data Structure. The full specification of the project is available at the [docs folder](docs/Specification.pdf), although it is available in Indonesian only.

This project was originally assigned at the 3rd semester, but I decided to redo the entire project (February 2025) from scratch to improve the code quality and to make it more maintainable. It also useful as a refresher for me to understand the concept of basic data structure and its related algorithms.

# Project Description 📝
A CLI program implemented in C about a cooking management game! Player can move inside a map and interact with the environment, such as buying ingredients and cooking food. This game has no win condition. This is just simulation that focus on implementation of basic data structure and algorithm, such as:

- Static List to store game configurations (loaded in the beginning of the game) 
- Priority Queue (Linked List) to store player's inventory
- Matrix to store the map of the game
- Tree to store the recipe of the food
- Stack to store the player's action history, with undo and redo feature

# How to Run 🚀
Prerequisites:
- GCC Compiler
- Makefile

Steps:
1. Navigate to the project directory
2. Run `make build` to compile the program
3. Run `make run` to start the program
3. Optionally, you can run `make all` to compile and run the program in one command