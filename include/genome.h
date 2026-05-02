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
  Genome(int length) {
    _genome = "";
    _binaryString = "";

    for (int i = 0; i < length; i++) {
      for (int j = 0; j < 8; j++) {
        _genome += decimalToHex(randomNumberGenerator(0, 15));
      }
    }

    int count = 0;
    for (auto c : _genome) {
      int decimal = hexToDecimal(c);
      std::string bin = std::bitset<4>(decimal).to_string();
      _binaryString += bin;
    }

    Gen gen;
    for (int i = 0; i < _binaryString.length(); i++) {
      if (i % 32 == 0 && i != 0) {
        _gens.push_back(gen);
        gen = Gen{};
      }
      if (i % 32 == 0)
        gen.sourceType = _binaryString[i];
      else if (i % 32 == 8)
        gen.sinkType = _binaryString[i];
      else if (i % 32 >= 1 && i % 32 <= 7)
        gen.sourceId = gen.sourceId + _binaryString[i];
      else if (i % 32 >= 9 && i % 32 <= 15)
        gen.sinkId = gen.sinkId + _binaryString[i];
      else
        gen.weight += _binaryString[i];
    }

    _gens.push_back(gen);
  }

  const std::string getGenome() { return _genome; }
  const std::string getGenomeBinary() { return _binaryString; }
  const std::vector<Gen> getGens() { return _gens; }

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
