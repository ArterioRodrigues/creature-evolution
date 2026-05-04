#include "helper.h"

int randomNumberGenerator(int start, int end) {
  return ThreadSafeRandom::generate(start, end);
}

float randomNumberGenerator(float start, float end) {
  return ThreadSafeRandom::generate(start, end);
}

int weightedRandomGenerator(const std::vector<uint8_t> &weights) {
  return ThreadSafeRandom::weightedGenerate(weights);
}

int ThreadSafeRandom::generate(int start, int end) {
  thread_local std::random_device rd;
  thread_local std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(start, end);
  return dist(gen);
}

float ThreadSafeRandom::generate(float start, float end) {
  thread_local std::random_device rd;
  thread_local std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dist(start, end);
  return dist(gen);
}

int ThreadSafeRandom::weightedGenerate(const std::vector<uint8_t> &weights) {
  thread_local std::random_device rd;
  thread_local std::mt19937 gen(rd());
  std::discrete_distribution<int> dist(weights.begin(), weights.end());
  return dist(gen);
}

const char decimalToHex(int decimal) {
  if (decimal < 10)
    return '0' + decimal;

  switch (decimal) {
  case 10:
    return 'a';
  case 11:
    return 'b';
  case 12:
    return 'c';
  case 13:
    return 'd';
  case 14:
    return 'e';
  case 15:
    return 'f';
  }

  return 'X';
}
const int hexToDecimal(char hex) {
  if (hex <= '9')
    return int(hex - '0');

  switch (hex) {
  case 'a':
    return 10;
  case 'b':
    return 11;
  case 'c':
    return 12;
  case 'd':
    return 13;
  case 'e':
    return 14;
  case 'f':
    return 15;
  }

  return -1;
}
