#include "ConcreteClient.hpp"
#include "ConcreteStorage.hpp"
namespace rumpelstiltskin {
  ConcreteClient::ConcreteClient(std::string cloudsecret) {}
  std::string ConcreteClient::attenuate(std::string s){ return s;}
  Storage ConcreteClient::storage(std::string) {
    uint8_t buf[32];
    return Storage(new ConcreteStorage(buf,"AB/CD/EFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST"));
  }
}
