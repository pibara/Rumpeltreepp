#include "rumpelstiltskin.hpp"
#include <string.h>
#include "ConcreteServer.hpp"
#include "ConcreteClient.hpp"
#include <cryptopp/osrng.h>
#include "base32.hpp"
namespace rumpelstiltskin {
  Server  create_server(sec::string mainsecret, sec::string cloudsecret) {
    return Server(new ConcreteServer(mainsecret,cloudsecret));
  };
  Client create_client(sec::string cloudsecret) {
    return Client(new ConcreteClient(cloudsecret));
  }
  sec::string pass2rootcap(sec::string pass) {
    //FIXME
    return "rw-ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST";
  }
  sec::string randomrootcap() {
    unsigned char pcbScratch[ 32 ];
    CryptoPP::AutoSeededRandomPool rng;
    rng.GenerateBlock( pcbScratch, 32 );
    return sec::string("rw-") + b32encode<32>(pcbScratch);
  }
  sec::string randomsecret() {
    //FIXME
    return "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRSTABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRSTABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRSTABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRSTABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRSTABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRSTABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRSTABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST";
  }
}
