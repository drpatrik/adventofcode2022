#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <numeric>
#include <algorithm>

auto read_calories_file(const std::string& name) {
  std::vector<std::vector<int>> elfs;
  std::ifstream f(name);
  std::string str;

  elfs.emplace_back(std::vector<int>());
  while (std::getline(f, str)) {
    if (str.empty()) {
      elfs.emplace_back(std::vector<int>());
      continue;
    }
    auto& calories = elfs.back();
    calories.push_back(std::stoi(str));
  }
  return elfs;
}

int return_most_calories(const  std::vector<std::vector<int>>& elfs) {
  int sum = 0;

  for (const auto& elf : elfs) {
    sum = std::max(std::accumulate(elf.begin(), elf.end(), 0), sum);
  }
  return sum;
}

auto return_top_three(const  std::vector<std::vector<int>>& elfs) {
  std::vector<int> sums;

  for (const auto& elf : elfs) {
    sums.push_back(std::accumulate(elf.begin(), elf.end(), 0));
  }
  std::sort(sums.begin(), sums.end(), std::greater<int>());

  return std::vector<int>(sums.begin(), sums.begin() + std::min<int>(3, sums.size()));
}

void day_one() {
  auto elfs = read_calories_file("input_day1.txt");
  std::cout << "Day 1 - Part 1: " << return_most_calories(elfs) << std::endl;
  auto sums = return_top_three(elfs);
  std::cout << "Day 1 - Part 2: " << std::accumulate(sums.begin(), sums.end(), 0) << std::endl;
}
