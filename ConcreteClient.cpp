#include "ConcreteClient.hpp"
#include "ConcreteStorage.hpp"
#include <string.h>
namespace rumpelstiltskin {
  ConcreteClient::ConcreteClient(std::string cloudsecret):mFakeServer("bogus",cloudsecret) {}
  std::string ConcreteClient::attenuate(std::string s){
     auto node=mFakeServer[s];
     return node.attenuated_cap();
  }
  Storage ConcreteClient::storage(std::string s) {
    auto node=mFakeServer[s];
    return node.storage();
  }
}
