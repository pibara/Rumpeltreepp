#include "rumpelstiltskin.hpp"
#include <string.h>
namespace rumpelstiltskin {
  Server::Server(AbstractServer *s):pImpl(s){}
  Node Server::operator[](string const &s) const {
    return pImpl->operator[](s);
  }
  Node Server::operator()(Node const *n, std::string const &s) const {
    return pImpl->operator()(n,s);
  }
  Node Server::attenuated(Node const *n) const {
    return pImpl->attenuated(n);
  }
}
