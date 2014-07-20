#include "rumpelstiltskin.hpp"
#include "ConcreteStorage.hpp"
namespace rumpelstiltskin {
  Client::Client(AbstractClient *p) : pImpl(p){}
  sec::string Client::attenuate(sec::string s){
    return pImpl->attenuate(s);
  }
  Storage Client::storage(sec::string cap) {
    return pImpl->storage(cap);
  }
}
