#include "rumpelstiltskin.hpp"
#include <iostream>

int main(int argc,char **argv) {
  
  //Get a random secret, normaly this should be used only on installation of a tool using the lib.
  //The secret should than get stored somewhere secure for use whenever the server gets run.
  sec::string secret=rumpelstiltskin::randomsecret();
  std::cout << "secret=" << secret << std::endl;
  //Create the core rumpelstiltskin server object using the secret(s). Here we assume local usage, 
  //for use of cloud storage the create_server function takes a second secret.
  auto server = rumpelstiltskin::create_server(secret);
  //When creating a brand new tree we need to create a root cap first. This function does this
  //securely random using crypto library primitives. Alternatively it could be done with a password.
  sec::string rootcap=rumpelstiltskin::randomrootcap();
  std::cout << "rootcap 1: " << rootcap << std::endl;
  rootcap = rumpelstiltskin::pass2rootcap("knockknock");
  std::cout << "rootcap 2: " << rootcap << std::endl;
  //Create a root node from the root cap.
  auto rootnode = server[rootcap];
  std::cout << "  unattenuated : " << rootnode.unattenuated_cap() << std::endl;
  std::cout << "  attenuated   : " << rootnode.attenuated_cap() << std::endl;
  std::cout << "  main         : " << rootnode.cap() << std::endl;
  auto storage = rootnode.storage();
  std::cout << "  storage_path : " << storage.path() << std::endl;
  uint8_t const * const key=storage.crypto_key();
  bool attenuated = rootnode.is_attenuated();
  //Create an attenuated version of the root node
  auto attenuatedrootnode = rootnode.attenuated();
  //Create a child node of the unatenuated root node
  auto childnode = rootnode["bob"];
  //Create a child node of the attenuated root node
  auto attenuatedchildnode1 = attenuatedrootnode["bob"];
  //Create an atenuated version of the unatenuated child node
  auto attenuatedchildnode2 = childnode.attenuated();
  //attenuation of decomposition should equate decomposition of attenuation.
  auto storage1 = attenuatedchildnode1.storage();
  auto storage2 = attenuatedchildnode2.storage();
  std::cout << "1: location " << storage1.path() << std::endl;
  std::cout << "2: location " << storage2.path() << std::endl;
  std::cout << "1: cap " << attenuatedchildnode1.cap() << std::endl;
  std::cout << "2: cap " << attenuatedchildnode2.cap() << std::endl;
  auto client = rumpelstiltskin::create_client();
  sec::string as1 = client.attenuate(rootcap);
  std::cout << "client side attenuated cap: " << as1 << std::endl;
  return 0;
};
