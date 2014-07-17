#ifndef _CONCRETESERVER_HPP
#define _CONCRETESERVER_HPP
#include "rumpelstiltskin.hpp"
#include <string.h>
#include "ConcreteNode.hpp"
namespace rumpelstiltskin {
  struct ConcreteServer : public AbstractServer {
    ConcreteServer(std::string mainsecret, std::string cloudsecret);
    Node operator[](std::string) const;
    Node operator()(Node const *, std::string) const;
    Node attenuated(Node const *n) const;
  };
}
#endif
