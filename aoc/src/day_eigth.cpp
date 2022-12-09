#include <iostream>
#include <fstream>
#include <vector>

using Forest = std::vector<std::vector<int>>;

inline int get_tree(int x, int y, const Forest& forest) { return forest.at(y).at(x); }

template<bool CalculateDistance = false>
int LookUp(int x_pos, int y_pos, const Forest& forest) {
  int height = get_tree(x_pos, y_pos, forest);
  int distance = 0;

  for (int y = y_pos - 1; y >= 0; --y) {
    if (get_tree(x_pos, y, forest) >= height) {
      return distance + 1;;
    }
    CalculateDistance && distance++;
  }

  return distance;;
}

template<bool CalculateDistance = false>
int LookDown(int x_pos, int y_pos, const Forest& forest) {
  int height = get_tree(x_pos, y_pos, forest);
  int distance = 0;

  for (size_t y = y_pos + 1; y < forest.size(); ++y) {
    if (get_tree(x_pos, y, forest) >= height) {
      return distance + 1;
    }
    CalculateDistance && distance++;
  }

  return distance;;
}

template<bool CalculateDistance = false>
int LookLeft(int x_pos, int y_pos, const Forest& forest) {
  int height = get_tree(x_pos, y_pos, forest);
  int distance = 0;

  for (int x = x_pos - 1; x >= 0; --x) {
    if (get_tree(x, y_pos, forest) >= height) {
      return distance + 1;
    }
     CalculateDistance && distance++;
  }

  return distance;;
}

template<bool CalculateDistance = false>
int LookRight(int x_pos, int y_pos, const Forest& forest) {
  int height = get_tree(x_pos, y_pos, forest);
  int distance = 0;

  for (size_t x = x_pos + 1; x < forest.at(y_pos).size(); ++x) {
    if (get_tree(x, y_pos, forest) >= height) {
      return distance + 1;
    }
    CalculateDistance && distance++;
  }

  return distance;
}

int FindVisibleTrees(const Forest& forest) {
  int visible = 0;

  for (size_t y_pos = 1; y_pos <= forest.size() - 2; ++y_pos) {
    for (size_t x_pos = 1; x_pos <= forest.at(y_pos).size() - 2; ++x_pos) {
      auto u = LookUp(x_pos, y_pos, forest);
      auto d = LookDown(x_pos, y_pos, forest);
      auto l = LookLeft(x_pos, y_pos, forest);
      auto r = LookRight(x_pos, y_pos, forest);

      if (u + d + l + r != 4) {
        visible++;
      }
    }
  }

  return visible + (forest.size() * 2) + ((forest.at(0).size() - 2) * 2);
}

int FindHighestScenicScore(const Forest& forest) {
  int max = 0;

  for (size_t y_pos = 1; y_pos <= forest.size() - 2; ++y_pos) {
    for (size_t x_pos = 1; x_pos <= forest.at(y_pos).size() - 2; ++x_pos) {
      auto u = LookUp<true>(x_pos, y_pos, forest);
      auto d = LookDown<true>(x_pos, y_pos, forest);
      auto l = LookLeft<true>(x_pos, y_pos, forest);
      auto r = LookRight<true>(x_pos, y_pos, forest);

      max = std::max(max, u * d * l * r);
    }
  }

  return max;
}

Forest ReadForest(const std::string& name) {
  Forest forest;

  std::string line;
  std::ifstream f(name);

  while (std::getline(f, line)) {
    forest.push_back(std::vector<int>());

    for (auto ch : line) {
      forest.back().push_back(ch);
    }
  }

  return forest;
}

void day_eight() {
  auto forest = ReadForest("input_files/input_day8.txt");

  std::cout << "Day 8 - Part 1: " << FindVisibleTrees(forest) << std::endl;
  std::cout << "Day 8 - Part 2: " << FindHighestScenicScore(forest) << std::endl;
}
