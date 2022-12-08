#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>

enum class FileType { FILE, DIRECTORY };
enum class Token { FILE, DIRECTORY, LS, CD, ERROR };

class FileNode {
 public:
  explicit FileNode(const std::string& name) : _file_type(FileType::DIRECTORY), _name(name), _size(0) {}
  FileNode(const std::string& name, int size) : _file_type(FileType::FILE), _name(name), _size(size) {}

  FileType _file_type;
  std::string _name;
  int _size;
  FileNode* _prev = nullptr;
  std::vector<FileNode *> _children;
  int _node_size = 0;
};

FileNode* AddDirectory(FileNode* node, const std::string& name) {
  if (nullptr == node) {
    return new FileNode(name);
  }
  auto it = std::find_if(node->_children.begin(), node->_children.end(), [&](const auto& a) { return name == a->_name; });

  if (it != node->_children.end()) {
    return *it;
  }
  auto new_node = new FileNode(name);
  new_node->_prev = node;
  node->_children.push_back(new_node);

  return new_node;
}

void AddFile(FileNode* node, const std::string& name, int size) {
    node->_children.push_back(new FileNode(name, size));
    node->_children.back()->_prev = node;
}

std::pair<int, std::string> ParseFileToken(const std::string& line) {
  auto pos = line.find(" ");

  if (std::string::npos == pos) {
    std::cout << "error" << std::endl;
    exit(0);
  }
  return std::make_pair(std::stoi(line.substr(0, pos)), line.substr(pos + 1, line.size()));
}

std::pair<Token, std::string> ParseTerminalOutput(const std::string& line) {
    if (line[0] != '$') {
      if (line.find("dir") != std::string::npos) {
        return std::make_pair(Token::DIRECTORY, std::string(line.begin() + 4, line.end()));
      }
      return std::make_pair(Token::FILE, std::string(line.begin(), line.end()));
    }
    auto pos = line.find("ls");

    if (pos != std::string::npos) {
      return std::make_pair(Token::LS, std::string(line.begin() + 4, line.end()));
    }
    pos = line.find("cd");

    if (pos != std::string::npos) {
      return std::make_pair(Token::CD, std::string(line.begin() + 5, line.end()));
    }

    return std::make_pair(Token::ERROR, "");
}

void update_directory_sizes(FileNode* node) {
  if (FileType::FILE == node->_file_type) {
    node->_prev->_node_size += node->_size;
    return;
  }
  for (auto chld : node->_children) {
    update_directory_sizes(chld);
    node->_node_size += chld->_node_size;
  }
}

FileNode* ParseFileSystem() {
  std::ifstream f("input_files/input_day7.txt");
  std::string line;

  FileNode* root = nullptr;
  FileNode* current = nullptr;

  while (std::getline(f, line)) {
    auto [token, param] = ParseTerminalOutput(line);

    switch (token) {
      case Token::FILE: {
        auto [size, name] = ParseFileToken(line);
        AddFile(current, name, size);
        break;
      }
      case Token::DIRECTORY:
        AddDirectory(current, param);
        break;
      case Token::LS:
        break;
      case Token::CD:
        if (".." == param) {
          if (current->_prev != nullptr) {
            current = current->_prev;
          }
        } else {
          current = AddDirectory(current, param);
          if (nullptr == root) {
            root = current;
          }
        }
        break;
      case Token::ERROR:
        std::cout << "error" << std::endl;
        exit(0);
        break;
      default:
        std::cout << "unknown token" << std::endl;
        exit(0);
    }
  }
  update_directory_sizes(root);

  return root;
}

void get_directory_sizes(const FileNode* node, std::vector<int>& sizes) {
  if (node->_file_type == FileType::FILE) {
    return;
  }
  sizes.push_back(node->_node_size);
  for (auto chld : node->_children) {
    get_directory_sizes(chld, sizes);
  }

  return;
}

int Part1(const FileNode* root) {
  std::vector<int> sizes, total_size_of_max_100000;

  get_directory_sizes(root, sizes);
  std::copy_if (sizes.begin(), sizes.end(), std::back_inserter(total_size_of_max_100000), [](int size){return size <= 100000; });
  return std::accumulate(total_size_of_max_100000.begin(), total_size_of_max_100000.end(), 0);
}

int Part2(const FileNode *root) {
  const int kTotalDiskSpace = 70000000;
  const int kSpaceNeeded = 30000000;

  std::vector<int> sizes;

  get_directory_sizes(root, sizes);
  std::sort(sizes.begin(), sizes.end());

  const int space_left = kTotalDiskSpace - root->_node_size;

  int smallest_fit = kTotalDiskSpace;

  for (auto size : sizes) {
    if (size - int(kSpaceNeeded - space_left) >= 0) {
      smallest_fit = std::min(smallest_fit, size);
    }
  }
  return smallest_fit;
}

void day_seven() {
   auto root = ParseFileSystem();
   std::cout << "Day 7 - Part 1: " << Part1(root) << std::endl;
   std::cout << "Day 7 - Part 2: " << Part2(root) << std::endl;
}
