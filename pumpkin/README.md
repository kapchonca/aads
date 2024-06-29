# Turning the operating system into a pumpkin

This is a simple C++ program that consumes all your RAM using read and write operations on a large array.

## WARNING

This program is specifically designed to turn your OS into a pumpkin. Be careful: turn off the program before your RAM runs out using the `Ctrl + C` combination. 

## Build and run

   ```bash
   cd <root project directory>
   mkdir build
   cd build
   cmake ..
   make
   ./pumpkin
   ```

## Usage

Run the program with either `r` for read mode or `w` for write mode:

```sh
./pumpkin [r|w]
```

- `r`: Read mode - the program will perform read operations on the allocated memory.
- `w`: Write mode - the program will perform write operations on the allocated memory.
