#include "rumpelstiltskin.hpp"
#include <iostream>

int main(int argc,char **argv) {
  std::string mysecret("PLZKHRQCPJYKNYKVKL6SN6T4LO5RKVSXCO46X26BKFDLB4LEJCEZXNSUQBOUX3RFIQOGPTUOM6KZ2DRXFG6QB3P5EN7K3FHHZUN2VFKE2MKQ4IHWKN2XRM7YC4YLLHFM2HVRZQYJUS7TJLGLE5YJ6RCIV46EFM6ECWG5L2MTXZFHIUOOMVNL3SPAEYFI7FHWGQEHUBJ7HU24M");
  auto server = rumpelstiltskin::create_server(mysecret);
  auto rootcap1 = rumpelstiltskin::pass2rootcap("Allice");
  auto rootnode1=server[rootcap1];  
  auto storage = rootnode1.storage();
  bool allzero = true;
  uint8_t const *key=storage.crypto_key();
  for (int i=0;i<32;i++) {
     if (key[i] != 0) {
        allzero = false;
     }
  }
  if (allzero) {
      std::cout << "Crypto key is all zero's, this is extremely unlikely to be valid" << std::endl;
      return 1;
  }
  return 0;
};
