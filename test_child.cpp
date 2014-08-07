#include "rumpelstiltskin.hpp"
#include <iostream>

int main(int argc,char **argv) {
  std::string mysecret("PLZKHRQCPJYKNYKVKL6SN6T4LO5RKVSXCO46X26BKFDLB4LEJCEZXNSUQBOUX3RFIQOGPTUOM6KZ2DRXFG6QB3P5EN7K3FHHZUN2VFKE2MKQ4IHWKN2XRM7YC4YLLHFM2HVRZQYJUS7TJLGLE5YJ6RCIV46EFM6ECWG5L2MTXZFHIUOOMVNL3SPAEYFI7FHWGQEHUBJ7HU24M");
  auto server = rumpelstiltskin::create_server(mysecret);
  auto rootcap1 = rumpelstiltskin::pass2rootcap("Allice");
  auto rootcap2 = rumpelstiltskin::pass2rootcap("Bob");
  auto rootnode1=server[rootcap1];
  auto rootnode2=server[rootcap2];
  auto domainnode1 = rootnode1["Carol"];
  auto domainnode2 = rootnode2["Carol"];
  if (domainnode1.cap() == domainnode2.cap()) {
      std::cout << "Same child from different parents, this is very bad." << std::endl;
      return 1;
  }
  return 0;
};
