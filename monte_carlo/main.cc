#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

int64_t CountHits(int64_t n) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dis(0.0, 1.0);

  int64_t counter = 0;
  for (int64_t _ = 0; _ < n; ++_) {
    double x = dis(gen);
    double y = dis(gen);
    if (x * x + y * y <= 1) {
      ++counter;
    }
  }
  return counter;
}

bool EvalPrecision(double epsilon, int64_t total_points,
                   std::vector<double> values) {
  double evaluation =
      M_PI_4 * (1 - M_PI_4) / (total_points * epsilon * epsilon * 1 * 1);
  int counter = 0;
  for (long unsigned int i = 0; i < values.size(); ++i) {
    if (std::abs(values[i] - M_PI_4) >= epsilon) {
      ++counter;
    }
  }
  return static_cast<double>(counter) / 100 <= evaluation;
}

double MonteCarloPi(int num_threads, int64_t total_points) {
  const int64_t points_per_thread = total_points / num_threads;
  std::vector<std::thread> threads;
  threads.reserve(num_threads);
  std::vector<int64_t> partial_counts(num_threads, 0);

  for (int i = 0; i < num_threads; ++i) {
    threads.emplace_back([i, points_per_thread, &partial_counts] {
      partial_counts[i] = CountHits(points_per_thread);
    });
  }

  for (auto& thread : threads) {
    thread.join();
  }

  int64_t total_count =
      std::accumulate(partial_counts.begin(), partial_counts.end(), 0);
  return static_cast<double>(total_count) / total_points;
}

int main(int argc, char const* argv[]) {
  if (argc != 2) {
    std::cerr << "Program usage: ./monte_carlo <number_of_threads>"
              << std::endl;
    return 1;
  }

  try {
    int num_threads = std::stoi(argv[1]);
    if (num_threads < 1) {
      throw std::invalid_argument("Number of threads must be positive.");
    }

    const int64_t total_points = 10000000LL;
    const int launch_count = 100;
    const double epsilon = 0.001f;

    std::vector<double> pi_results;
    pi_results.reserve(launch_count);

    double time_counter = 0;

    for (int i = 0; i < launch_count; ++i) {
      auto start_time = std::chrono::steady_clock::now();

      pi_results.emplace_back(MonteCarloPi(num_threads, total_points));

      auto end_time = std::chrono::steady_clock::now();
      std::chrono::duration<double> elapsed_seconds = end_time - start_time;
      time_counter += elapsed_seconds.count();
    }

    bool estimation = EvalPrecision(epsilon, total_points, pi_results);

    double average_value =
        std::accumulate(pi_results.begin(), pi_results.end(), 0.0) * 4 /
        launch_count;

    std::cout << "Average time per launch: " << time_counter / launch_count
              << " seconds" << std::endl;
    std::cout << "Value of pi: " << average_value << std::endl;
    std::cout << "Estimation is " << std::boolalpha << estimation << std::endl;

    return 0;
  } catch (const std::invalid_argument& e) {
    std::cerr << "Invalid argument: " << e.what() << std::endl;
    return 1;
  }
}