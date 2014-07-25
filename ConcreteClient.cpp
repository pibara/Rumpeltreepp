#include "ConcreteClient.hpp"
#include "ConcreteStorage.hpp"
#include <string.h>
namespace rumpelstiltskin {
  ConcreteClient::ConcreteClient(string cloudsecret):mFakeServer("bogus",cloudsecret) {}
  string ConcreteClient::attenuate(string s) const{
     auto node=mFakeServer[s];
     return node.attenuated_cap();
  }
  Storage ConcreteClient::storage(string s) const {
    auto node=mFakeServer[s];
    return node.storage();
  }
}
