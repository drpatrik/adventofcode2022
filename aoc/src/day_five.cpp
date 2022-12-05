#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>

using Stack = std::vector<char>;
using CargoHold = std::vector<Stack>;
using Moves = std::tuple<int, int, int>;
using Rearrangement = std::vector<Moves>;

const CargoHold cargo_hold_template = {
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

const CargoHold cargo_hold_test_template = {
  { 'N', 'Z' },
  { 'D', 'C', 'M'},
  { 'P' }
};

void PrintMoves(const Moves moves) {
  auto [n, s1, s2] = moves;

  std::cout << "Move " << n << " from " << s1 << " to " << s2 << std::endl;
}

void PrintCargoHold(const CargoHold& cargo_hold) {
  for (const auto& stack : cargo_hold) {
    for (const auto crate : stack) {
      std::cout << crate;
    }
    std::cout << std::endl;
  }
  std::cout << "----" << std::endl;
}

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

auto CrateMover9000(const CargoHold& cargo_hold_template, const Rearrangement& rearrangements) {
  std::string top_crates;
  CargoHold cargo_hold(cargo_hold_template);

  for (const auto& moves : rearrangements) {
    auto [n, s1, s2] = moves;

    Stack& from = cargo_hold.at(s1 - 1);
    Stack& to = cargo_hold.at(s2 - 1);

    std::vector<char> slice(from.begin(), from.begin() + n);
    from.erase(from.begin(), from.begin() + n);
    to.insert(to.begin(), slice.rbegin(), slice.rend());
  }
  for (const auto& stack : cargo_hold) {
    top_crates += stack.front();
  }

  return top_crates;
}

auto CrateMover9001(const CargoHold& cargo_hold_template, const Rearrangement& rearrangements) {
  std::string top_crates;
  CargoHold cargo_hold(cargo_hold_template);

  for (const auto& moves : rearrangements) {
    // move n from s1 to s2
    auto [n, s1, s2] = moves;

    Stack& from = cargo_hold.at(s1 - 1);
    Stack& to = cargo_hold.at(s2 - 1);

    std::vector<char> slice(from.begin(), from.begin() + n);
    from.erase(from.begin(), from.begin() + n);
    to.insert(to.begin(), slice.begin(), slice.end());
  }
  for (const auto& stack : cargo_hold) {
    top_crates += stack.front();
  }

  return top_crates;
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

  std::cout << "Day 5 - Part 1: " << CrateMover9000(cargo_hold_template, strategies) << std::endl;
  std::cout << "Day 5 - Part 2: " << CrateMover9001(cargo_hold_template, strategies) << std::endl;
}
