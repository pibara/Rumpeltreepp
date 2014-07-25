#ifndef _CONCRETECLIENT_HPP
#define _CONCRETECLIENT_HPP
#include "rumpelstiltskin.hpp"
#include <string.h>
#include "ConcreteNode.hpp"
#include "ConcreteServer.hpp"
namespace rumpelstiltskin {
  /*The concrete impementation class for the client side class*/
  struct ConcreteClient : public AbstractClient {
      ConcreteClient(string const &cloudsecret);
      string attenuate(string const &uacap) const;
      Storage storage(string const &) const;
     private:
      ConcreteServer const mFakeServer;
  };
}
#endif
