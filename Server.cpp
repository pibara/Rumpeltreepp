#include "rumpelstiltskin.hpp"
#include <string.h>
namespace rumpelstiltskin {
  Server::Server(AbstractServer *s):pImpl(s){}
  Node Server::operator[](sec::string s) const {
    return pImpl->operator[](s);
  }
  Node Server::operator()(Node const *n, sec::string s) const {
    return pImpl->operator()(n,s);
  }
  Node Server::attenuated(Node const *n) const {
    return pImpl->attenuated(n);
  }
}
