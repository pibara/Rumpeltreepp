#include "rumpelstiltskin.hpp"
#include <string.h>
#include "ConcreteServer.hpp"
#include "ConcreteClient.hpp"
namespace rumpelstiltskin {
  Server  create_server(std::string mainsecret, std::string cloudsecret) {
    return Server(new ConcreteServer(mainsecret,cloudsecret));
  };
  Client create_client(std::string cloudsecret) {
    return Client(new ConcreteClient(cloudsecret));
  }
  std::string pass2rootcap(std::string pass) {
    return "rw-ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST";
  }
  std::string randomrootcap() {
    return "rw-ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST";
  }
  std::string randomsecret() {
    return "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRSTABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRSTABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRSTABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRSTABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRSTABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRSTABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRSTABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST";
  }
}
