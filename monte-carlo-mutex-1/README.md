# README

This is a C++ program that estimates the value of Pi using the Monte Carlo method with multithreading.

## Environment Setup

To run this program, you will need a C++ compiler installed on your computer. You can use g++ or clang++ to compile the code. You will also need the pthread library. If you are using Linux or macOS, pthread is usually included with the system libraries. If you are using Windows, you can download pthread from the following website: https://sourceware.org/pthreads-win32/.

## How to Run the Program

To compile the program, open a terminal and navigate to the directory where the source file is located. Then, use the following command to compile the code:

```
g++ -std=c++11 -pthread monte-carlo-mutex.cpp -o monte-carlo-mutex
```

This will create an executable file called `monte-carlo-mutex`. To run the program, use the following command:

```
./monte-carlo-mutex
```

By default, the program generates 1,000,000 random points and uses 4 threads. You can modify these values in the `main()` function.

## Result
！[](./monte-carlo-mutex.png)


## Code Explanation

The program uses the Monte Carlo method to estimate the value of Pi. It generates random points inside a square with sides of length 2 and centered at the origin. It then counts the number of points that fall inside the inscribed circle with radius 1 and centered at the origin. The ratio of the number of points inside the circle to the total number of points generated is an estimate of Pi/4.

- The `pthread_mutex_lock()` is a mutual exclusion lock that is used to protect critical sections of code from concurrent access by multiple threads. In this program, we use a pthread_mutex to synchronize access to the global variables `points_in_circle` and `total_points`.

- The `generate_points()` function generates random points and counts the ones that fall inside the circle. It uses a mutex to synchronize access to the global variables `points_in_circle` and `total_points`.

- The `monte_carlo_pi_multithreaded()` function creates multiple threads and assigns an equal number of points to each thread. It then waits for all threads to finish and calculates the estimated value of Pi.

- The `main()` function calls the `monte_carlo_pi_multithreaded()` function. It prints the estimated value of Pi to the console.
