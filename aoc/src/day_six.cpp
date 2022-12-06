#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <type_traits>

int FindStartOfPacket(std::istream& stream, size_t length) {
  char ch;
  int pos = 0;
  std::string buffer;

  while (stream.get(ch)) {
    pos++;
    if (buffer.find(ch) != std::string::npos) {
      buffer.erase(buffer.begin(), buffer.begin() + buffer.find(ch) + 1);
    }
    buffer += ch;
    if (buffer.size() == length) {
      return pos;
    }
  }

  return -1;
}

void day_six() {
  std::ifstream f("input_files/input_day6.txt");

  std::cout << "Day 6 - Part 1: " << FindStartOfPacket(f, 4) << std::endl;
  f.seekg (0, f.beg);
  std::cout << "Day 6 - Part 2: " << FindStartOfPacket(f, 14) << std::endl;
}
