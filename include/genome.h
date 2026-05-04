#pragma once
#include "helper.h"
#include "pch.h"
#include <vector>

struct Gen {
  char sourceType;
  std::string sourceId;

  char sinkType;
  std::string sinkId;

  std::string weight;
};

class Genome {
public:
  Genome(int length);
  Genome(const std::string &hexSource);
  Genome(const std::string& hexSource, float mutationRate);
  const std::string toString();
  const std::string toBinaryString();
  const std::vector<Gen> getGens();

  void parseGenome();
  void displayGenomeBinary() {
    for (int i = 0; i < _binaryString.length(); i++) {
      if (i % 32 == 0 && i != 0) std::cout << std::endl;

      if (i % 32 == 0)
        std::cout << _binaryString[i] << " ";
      else if (i % 32 >= 1 && i % 32 <= 7 || i % 32 >= 9 && i % 32 <= 15)
        std::cout << _binaryString[i];
      else if (i % 32 == 8)
        std::cout << " " << _binaryString[i] << " ";
      else
        std::cout << _binaryString[i];

      if (i % 32 == 15) std::cout << " ";
    }
  }

private:
  std::string _genome;
  std::string _binaryString;

  std::vector<Gen> _gens;
};
