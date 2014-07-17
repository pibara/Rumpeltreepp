#include "rumpelstiltskin.hpp"
#include <string.h>
namespace rumpelstiltskin {
  Node::Node(AbstractNode *node,AbstractServer const *server):pImpl(node),sServer(server) {};
  std::string Node::rocap() const {
      return pImpl->rocap();
  }
  std::string Node::rwcap() const {
      return pImpl->rwcap();
  }
  std::string Node::location() const {
      return pImpl->location();
  }
  uint8_t const * const Node::rawkey() const {
     return pImpl->rawkey();
  }
  Node Node::operator[](std::string s) const {
     return (*sServer)(this,s);
  }
  bool Node::is_attenuated() const {
     return pImpl->is_attenuated();
  }
  Node Node::attenuated() const {
     return sServer->attenuated(this);
  };
}
