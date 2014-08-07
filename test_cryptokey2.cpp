#include "rumpelstiltskin.hpp"
#include <iostream>

int main(int argc,char **argv) {
  std::string mysecret("PLZKHRQCPJYKNYKVKL6SN6T4LO5RKVSXCO46X26BKFDLB4LEJCEZXNSUQBOUX3RFIQOGPTUOM6KZ2DRXFG6QB3P5EN7K3FHHZUN2VFKE2MKQ4IHWKN2XRM7YC4YLLHFM2HVRZQYJUS7TJLGLE5YJ6RCIV46EFM6ECWG5L2MTXZFHIUOOMVNL3SPAEYFI7FHWGQEHUBJ7HU24M");
  auto server = rumpelstiltskin::create_server(mysecret);
  auto rootcap1 = rumpelstiltskin::pass2rootcap("Allice");
  auto rootcap2 = rumpelstiltskin::pass2rootcap("Bob");
  auto rootnode1=server[rootcap1];  
  auto rootnode2=server[rootcap2];
  auto storage1 = rootnode1.storage();
  auto storage2 = rootnode2.storage();
  bool allsame = true;
  uint8_t const *key1=storage1.crypto_key();
  uint8_t const *key2=storage2.crypto_key();
  for (int i=0;i<32;i++) {
     if (key1[i] != key2[i]) {
        allsame = false;
     }
  }
  if (allsame) {
      std::cout << "Crypto key for different rootcap is the same. This is bad." << std::endl;
      return 1;
  }
  return 0;
};
