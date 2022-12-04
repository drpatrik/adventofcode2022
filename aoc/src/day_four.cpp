#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>

typedef std::tuple<int, int, int, int> Section;

inline Section get_section(const std::string& str) {
  std::string token;
  std::vector<int> range;

  for (const auto ch : str) {
    switch (ch) {
      case ',': range.push_back(std::stoi(token)); token.clear(); break;
      case '-': range.push_back(std::stoi(token)); token.clear(); break;
      default:
        token += ch;
    }
  }
  range.push_back(std::stoi(token));

  return { range.at(0), range.at(1), range.at(2), range.at(3) };
}

auto read_sections(const std::string& name) {
  std::string str;
  std::ifstream f(name);
  std::vector<Section> sections;

  while (std::getline(f, str)) {
    sections.emplace_back(get_section(str));
  }

  return sections;
}

int fully_contains(const Section& section) {
  auto [l1,u1, l2, u2] = section;

  return  ((l1 >= l2 && u1 <= u2) || (l2 >= l1 && u2 <= u1));
}

int total_contained_assigmeents(const std::vector<Section>& sections) {
  int sum = 0;

  for (const auto& s : sections) {
    sum += fully_contains(s);
  }

  return sum;
}

std::vector<int> expand_range(int l, int u) {
  std::vector<int> range;

  for (int i = l; i <= u;i++) {
    range.push_back(i);
  }

  return range;
}

int overlapping_assignments(const Section& section) {
  auto [l1,u1, l2, u2] = section;
  auto r1 = expand_range(l1, u1);
  auto r2 = expand_range(l2, u2);

  std::vector<int> intersection;
  std::set_intersection(r1.begin(), r1.end(), r2.begin(), r2.end(), std::back_inserter(intersection));

  return (intersection.size() > 0);
}

int total_overlapping_assignments(const std::vector<Section>& sections) {
  int sum = 0;

  for (const auto& s : sections) {
    sum += overlapping_assignments(s);
  }

  return sum;
}

void day_four() {
  auto sections = read_sections("input_files/input_day4.txt");

  std::cout << "Day 4 - Part 1: " << total_contained_assigmeents(sections) << std::endl;
  std::cout << "Day 4 - Part 2: " << total_overlapping_assignments(sections) << std::endl;
}
