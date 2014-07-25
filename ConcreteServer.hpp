#ifndef _CONCRETESERVER_HPP
#define _CONCRETESERVER_HPP
#include "rumpelstiltskin.hpp"
#include <string.h>
#include "ConcreteNode.hpp"
namespace rumpelstiltskin {
  struct ConcreteServer : public AbstractServer {
      ConcreteServer(string mainsecret, string cloudsecret);
      Node operator[](string) const;
      Node operator()(Node const *, std::string) const;
      Node attenuated(Node const *n) const;
    private:
      void rotostoragekey(string rocap,uint8_t *storagekey) const;
      string rwtoro(string rwcap,uint8_t *storagekey) const;
      string rotostoragepath(uint8_t *storagekey) const;
      string const mMainSecret;
      string const mCloudSecret; 
  };
}
#endif
