#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <set>
#include <cassert>

struct Position {
  Position(int x, int y) : _x(x), _y(y) {}

  Position()  : _x(0), _y(0) {}

  bool operator< (const Position& p) const { return (_x < p._x) || (_x == p._x && _y < p._y); }

  int x() const { return _x; }

  int y() const { return _y; }

  int _x;
  int _y;
};

using VisitedPos = std::set<Position>;
using Motions = std::vector<std::pair<char, int>>;

template <typename T> int sgn(T val) { return (T(0) < val) - (val < T(0)); }

Position UpdateTail(const Position& head, const Position& tail) {
  const int dx = head.x() - tail.x();
  const int dy = head.y() - tail.y();

  Position new_tail = tail;

  if (abs(dx) > 1 || abs(dy) > 1) {
    new_tail._x += sgn(dx);
    new_tail._y += sgn(dy);
  }

  return new_tail;
}

const int kRopeLength = 9;

auto Simulation(const Motions& motions) {
  VisitedPos visited_short_rope;
  VisitedPos visited_long_rope;

  Position head = Position(0, 0);
  std::array<Position, kRopeLength> rope;

  for (const auto& m : motions) {
    auto [dir, steps] = m;

    for (int s = 0; s < steps; ++s) {
      switch (dir) {
        case 'R': head._x++; break;
        case 'L': head._x--; break;
        case 'U': head._y--; break;
        case 'D': head._y++; break;
        default: assert(false);
      }
      rope.front() = UpdateTail(head, rope.front());
      for (size_t i = 1; i < rope.size(); ++i) {
        rope.at(i) = UpdateTail(rope.at(i - 1), rope.at(i));
      }
      visited_short_rope.insert(rope.front());
      visited_long_rope.insert(rope.back());
    }
  }

  return std::make_pair(visited_short_rope.size(), visited_long_rope.size());
}

Motions ReadMotions(const std::string& name) {
  Motions motions;

  std::ifstream f(name);
  std::string line;

  while (std::getline(f, line)) {
    motions.push_back(std::make_pair(line.front(), std::stoi(std::string(line.begin() + 2, line.end()))));
  }

  return motions;
}

void day_nine() {
  auto motions = ReadMotions("input_files/input_day9.txt");

  auto [part1, part2] = Simulation(motions);

  std::cout << "Day 9 - Part 1: " << part1 << std::endl;
  std::cout << "Day 9 - Part 2: " << part2 << std::endl;
}
