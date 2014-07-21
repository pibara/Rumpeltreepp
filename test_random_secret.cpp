#include "rumpelstiltskin.hpp"
#include <iostream>

int main(int argc,char **argv) {
  
  //Get a random secret, normaly this should be used only on installation of a tool using the lib.
  //The secret should than get stored somewhere secure for use whenever the server gets run.
  sec::string secret1=rumpelstiltskin::randomsecret();
  sec::string secret2=rumpelstiltskin::randomsecret();
  if (secret1 == secret2) {
     std::cerr << "random secrets are both the same, this is bad news" << std::endl;
     return 1;
  }
  return 0;
};
