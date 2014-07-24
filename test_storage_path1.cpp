#include "rumpelstiltskin.hpp"
#include <iostream>

int main(int argc,char **argv) {
  
  std::string secret1=rumpelstiltskin::randomsecret();
  std::string secret2=rumpelstiltskin::randomsecret();
  auto server1 = rumpelstiltskin::create_server(secret1);
  auto server2 = rumpelstiltskin::create_server(secret2);
  auto rootcap = rumpelstiltskin::pass2rootcap("knockknock");
  auto rootnode1 = server1[rootcap];
  auto rootnode2 = server2[rootcap];
  if (rootnode1.attenuated_cap() != rootnode2.attenuated_cap()) {
     std::cerr << "attenuation should be secret independent, its not, thats bad." << std::endl;
     return 1;
  }
  auto storage1 = rootnode1.storage();
  auto storage2 = rootnode2.storage();
  if (storage1.path() != storage2.path()) {
     std::cerr << "storage paths should be secret independent, its not, thats bad." << std::endl;
     return 2;
  }
  return 0;
};

