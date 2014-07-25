#include "rumpelstiltskin.hpp"
#include <string.h>
namespace rumpelstiltskin {
  //Implementation of a whole lot of PIMPL forwarders.
  Node::Node(AbstractNode *node,AbstractServer const *server):sServer(server),pImpl(node) {};
  string Node::unattenuated_cap() const {
      return pImpl->unattenuated_cap();
  }
  string Node::attenuated_cap() const {
      return pImpl->attenuated_cap();
  }
  string Node::cap() const { 
    if (pImpl->is_attenuated()) {
       return pImpl->attenuated_cap();
    } else {
       return pImpl->unattenuated_cap();
    }
  }
  Storage Node::storage() const {
      return pImpl->storage();
  }
  Node Node::operator[](std::string const &s) const {
     return (*sServer)(this,s);
  }
  bool Node::is_attenuated() const {
     return pImpl->is_attenuated();
  }
  Node Node::attenuated() const {
     return sServer->attenuated(this);
  };
}
