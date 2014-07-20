#ifndef _CONCRETESERVER_HPP
#define _CONCRETESERVER_HPP
#include "rumpelstiltskin.hpp"
#include <string.h>
#include "ConcreteNode.hpp"
namespace rumpelstiltskin {
  struct ConcreteServer : public AbstractServer {
    ConcreteServer(sec::string mainsecret, sec::string cloudsecret);
    Node operator[](sec::string) const;
    Node operator()(Node const *, sec::string) const;
    Node attenuated(Node const *n) const;
  };
}
#endif
