#include "rumpelstiltskin.hpp"
#include <string.h>
namespace rumpelstiltskin {
  Node::Node(AbstractNode *node,AbstractServer const *server):pImpl(node),sServer(server) {};
  std::string Node::unattenuated_cap() const {
      return pImpl->unattenuated_cap();
  }
  std::string Node::attenuated_cap() const {
      return pImpl->attenuated_cap();
  }
  std::string Node::cap() const { 
    if (pImpl->is_attenuated()) {
       return pImpl->attenuated_cap();
    } else {
       return pImpl->unattenuated_cap();
    }
  }
  Storage Node::storage() const {
      return pImpl->storage();
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
