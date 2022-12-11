#include <iostream>
#include <fstream>
#include <vector>

const int kRows = 6;
const int kCols = 40;
const int kSpriteWidth = 3;

using InstructionPipeline = std::vector<std::pair<int, int>>;

InstructionPipeline ReadInstructions(const std::string& name) {
  InstructionPipeline pipeline;

  std::ifstream f(name);
  std::string line;
  int cycle = 1;

  while (std::getline(f, line)) {
    const int kParamStart = 5;

    auto it = line.find("addx ");

    if (it != std::string::npos) {
      pipeline.push_back(std::make_pair(cycle, 0));
      cycle++;
      pipeline.push_back(std::make_pair(cycle, std::stoi(std::string(line.begin() + kParamStart, line.end()))));
    } else {
      pipeline.push_back(std::make_pair(cycle,  0));
    }
    cycle++;
  }

  return pipeline;
}

int CalculateTotalStrength(const InstructionPipeline& pipeline) {
  int x = 1;
  int total_signal_strength = 0;

  for (const auto& i : pipeline) {
    auto [cycle, reg] = i;

    if (cycle % 40 == 20) {
      total_signal_strength += cycle * x;
    }
    x += reg;
  }
  return total_signal_strength;
}

char get_pixel(int cycle, int x) {
  int current_column = (cycle - 1) % kCols;

  return  (std::abs(current_column - x) <= kSpriteWidth >> 1) ? '#' : ' ';
}

void DrawScreen(const InstructionPipeline& pipeline) {
  int x = 1;
  std::vector<char> screen(kRows * kCols, ' ');

  for (const auto& i : pipeline) {
    auto [cycle, reg] = i;

    screen[cycle - 1] = get_pixel(cycle, x);
    x+= reg;
  }
  for (size_t i = 0; i < screen.size(); ++i) {
    std::cout << screen.at(i);
    if ((i + 1) % kCols == 0) {
      std::cout << std::endl;
    }
  }
  std::cout << std::endl;
}

void day_ten() {
  const InstructionPipeline pipeline = ReadInstructions("input_files/input_day10.txt");

  std::cout << "Day 1 - Part 1: " << CalculateTotalStrength(pipeline) << std::endl;
  std::cout << "Day 2 - Part 2: " << std::endl;
  DrawScreen(pipeline);
}
