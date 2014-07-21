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
    private:
      void rotostoragekey(sec::string rocap,uint8_t *storagekey) const;
      sec::string rwtoro(sec::string rwcap,uint8_t *storagekey) const;
      sec::string rotostoragepath(uint8_t *storagekey) const;
      sec::string mMainSecret;
      sec::string mCloudSecret;
  };
}
#endif
