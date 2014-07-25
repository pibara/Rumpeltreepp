#include "rumpelstiltskin.hpp"
#include <string.h>
#include "ConcreteServer.hpp"
#include "ConcreteClient.hpp"
#include <cryptopp/osrng.h>
#include "base32.hpp"
namespace rumpelstiltskin {
  Server  create_server(string const &mainsecret, string const &cloudsecret) {
    return Server(new ConcreteServer(mainsecret,cloudsecret));
  };
  Client create_client(string const &cloudsecret) {
    return Client(new ConcreteClient(cloudsecret));
  }
  string pass2rootcap(string const &pass) {
    unsigned char pcbScratch[CryptoPP::SHA256::DIGESTSIZE];
    CryptoPP::SHA256().CalculateDigest(pcbScratch,reinterpret_cast<const unsigned char *>(pass.c_str()),pass.size());
    string rval= string("rw-") + b32encode<32>(pcbScratch);
    memclear32(pcbScratch);
    return rval;
  }
  string randomrootcap() {
    unsigned char pcbScratch[ 32 ];
    CryptoPP::AutoSeededRandomPool rng;
    rng.GenerateBlock( pcbScratch, 32 );
    string rval= string("rw-") + b32encode<32>(pcbScratch);
    memclear32(pcbScratch);
    return rval;
  }
  string randomsecret() {
    unsigned char pcbScratch[ 128 ];
    CryptoPP::AutoSeededRandomPool rng;
    rng.GenerateBlock( pcbScratch,128);
    string rval= b32encode<128>(pcbScratch);
    memclear32(pcbScratch);
    return rval;
  }
  void memclear32(volatile unsigned char *p) {
      for (size_t index=0;index<32;index++){
         p[index]=0;
      }
  }
}
