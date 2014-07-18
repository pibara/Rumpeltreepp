#include "rumpelstiltskin.hpp"
#include "ConcreteStorage.hpp"
namespace rumpelstiltskin {
  Client::Client(AbstractClient *p) : pImpl(p){}
  std::string Client::attenuate(std::string s){
    return pImpl->attenuate(s);
  }
  Storage Client::storage(std::string cap) {
    uint8_t buf[32];
    return Storage(new ConcreteStorage(buf,"AB/CD/EFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST"));
  }
}
