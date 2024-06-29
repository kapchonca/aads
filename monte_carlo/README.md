
# Monte Carlo Pi Estimation

This project estimates the value of π (Pi) using the Monte Carlo method. It leverages multithreading to speed up the computation process.

## How It Works

The Monte Carlo method for estimating π involves randomly generating points in a unit square and checking how many fall inside a quarter circle. The ratio of the points inside the quarter circle to the total number of points, multiplied by 4, approximates π.

## Build 

   ```bash
   cd <root project directory>
   mkdir build
   cd build
   cmake ..
   make
   ```

## Run

Run the program with the desired number of threads.

```sh
./monte_carlo <number of threads>
```

## Program Output

The program outputs the following:

- **Average time per launch**: The average time taken for each launch of the simulation.
- **Value of π**: The estimated value of π.
- **Estimation precision**: Whether the estimation is within the specified precision `epsilon`.

### Sample Output

```sh
Average time per launch: 0.123456 seconds
Value of pi: 3.141592
Estimation is true
```
