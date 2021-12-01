#include <parser.hpp>


int main() {
  Student st;
  auto p = parse_to_vec("../json/file1.json");
  print(p,std::cout);
}