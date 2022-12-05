#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <numeric>
#include <type_traits>

enum class CrateMoverType { CM9000, CM9001 };

using Stack = std::vector<char>;
using CargoHold = std::vector<Stack>;
using Moves = std::tuple<int, int, int>;
using Rearrangement = std::vector<Moves>;

const CargoHold kCargoHoldTemplate = {
  { 'L','C', 'G', 'M', 'Q' },
  { 'G','H','F','T','C','L','D','R'},
  { 'R','W','T','M','N','F','J','V'},
  { 'P','Q','V','D','F','J'},
  { 'T','B','L','S','M','F','N'},
  { 'P','D','C','H','V','N','R'},
  { 'T','C','H'},
  { 'P','H','N','Z','V','J','S','G'},
  { 'G','H','F','Z'}
};

const CargoHold kCargoHoldTestTemplate = {
  { 'N', 'Z' },
  { 'D', 'C', 'M'},
  { 'P' }
};

Moves GetMoves(const std::string& line) {
  std::string num;
  std::vector<int> moves;

  for (auto ch : line) {
    switch (ch) {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        num += ch;
        break;
      case ' ':
        if (num.size() > 0) {
          moves.push_back(std::stoi(num));
        }
        num.clear();
        break;
    }
  }
  moves.push_back(std::stoi(num));
  return { moves.at(0), moves.at(1), moves.at(2) };
}

template <CrateMoverType cm_type>
auto CrateMover(const CargoHold& cargo_hold_template, const Rearrangement& rearrangements) {
  CargoHold cargo_hold(cargo_hold_template);

  for (const auto& moves : rearrangements) {
    // move n from s1 to s2
    auto [n, s1, s2] = moves;

    Stack& from = cargo_hold.at(s1 - 1);
    Stack& to = cargo_hold.at(s2 - 1);

    std::vector<char> slice(from.begin(), from.begin() + n);
    from.erase(from.begin(), from.begin() + n);

    if constexpr(cm_type == CrateMoverType::CM9000) {
      to.insert(to.begin(), slice.rbegin(), slice.rend());
    } else {
      to.insert(to.begin(), slice.begin(), slice.end());
    }
  }

  return std::accumulate(cargo_hold.begin(), cargo_hold.end(), std::string(""), [](const auto& a, const auto& b) { return a + b.front(); });
}

auto read_file(const std::string& name) {
  std::string line;
  std::ifstream f(name);

  while (std::getline(f, line)) {
    if (!line.empty()) {
      continue;
    }
    break;
  }
  Rearrangement rearrangements;

  while (std::getline(f, line)) {
    rearrangements.push_back(GetMoves(line));
  }

  return rearrangements;
}

void day_five() {
  auto strategies = read_file("input_files/input_day5.txt");

  std::cout << "Day 5 - Part 1: " << CrateMover<CrateMoverType::CM9000>(kCargoHoldTemplate, strategies) << std::endl;
  std::cout << "Day 5 - Part 2: " << CrateMover<CrateMoverType::CM9001>(kCargoHoldTemplate, strategies) << std::endl;
}
