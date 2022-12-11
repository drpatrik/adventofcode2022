#include <vector>
#include <string>
#include <iostream>

namespace utility {

inline std::vector<std::string> split(const std::string& str, const std::string& delim = " ") {
  std::vector<std::string> tokens;

  auto tmp = str;

  while (!tmp.empty()) {
    auto it = tmp.find_first_of(delim, 0);

    if (it == std::string::npos) {
      tokens.push_back(tmp);
      break;
    }
    tokens.push_back(std::string(tmp.begin(), tmp.begin() + it));
    tmp.erase(tmp.begin(), tmp.begin() + it + 1);
  }

  return tokens;
}

} // namespace
