#ifndef _CONCRETECLIENT_HPP
#define _CONCRETECLIENT_HPP
#include "rumpelstiltskin.hpp"
#include <string.h>
#include "ConcreteNode.hpp"
#include "ConcreteServer.hpp"
namespace rumpelstiltskin {
  struct ConcreteClient : public AbstractClient {
      ConcreteClient(std::string cloudsecret);
      std::string attenuate(std::string uacap);
      Storage storage(std::string);
     private:
      ConcreteServer const mFakeServer;
  };
}
#endif
