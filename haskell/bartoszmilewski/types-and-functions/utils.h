#include <thread>
#include <chrono>

void wait(int seconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000*seconds));
}
