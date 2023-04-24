#include <iostream>
#include <random>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>

// Global variables
std::mutex mtx;
unsigned long points_in_circle = 0;
unsigned long total_points = 0;

// Function to check if a point is inside the circle
bool is_inside_circle(double x, double y) {
    return x * x + y * y <= 1.0;
}

// Function to generate random points and count the ones inside the circle
void generate_points(unsigned long n) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    unsigned long local_points_in_circle = 0;

    for (unsigned long i = 0; i < n; ++i) {
        double x = dis(gen);
        double y = dis(gen);
        if (is_inside_circle(x, y)) {
            ++local_points_in_circle;
        }
    }

    std::unique_lock<std::mutex> lock(mtx);
    points_in_circle += local_points_in_circle;
    total_points += n;
    lock.unlock();
}

// Function to run Monte Carlo simulation with multithreading
double monte_carlo_pi_multithreaded(unsigned long n_points, unsigned int n_threads) {
    // Reset global variables
    points_in_circle = 0;
    total_points = 0;

    // Create and start threads
    std::vector<std::thread> threads;
    unsigned long points_per_thread = n_points / n_threads;

    for (unsigned int i = 0; i < n_threads; ++i) {
        threads.push_back(std::thread(generate_points, points_per_thread));
    }

    // Join threads
    // &thread: A reference to the current std::thread object in the threads container.
    for (std::thread &thread : threads) {
        thread.join();
    }

    // Calculate and return estimated pi value
    return 4.0 * points_in_circle / total_points;
}

int main() {
    unsigned long n_points = 1000000;
    unsigned int n_threads = 4;

    auto start_time = std::chrono::high_resolution_clock::now();
    double pi_estimate = monte_carlo_pi_multithreaded(n_points, n_threads);
    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_time = end_time - start_time;

    std::cout << "Estimated value of Pi: " << pi_estimate << std::endl;
    //std::cout << "Elapsed time: " << elapsed_time.count() << " seconds" << std::endl;

    return 0;
}
