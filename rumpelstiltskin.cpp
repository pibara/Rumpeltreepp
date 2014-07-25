#include "rumpelstiltskin.hpp"
#include <string.h>
#include "ConcreteServer.hpp"
#include "ConcreteClient.hpp"
#include <cryptopp/osrng.h>
#include "base32.hpp"
namespace rumpelstiltskin {
  Server  create_server(string mainsecret, string cloudsecret) {
    return Server(new ConcreteServer(mainsecret,cloudsecret));
  };
  Client create_client(string cloudsecret) {
    return Client(new ConcreteClient(cloudsecret));
  }
  string pass2rootcap(string pass) {
    unsigned char pcbScratch[CryptoPP::SHA256::DIGESTSIZE];
    CryptoPP::SHA256().CalculateDigest(pcbScratch,reinterpret_cast<const unsigned char *>(pass.c_str()),pass.size());
    return string("rw-") + b32encode<32>(pcbScratch);
  }
  string randomrootcap() {
    unsigned char pcbScratch[ 32 ];
    CryptoPP::AutoSeededRandomPool rng;
    rng.GenerateBlock( pcbScratch, 32 );
    return string("rw-") + b32encode<32>(pcbScratch);
  }
  string randomsecret() {
    unsigned char pcbScratch[ 128 ];
    CryptoPP::AutoSeededRandomPool rng;
    rng.GenerateBlock( pcbScratch,128);
    return b32encode<128>(pcbScratch);
  }
}
