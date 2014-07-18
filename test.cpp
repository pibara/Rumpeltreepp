#include "rumpelstiltskin.hpp"
#include <iostream>

int main(int argc,char **argv) {
  //Get a random secret, normaly this should be used only on installation of a tool using the lib.
  //The secret should than get stored somewhere secure for use whenever the server gets run.
  std::string secret=rumpelstiltskin::randomsecret();
  //Create the core rumpelstiltskin server object using the secret(s). Here we assume local usage, 
  //for use of cloud storage the create_server function takes a second secret.
  auto server = rumpelstiltskin::create_server(secret);
  //When creating a brand new tree we need to create a root cap first. This function does this
  //securely random using crypto library primitives. Alternatively it could be done with a password.
  std::string rootcap=rumpelstiltskin::randomrootcap();
  //Create a root node from the root cap.
  auto rootnode = server[rootcap];
  //Create an attenuated version of the root node
  auto attenuatedrootnode = rootnode.attenuated();
  //Create a child node of the unatenuated root node
  auto childnode = rootnode["bob"];
  //Create a child node of the attenuated root node
  auto attenuatedchildnode1 = attenuatedrootnode["bob"];
  //Create an atenuated version of the unatenuated child node
  auto attenuatedchildnode2 = childnode.attenuated();
  //attenuation of decomposition should equate decomposition of attenuation.
  std::cout << "1: location " << attenuatedchildnode1.location() << std::endl;
  std::cout << "2: location " << attenuatedchildnode2.location() << std::endl;
  std::cout << "1: cap " << attenuatedchildnode1.rocap() << std::endl;
  std::cout << "1: cap " << attenuatedchildnode1.rocap() << std::endl;
  return 0;
};
