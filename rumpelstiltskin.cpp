#include "rumpelstiltskin.hpp"
#include <string.h>
#include "ConcreteServer.hpp"
namespace rumpelstiltskin {
  Server  create_server(std::string mainsecret, std::string cloudsecret) {
    return Server(new ConcreteServer(mainsecret,cloudsecret));
  };
  std::string pass2rootcap(std::string pass) {
    return "rw-ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST";
  }
}
