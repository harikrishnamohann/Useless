<img width="1280" alt="readme-banner" src="https://github.com/user-attachments/assets/35332e92-44cb-425b-9dff-27bcf1023c6c">

# Wootkas 🎯


## Basic Details
### Team Name: Some useless people


### Team Members
- Team Lead: Harikrishna Mohan - College of engineering and management, vadakkal
- Member 2: Neil Presanan - College of engineering and management, vadakkal
- Member 3: Amal S Kumar - College of engineering and management, vadakkal

### Project Description
Wootkas is a simple C program that can create variations of cool svg abstract arts using text manipulation. 

### The Problem (that doesn't exist)
This is made for pleasure only. There was no problem with my wallpapers in the first place.

### The Solution (that nobody asked for)
A new wallpaper engine that nobody asked for. We couldn't reach there, but we made a base with the logic we intended to perform.
The current state of this project only represent an api that can be used for building our clever little wallpaper engine (it is unfinished -_-).

## Technical Details
### Technologies/Components Used
For Software:

- It is written in C
- Some custom Libraries are used during the process
	- arena.h
	
	> it is a custom memory allocator that handles memory using the arena allocation strategy.

	- list.h
	
	> It is a custom implementation of doubly linked list using Arena allocator. This was used because of un-sahikkable segfaults during the last moment.

- Build system used: makefile

## Implementation
### Prerequisites:
- gcc
- make

### Installation
1. clone the Repository using `git clone https://github.com/harikrishnamohann/Useless.git`
2. go to the project folder: `cd ./Useless`

# Run
### For linux:
- make the run.sh file executable: `chmod +x run.sh`
- run it using: `./run.sh`
- 
### For other systems:
- run `make`
- execute `./target/debug`
---
## How does it work?
There are a predetermined set of svg files with custom identifiers placed in desired locations. The program reads the file and process it character by character, thereby replacing the identifiers using a key value pair. It outputs the modified text into out.svg file.

# Demo
![Demo](https://github.com/harikrishnamohann/Useless/blob/master/demo/demo.gif)

# Diagrams
![The Plan](https://github.com/harikrishnamohann/Useless/blob/master/demo/ThePlan.jpg)
*This was the idea we begin with. A minimal abstract wallpaper generation tool, which runs as a background process and updates the wallpaper based on time with some sprinkled entropy in the image such as change in color, position, transformation of objects etc*

## Team Contributions
- Harikrishna Mohan: worked on text processing
- Amal S kumar: Worked on helper functions for text processing
- Neil Presanan: Worked on setting up git, svg's and kept us awake till morning

---
Made with ❤️ at TinkerHub Useless Projects 

![Static Badge](https://img.shields.io/badge/TinkerHub-24?color=%23000000&link=https%3A%2F%2Fwww.tinkerhub.org%2F)
![Static Badge](https://img.shields.io/badge/UselessProject--24-24?link=https%3A%2F%2Fwww.tinkerhub.org%2Fevents%2FQ2Q1TQKX6Q%2FUseless%2520Projects)


