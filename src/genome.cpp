#include "genome.h"
#include "helper.h"

void Genome::parseGenome() {
  _binaryString = "";

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

Genome::Genome(int length) {
  _genome = "";
  _binaryString = "";

  for (int i = 0; i < length; i++) {
    for (int j = 0; j < 8; j++) {
      _genome += decimalToHex(randomNumberGenerator(0, 15));
    }
  }

  parseGenome();
}

Genome::Genome(const std::string &hexSource) {
  _genome = hexSource;
  parseGenome();
}

Genome::Genome(const std::string &hexSource, float mutationRate) {
  for (int i = 0; i < hexSource.length(); i++) {
    int decimal = hexToDecimal(hexSource[i]);
    std::string bin = std::bitset<4>(decimal).to_string();

    for (int j = 0; j < bin.length(); j++)
      if (randomNumberGenerator(0.0f, 1.0f) < mutationRate) bin[j] = (bin[j] == '0') ? '1' : '0';

    _genome += decimalToHex(std::bitset<4>(bin).to_ulong());
  }

  parseGenome();
}

const std::string Genome::toString() { return _genome; }
const std::string Genome::toBinaryString() { return _binaryString; }
const std::vector<Gen> Genome::getGens() { return _gens; }
