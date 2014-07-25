#include "rumpelstiltskin.hpp"
#include "ConcreteStorage.hpp"
namespace rumpelstiltskin {
  Client::Client(AbstractClient *p) : pImpl(p){}
  string Client::attenuate(string s){
    return pImpl->attenuate(s);
  }
  Storage Client::storage(string cap) {
    return pImpl->storage(cap);
  }
}
