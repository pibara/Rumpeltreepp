#ifndef _CONCRETECLIENT_HPP
#define _CONCRETECLIENT_HPP
#include "rumpelstiltskin.hpp"
#include <string.h>
#include "ConcreteNode.hpp"
#include "ConcreteServer.hpp"
namespace rumpelstiltskin {
  struct ConcreteClient : public AbstractClient {
      ConcreteClient(sec::string cloudsecret);
      sec::string attenuate(sec::string uacap);
      Storage storage(sec::string);
     private:
      ConcreteServer const mFakeServer;
  };
}
#endif
