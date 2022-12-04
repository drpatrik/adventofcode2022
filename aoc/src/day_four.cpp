#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <numeric>
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
  std::ifstream f(name);
  std::vector<Section> sections;
  std::string str;

  while (std::getline(f, str)) {
    sections.emplace_back(get_section(str));
  }

  return sections;
}

std::vector<int> expand_range(int l, int u) {
  std::vector<int> range;

  for (int i = l; i <= u;i++) {
    range.push_back(i);
  }

  return range;
}

std::pair<int, int> overlapping_assignments(const Section& section) {
  auto r1 = expand_range(std::get<0>(section), std::get<1>(section));
  auto r2 = expand_range(std::get<2>(section), std::get<3>(section));

  std::vector<int> i_section;
  std::set_intersection(r1.begin(), r1.end(), r2.begin(), r2.end(), std::back_inserter(i_section));

  return std::make_pair(i_section.size() == r1.size() || i_section.size() == r2.size(), i_section.size() > 0);
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
