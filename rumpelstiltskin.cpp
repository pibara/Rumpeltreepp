#include "rumpelstiltskin.hpp"
namespace rumpelstiltskin {
  struct ConcreteNode : public AbstractNode {
     std::string rocap() const {
         return "ro-ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST";
     }
     std::string rwcap() const {
         return "rw-ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST";
     }
     std::string location() const {
         return "AB/CD/EF/GHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST";
     }
     uint8_t const * const rawkey() const {
         return nullptr;
     }
     bool is_attenuated() const {
         return false;
     }
  };

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
     return Node(new ConcreteNode(),sServer);
  };

  Server::Server(AbstractServer *s):pImpl(s){}
  Node Server::operator[](std::string s) const {
    return pImpl->operator[](s);
  }

  Node Server::operator()(Node const *n, std::string s) const {
    return pImpl->operator()(n,s);
  }

  struct ConcreteServer : public AbstractServer {
    ConcreteServer(std::string mainsecret, std::string cloudsecret) {}
    Node operator[](std::string) const {
        return Node(new ConcreteNode(),this);
    }
    Node operator()(Node const *, std::string) const {
        return Node(new ConcreteNode(),this);
    }
  };

  Server  create_server(std::string mainsecret, std::string cloudsecret) {
    return Server(new ConcreteServer(mainsecret,cloudsecret));
  };
  std::string pass2rootcap(std::string pass) {
    return "rw-ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST";
  }
}
