readmee
# Wootkas
🚧🚧 Work in progress... 🚧🚧

This project is in a messy state since it is created during a hackathon. It ambitions to mature as a wallpaper engine that creates variations of minimal abstract arts from a preset of svg files using basic text manipulation.

### Demo
 ![Demo](https://github.com/harikrishnamohann/Useless/blob/master/demo/demo.gif)

### Description
This is a c program to create infinite variations of an svg image preset using basic text manipulation. 

### How it works?
There are a predetermined set of svg files with custom identifiers placed in desired locations. The program reads the file and process it character by character, thereby replacing the identifiers using a key value pair. It outputs the modified text into out.svg file.

### Libraries used: 
- Some C standard libraries
- arena.h
> A custom memory allocator using the widely-used arena-allocation strategy.
- list.h
> It is a custom implementation of doubly linked list using Arena allocator.

### To-do:
- Memory management & remove unused functions
- Implement a script for handling wallpapers on the system based on time or other events
- Add more preset svg's
- make a way for the user to select a presets 

## Contributers
- [BATMAN6666-007](https://github.com/BATMAN6666-007)
- [Lunarmist](https://github.com/Lunarmist-byte)