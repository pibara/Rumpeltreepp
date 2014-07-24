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
      void operator delete(void * p, size_t s);
    private:
      void rotostoragekey(std::string rocap,uint8_t *storagekey) const;
      std::string rwtoro(std::string rwcap,uint8_t *storagekey) const;
      std::string rotostoragepath(uint8_t *storagekey) const;
      std::string mMainSecret;
      std::string mCloudSecret;
  };
}
#endif
