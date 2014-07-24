#include "rumpelstiltskin.hpp"
#include <string.h>
#include "ConcreteServer.hpp"
#include "ConcreteClient.hpp"
#include <cryptopp/osrng.h>
#include "base32.hpp"
namespace rumpelstiltskin {
  Server  create_server(std::string mainsecret, std::string cloudsecret) {
    return Server(new ConcreteServer(mainsecret,cloudsecret));
  };
  Client create_client(std::string cloudsecret) {
    return Client(new ConcreteClient(cloudsecret));
  }
  std::string pass2rootcap(std::string pass) {
    unsigned char pcbScratch[CryptoPP::SHA256::DIGESTSIZE];
    CryptoPP::SHA256().CalculateDigest(pcbScratch,reinterpret_cast<const unsigned char *>(pass.c_str()),pass.size());
    return std::string("rw-") + b32encode<32>(pcbScratch);
  }
  std::string randomrootcap() {
    unsigned char pcbScratch[ 32 ];
    CryptoPP::AutoSeededRandomPool rng;
    rng.GenerateBlock( pcbScratch, 32 );
    return std::string("rw-") + b32encode<32>(pcbScratch);
  }
  std::string randomsecret() {
    unsigned char pcbScratch[ 128 ];
    CryptoPP::AutoSeededRandomPool rng;
    rng.GenerateBlock( pcbScratch,128);
    return b32encode<128>(pcbScratch);
  }
}
