#include "rumpelstiltskin.hpp"
#include <iostream>

int main(int argc,char **argv) {
  std::string mysecret("PLZKHRQCPJYKNYKVKL6SN6T4LO5RKVSXCO46X26BKFDLB4LEJCEZXNSUQBOUX3RFIQOGPTUOM6KZ2DRXFG6QB3P5EN7K3FHHZUN2VFKE2MKQ4IHWKN2XRM7YC4YLLHFM2HVRZQYJUS7TJLGLE5YJ6RCIV46EFM6ECWG5L2MTXZFHIUOOMVNL3SPAEYFI7FHWGQEHUBJ7HU24M");
  auto server = rumpelstiltskin::create_server(mysecret);
  auto rootcap1 = rumpelstiltskin::pass2rootcap("Allice");
  auto rootnode1=server[rootcap1];
  auto childnode1 = rootnode1["Bob"];
  auto childnode2 = rootnode1["Carol"];
  if (childnode1.cap() == childnode2.cap()) {
      std::cout << "Same child from different name, this is very bad." << std::endl;
      return 1;
  }
  return 0;
};
