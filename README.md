# LS_Midterm: A UNIX File System Tool
This application was designed for FreeBSD and serves as the midterm assignment for the class CS631 - Advanced Programming in the Unix Environment, taught by Jan Schaumann.

## Assignment Requirements:
The objective of this assignment is to write a significant system tool from scratch. In doing so, you will learn many details of the UNIX filesystem and the general system concepts covered in class. The detailed assignment requirements can be found [here](https://stevens.netmeister.org/631/f23-midterm.html).

## Building the Program
To build the program, run cmake in the main directory of the program. Ensure you have cmake installed on your system.

To build the program, follow these steps:

1. Navigate to the main directory of the program.
2. Run the following commands:
```sh
make
```
To remove the only object files after compiling the binary run the following command
```sh
make clean-obj
```

To remove all files created during the make process including the binary run the following
```sh
make clean
```

## Running the Program

```sh
./ls_midterm [option] [path] ...
```

Replace [options] with any applicable flags and [path] with the directories or files you want to analyze. The program will list the contents of the specified directory, formatted according to the provided options.

## Memory Management
This program has been carefully developed to handle memory management correctly, ensuring no memory leaks. Valgrind was used extensively to check for and fix any memory issues.

