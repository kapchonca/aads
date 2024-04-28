#include <chrono>
#include <cstring>
#include <iostream>
#include <thread>

volatile char global_variable = 'b';

void write_access(long num_steps, int delay, char* arr) {
  for (long i = 0; i < num_steps; ++i) {
    arr[i * 4096] = 'a';
    if (i % 1000 == 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
  }
}

void read_access(long num_steps, int delay, char* arr) {
  for (long i = 0; i < num_steps; ++i) {
    global_variable = arr[i * 4096];
    if (i % 1000 == 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
  }
}

int main(int argc, char const* argv[]) {
  if (argc != 2 or
      !((std::strcmp(argv[1], "r") == 0 or std::strcmp(argv[1], "w") == 0))) {
    std::cerr
        << "Program usage: ./pumpkin [r|w]\n'r' = read mode, 'w' = write mode"
        << std::endl;
    return 1;
  }

  char* arr = new (std::nothrow) char[12L * 1024 * 1024 * 1024];

  if (!arr) {
    std::cerr << "Failed to allocate memory." << std::endl;
    return 1;
  }

  const int delay_ms = 10;
  const long num_steps = (12L * 1024 * 1024 * 1024) / 4096;

  if (std::strcmp(argv[1], "r") == 0) {
    read_access(num_steps, delay_ms, arr);

  } else {
    write_access(num_steps, delay_ms, arr);
  }

  delete[] arr;
  return 0;
}
