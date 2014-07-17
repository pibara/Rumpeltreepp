#include "rumpelstiltskin.hpp"
#include <iostream>

int main(int argc,char **argv) {
  std::string rootcap=rumpelstiltskin::pass2rootcap("rumpelstiltskin");
  auto server = rumpelstiltskin::create_server("justtesting");
  auto rootnode = server[rootcap];
  auto attenuatedrootnode = rootnode.attenuated();
  auto childnode = rootnode["bob"];
  auto attenuatedchildnode1 = attenuatedrootnode["bob"];
  auto attenuatedchildnode2 = childnode.attenuated();
  std::cout << "1: " << attenuatedchildnode1.location() << std::endl;
  std::cout << "2: " << attenuatedchildnode2.location() << std::endl;
  return 0;
};
