#include "rumpelstiltskin.hpp"
namespace rumpelstiltskin {
 
  Node::Node(AbstractNode *node,Server const &server):pImpl(node),sServer(server) {};
  std::string Node::rocap() const {
      return pImpl->rocap();
  }
  std::string Node::rwcap() const {
      return pImpl->rwcap();
  }
  std::string Node::location() const {
      return pImpl->location();
  }
  byte const * const Node::rawkey() const {
     return pImpl->rawkey();
  }
  Node const Node::operator[](std::string s) const {
     return sServer(this,s);
  }
  bool Node::attenuated() const {
     return pImpl->attenuated();
  }

  Server::Server(AbstractServer *s):pImpl(s){}
  Node Server::operator[](std::string s) const {
    return pImpl->operator[](s);
  }
  Node Server::operator()(Node *n, std::string s) const {
    return pImpl->operator()(n,s);
  }

  struct ConcreteNode : public AbstractNode {

  };

  struct ConcreteServer : public AbstractServer {

  };

  Server const create_server(std::string mainsecret, std::string cloudsecret) {
    return Server(new ConcreteServer(mainsecret,cloudsecret));
  };
}
