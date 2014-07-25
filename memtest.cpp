#include "rumpelstiltskin.hpp"
#include <iostream>

int main(int argc,char **argv) {
  for (int i=0;i<100000;i++) {  
    auto secret=rumpelstiltskin::randomsecret();
/*    auto server = rumpelstiltskin::create_server(secret);
    auto rootcap=rumpelstiltskin::randomrootcap();
    rootcap = rumpelstiltskin::pass2rootcap("knockknock");
    auto rootnode = server[rootcap];
    auto storage = rootnode.storage();
    auto attenuatedrootnode = rootnode.attenuated();
    auto childnode = rootnode["bob"];
    auto attenuatedchildnode1 = attenuatedrootnode["bob"];
    auto attenuatedchildnode2 = childnode.attenuated();
    auto storage1 = attenuatedchildnode1.storage();
    auto storage2 = attenuatedchildnode2.storage();
    auto client = rumpelstiltskin::create_client();
    auto as1 = client.attenuate(rootcap);*/
  }
};
