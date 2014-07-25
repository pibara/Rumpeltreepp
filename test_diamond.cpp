#include "rumpelstiltskin.hpp"
#include <iostream>

int main(int argc,char **argv) {
  
  auto secret1=rumpelstiltskin::randomsecret();
  auto server1 = rumpelstiltskin::create_server(secret1);
  auto rootcap = rumpelstiltskin::pass2rootcap("knockknock");
  auto rootnode1 = server1[rootcap];
  auto attenuated_rootnode1 = rootnode1.attenuated();
  auto childnode1 = rootnode1["bob"];
  auto attenuated_childnode1 = childnode1.attenuated();
  auto childof_attenuatednode = attenuated_rootnode1["bob"];
  if (attenuated_childnode1.cap() != childof_attenuatednode.cap()) {
      std::cerr << "Attenuation of decomposition should yield the same result as decomposition of attenuation" << std::endl;
      return 1;
  }  
  return 0;
};
