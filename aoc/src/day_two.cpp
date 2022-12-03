#include <iostream>
#include <vector>
#include <fstream>
#include <map>

const std::map<std::string, int> kOutcomes = {
  { "RR", 4 }, // Draw 3 + 1
  { "PP", 5 }, // Draw 3 + 2
  { "SS", 6 }, // Draw 3 + 3
  { "RP", 8 }, // Win 6 + 2
  { "PR", 1 }, // Loose 0 + 1
  { "SR", 7 }, // Win 6 + 1
  { "RS", 3 }, // Loose 0 + 3
  { "SP", 2 }, // Loose 0 + 2
  { "PS", 9 } // Win 6 + 3
};

enum Strategy { Loose, Draw, Win };

const std::map<Strategy, std::map<std::string, std::string>> kStrategies = {
  { Loose, { { "R", "S" },  { "P", "R" }, { "S", "P" } } },
  { Draw, { { "R", "R" },  { "P", "P" },  { "S", "S" } } },
  { Win, {  { "R", "P" },  { "P", "S" },  { "S", "R" } } }
};

auto read_strategy_file_part1(const std::string& name) {
  std::vector<std::string> strategies;
  std::ifstream f(name);
  std::string str;
  std::string strategy;

  while (std::getline(f, str)) {
    strategy.clear();
    for (const auto ch : str) {
      switch (ch) {
        case 'A' : strategy += 'R'; break;
        case 'B' : strategy += 'P'; break;
        case 'C' : strategy += 'S'; break;
        case 'X' : strategy += 'R'; break;
        case 'Y' : strategy += 'P'; break;
        case 'Z' : strategy += 'S'; break;
      }
    }
    strategies.push_back(strategy);
  }

  return strategies;
}

auto read_strategy_file_part2(const std::string& name) {
  std::vector<std::string> strategies;
  std::ifstream f(name);
  std::string str;
  std::string strategy;

  while (std::getline(f, str)) {
    strategy.clear();
    for (const auto ch : str) {
      switch (ch) {
        case 'A' : strategy += 'R'; break;
        case 'B' : strategy += 'P'; break;
        case 'C' : strategy += 'S'; break;
        case 'X' : strategy += kStrategies.at(Loose).at(strategy); break;
        case 'Y' : strategy += kStrategies.at(Draw).at(strategy); break;
        case 'Z' : strategy += kStrategies.at(Win).at(strategy);; break;
      }
    }
    strategies.push_back(strategy);
  }

  return strategies;
}

int calculate_total_score(const std::vector<std::string>& strategies) {
  int sum = 0;

  for (const auto& strategy : strategies) {
    sum +=  kOutcomes.at(strategy);
  }

  return sum;
}

void day_two() {
  auto strategies = read_strategy_file_part1("input_files/input_day2.txt");
  std::cout << "Day2 - Part 1: " << calculate_total_score(strategies) << std::endl;

  strategies = read_strategy_file_part2("input_files/input_day2.txt");
  std::cout << "Day2 - Part 2: " << calculate_total_score(strategies) << std::endl;
}
