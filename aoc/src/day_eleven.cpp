#include "utility/split.h"
#include <iostream>
#include <fstream>
#include <numeric>

const std::vector<std::function< size_t(size_t,size_t)>> kCalculateWorryLevels = {
  { [](size_t old, size_t) { return old * old; } },
  { [](size_t old, size_t var) { return old + var; } },
  { [](size_t old, size_t var) { return old * var; } }
};

const std::vector<std::string> kOperations = { "old", "+", "*" };

class Monkey {
 public:
  enum Operations { Square, Add, Multiply };

  explicit Monkey(int n) : _n(n) { _conditions.resize(2); }

  void GotItem(size_t item) { _items.push_back(item); }

  void AddItems(const std::vector<std::string>& items) {
    for (size_t i = 1; i < items.size(); ++i) {
      _items.push_back(std::stoi(items.at(i)));
    }
  }

  void AddOperations(const std::string& line) {
    _var = -1;
    if (line.find("old * old") != std::string::npos) {
      _op = Square;
    } else if (line.find("old *") != std::string::npos) {
      const auto tmp = utility::split(line);

      _op = Multiply;
      _var = std::stoi(tmp.at(tmp.size() - 1));

    } else if (line.find("old +") != std::string::npos) {
      const auto tmp = utility::split(line);

      _op = Add;
      _var = std::stoi(tmp.at(tmp.size() - 1));
      return;
    } else {
      assert(false);
    }
  }

  void AddDivisible(const std::vector<std::string>& divisible) { _divisible = std::stoi(divisible.at(divisible.size() - 1)); }

  void AddConditions(const std::vector<std::string>& cond) {
    if (cond.at(5) == "true:") {
      _conditions.at(1) = std::stoi(cond.at(9));
    } else  if (cond.at(5) == "false:") {
      _conditions.at(0) = std::stoi(cond.at(9));
    } else {
      assert(false);
    }
  }

  void ExecuteRound(std::vector<Monkey>& monkeys, size_t worry_level_divider, size_t common_multiple = 0) {
    if (_items.empty()) {
      return;
    }
    while(!_items.empty()) {
      auto item = _items.front();
      _items.erase(_items.begin());

      item = (kCalculateWorryLevels.at(_op))(item, _var == -1 ? item : _var);
      item /= worry_level_divider;
      item = common_multiple == 0 ? item : item % common_multiple;
      monkeys.at(_conditions.at(item %_divisible == 0)).GotItem(item);
      _times_inspecting++;
    }
  }

  int n() const { return _n; }

  size_t divisible() const { return _divisible; }

  size_t times_inspecting() const { return _times_inspecting; }

 private:
  int _n ;
  std::vector<size_t> _items;
  int _op = 0;
  int _var = 0;
  size_t _divisible = 0;
  std::vector<int> _conditions;
  size_t _times_inspecting = 0;
};

auto ParseMonkeys(const std::string& name) {
  std::vector<Monkey> monkeys;

  std::ifstream f(name);
  std::string line;

  size_t n = 0;
  while (std::getline(f, line)) {
    if (line.empty()) {
      continue;
    }
    std::getline(f, line);

    Monkey monkey(n);

    monkey.AddItems(utility::split(line, ":,"));
    std::getline(f, line);
    monkey.AddOperations(line);
    std::getline(f, line);
    monkey.AddDivisible(utility::split(line));
    std::getline(f, line);
    monkey.AddConditions(utility::split(line));
    std::getline(f, line);
    monkey.AddConditions(utility::split(line));
    monkeys.emplace_back(monkey);
    n++;
  }

  return monkeys;
}

size_t Part1() {
  auto monkeys = ParseMonkeys("input_files/input_day11.txt");

  for (int round = 0; round < 20; ++round) {
    for (auto& monkey : monkeys) {
      monkey.ExecuteRound(monkeys, 3);
    }
  }
  std::vector<size_t> inspections;

  std::transform(monkeys.begin(), monkeys.end(), std::back_inserter(inspections), [](const auto& monkey) { return monkey.times_inspecting(); });
  std::sort(inspections.rbegin(), inspections.rend());

  return inspections.at(0) * inspections.at(1);
}

size_t Part2() {
  auto monkeys = ParseMonkeys("input_files/input_day11.txt");
  auto common_multiple = std::accumulate(monkeys.begin(), monkeys.end(), 1, [](auto a, const auto& b) {return a * b.divisible(); });

  for (int round = 0; round < 10000; ++round) {
    for (auto& monkey : monkeys) {
      monkey.ExecuteRound(monkeys, 1, common_multiple);
    }
  }
  std::vector<size_t> inspections;

  std::transform(monkeys.begin(), monkeys.end(), std::back_inserter(inspections), [](const auto& monkey) { return monkey.times_inspecting(); });
  std::sort(inspections.rbegin(), inspections.rend());

  return inspections.at(0) * inspections.at(1);
}


void day_eleven() {
  std::cout << "Day 11 - Part 1: " << Part1() << std::endl;
  std::cout << "Day 11 - Part 2: " << Part2() << std::endl;
}
