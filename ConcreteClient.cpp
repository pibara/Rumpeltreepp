#include "ConcreteClient.hpp"
#include "ConcreteStorage.hpp"
namespace rumpelstiltskin {
  ConcreteClient::ConcreteClient(sec::string cloudsecret):mFakeServer("bogus",cloudsecret) {}
  sec::string ConcreteClient::attenuate(sec::string s){
     auto node=mFakeServer[s];
     return node.attenuated_cap();
  }
  Storage ConcreteClient::storage(sec::string s) {
    auto node=mFakeServer[s];
    return node.storage();
  }
}
