#ifndef _CONCRETECLIENT_HPP
#define _CONCRETECLIENT_HPP
#include "rumpelstiltskin.hpp"
#include <string.h>
#include "ConcreteNode.hpp"
#include "ConcreteServer.hpp"
namespace rumpelstiltskin {
  struct ConcreteClient : public AbstractClient {
      ConcreteClient(string cloudsecret);
      string attenuate(string uacap);
      Storage storage(string);
     private:
      ConcreteServer const mFakeServer;
  };
}
#endif
