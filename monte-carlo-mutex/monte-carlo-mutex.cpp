#include <iostream>
#include <random>
#include <pthread.h>
#include <vector>
#include <chrono>

// Global variables
pthread_mutex_t mtx ;
int points_in_circle = 0;
int total_points = 0;

// Function to check if a point is inside the circle
bool is_inside_circle(double x, double y) {
    return x * x + y * y <= 1.0;
}

// Function to generate random points and count the ones inside the circle
void* generate_points(void* arg) {
    int n = *((int*) arg);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    int local_points_in_circle = 0;

    for (int i = 0; i < n; ++i) {
        double x = dis(gen);
        double y = dis(gen);
        if (is_inside_circle(x, y)) {
            ++local_points_in_circle;
        }
    }

    pthread_mutex_lock(&mtx);
    points_in_circle += local_points_in_circle;
    total_points += n;
    pthread_mutex_unlock(&mtx);

    return nullptr;
}

// Function to run Monte Carlo simulation with multithreading
double monte_carlo_pi_multithreaded(int n_points, int n_threads) {
    // Reset global variables
    points_in_circle = 0;
    total_points = 0;

    // Create and start threads
    std::vector<pthread_t> threads(n_threads);
    int points_per_thread = n_points / n_threads;

    // fourth argument of the pthread_create function expects a void* (void pointer) as the argument
    for (int i = 0; i < n_threads; ++i) {
        pthread_create(&threads[i], nullptr, generate_points, (void*)&points_per_thread);
    }

    // Join threads
    // &thread: A reference to the current std::thread object in the threads container.
    for (pthread_t &thread : threads) {
        pthread_join(thread, nullptr);
    }

    // Calculate and return estimated pi value
    return 4.0 * points_in_circle / total_points;
}

int main() {
    int n_points = 1000000;
    int n_threads = 4;
    pthread_mutex_init(&mtx, NULL);

    auto start_time = std::chrono::high_resolution_clock::now();
    double pi_estimate = monte_carlo_pi_multithreaded(n_points, n_threads);
    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed_time = end_time - start_time;

    std::cout << "Estimated value of Pi: " << pi_estimate << std::endl;
    //std::cout << "Elapsed time: " << elapsed_time.count() << " seconds" << std::endl;

    return 0;
}
