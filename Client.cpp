#include "rumpelstiltskin.hpp"
#include "ConcreteStorage.hpp"
namespace rumpelstiltskin {
  Client::Client(AbstractClient *p) : pImpl(p){}
  string Client::attenuate(string s) const{
    return pImpl->attenuate(s);
  }
  Storage Client::storage(string cap) const{
    return pImpl->storage(cap);
  }
}
