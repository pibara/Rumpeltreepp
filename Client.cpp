#include "rumpelstiltskin.hpp"
#include "ConcreteStorage.hpp"
namespace rumpelstiltskin {
  Client::Client(AbstractClient *p) : pImpl(p){}
  std::string Client::attenuate(std::string s){
    return pImpl->attenuate(s);
  }
  Storage Client::storage(std::string cap) {
    return pImpl->storage(cap);
  }
}
