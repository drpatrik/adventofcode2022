#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>

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
  std::ifstream f(name);
  std::vector<Section> sections;
  std::string str;

  while (std::getline(f, str)) {
    sections.emplace_back(get_section(str));
  }

  return sections;
}

std::pair<int, int> overlapping_assignments(const Section& section) {
  auto [l1,u1, l2, u2] = section;

  return std::make_pair(((l1 >= l2 && u1 <= u2) || (l2 >= l1 && u2 <= u1)), !(u1 < l2 || u2 < l1));
}

std::pair<int, int>  total_overlapping_assignments(const std::vector<Section>& sections) {
  int total_contained = 0;
  int total_overlapping = 0;

  for (const auto& section : sections) {
    auto [c, o] = overlapping_assignments(section);

    total_contained += c;
    total_overlapping += o;
  }

  return std::make_pair(total_contained, total_overlapping);
}

void day_four() {
  auto sections = read_sections("input_files/input_day4.txt");

  auto [total_contained, total_overlapping] = total_overlapping_assignments(sections);

  std::cout << "Day 4 - Part 1: " << total_contained << std::endl;
  std::cout << "Day 4 - Part 2: " << total_overlapping << std::endl;
}
