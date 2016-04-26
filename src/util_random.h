#ifndef UTILRANDOMH
#define UTILRANDOMH

#include <chrono>
#include <random>

std::default_random_engine gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
std::uniform_real_distribution<double> randr(0.0, 1.0);

#endif
