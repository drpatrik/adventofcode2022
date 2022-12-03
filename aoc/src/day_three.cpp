#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>

struct Backpack {
  Backpack(const std::string& c1, const std::string& c2) : c1(c1), c2(c2) {}
  std::string c1;
  std::string c2;
};

int calculate_priority(const std::string& str) {
  char ch = str.at(0);

  return (std::isupper(ch) ? int(ch) - 38 : int(ch) - 96);
}

auto read_backpacks_part1(const std::string& name) {
  std::vector<Backpack> backbacks;
  std::ifstream f(name);
  std::string str;

  while (std::getline(f, str)) {
    auto c1 = std::string(str.begin(), str.begin() + (str.size() >> 1));
    auto c2 = std::string(str.begin() + (str.size() >> 1), str.end());

    std::sort(c1.begin(), c1.end());
    std::sort(c2.begin(), c2.end());

    backbacks.emplace_back(c1, c2 );
  }

  return backbacks;
}

int calculate_total_priority(const std::vector<Backpack>& backpacks) {
  int priority_sum = 0;

  for (const auto& bp : backpacks ) {
    std::string intersection;

    std::set_intersection(bp.c1.begin(), bp.c1.end(), bp.c2.begin(), bp.c2.end(), std::back_inserter(intersection));

    if (intersection.empty()) {
      continue;
    }
    priority_sum += calculate_priority(intersection);
  }

  return priority_sum;
}

auto read_backpacks_part2(const std::string& name) {
  std::vector<std::string> backbacks;
  std::ifstream f(name);
  std::string str;

  while (std::getline(f, str)) {
    std::sort(str.begin(), str.end());
    backbacks.emplace_back(str);
  }

  return backbacks;
}

auto group_backpacks(const std::vector<std::string>& backpacks) {
  std::vector<std::vector<std::string>> grouped_backpacks;

  for (size_t c = 0; c < backpacks.size(); ++c) {
    if (c % 3 == 0) {
      grouped_backpacks.emplace_back(std::vector<std::string>());
    }
    grouped_backpacks.back().emplace_back(backpacks.at(c));
  }

  return grouped_backpacks;
}

int calculate_badge_score(const std::vector<std::vector<std::string>>& group_backpacks) {
  int badge_score = 0;

  for (const auto& group : group_backpacks) {
    const auto& g1 = group.at(0);
    const auto& g2 = group.at(1);
    const auto& g3 = group.at(2);

    std::string first_intersection;
    std::set_intersection(g1.begin(), g1.end(), g2.begin(), g2.end(), std::back_inserter(first_intersection));
    std::string second_intersection;
    std::set_intersection(first_intersection.begin(), first_intersection.end(), g3.begin(), g3.end(), std::back_inserter(second_intersection));
    badge_score += calculate_priority(second_intersection);
  }

  return badge_score;
}

void day_three() {
  const auto backpacks_p1 = read_backpacks_part1("input_files/input_day3.txt");

  std::cout << "Day3 - Part 1: " << calculate_total_priority(backpacks_p1) << std::endl;

  const auto backpacks_p2 = read_backpacks_part2("input_files/input_day3.txt");
  const auto grouped_backpacks = group_backpacks(backpacks_p2);
  std::cout << "Day3 - Part 2: " << calculate_badge_score(grouped_backpacks) << std::endl;
}
