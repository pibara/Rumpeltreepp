#include "rumpelstiltskin.hpp"
#include <iostream>

int main(int argc,char **argv) {
  
  //Get a random secret, normaly this should be used only on installation of a tool using the lib.
  //The secret should than get stored somewhere secure for use whenever the server gets run.
  auto secret1=rumpelstiltskin::randomsecret();
  auto secret2=rumpelstiltskin::randomsecret();
  if (secret1 == secret2) {
     std::cerr << "random secrets are both the same, this is bad news" << std::endl;
     return 1;
  }
  auto server1 = rumpelstiltskin::create_server(secret1,secret1);
  auto server2 = rumpelstiltskin::create_server(secret2,secret2);
  auto rootcap = rumpelstiltskin::pass2rootcap("knockknock");
  auto rootnode1 = server1[rootcap];
  auto rootnode2 = server2[rootcap];
  if (rootnode1.attenuated_cap() != rootnode2.attenuated_cap()) {
     std::cerr << "Different attenuated root nodes for different secrets, this is not OK!" << std::endl;
     return 2;
  }
  auto childnode1 = rootnode1["bob"];
  auto childnode2 = rootnode2["bob"];
  if (childnode1.cap() == childnode2.cap()) {
      std::cerr << "Same child nodes for different secrets, this is not OK!" << std::endl;
      return 3;
  }
  auto storage1 = rootnode1.storage();
  auto storage2 = rootnode2.storage();
  if (storage1.path() == storage2.path()) {
       std::cerr << "Different storage paths for different cloud secrets, this is not OK!" << std::endl;
       return 4;
  }
  return 0;
};
