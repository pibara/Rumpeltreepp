//FIXME, this must become where the real logic lives.
#include "rumpelstiltskin.hpp"
#include "base32.hpp"
#include <string.h>
#include <cryptopp/sha.h>
#include <cryptopp/hmac.h>
#include "ConcreteNode.hpp"
#include "ConcreteServer.hpp"
#include <string>

namespace rumpelstiltskin {
    ConcreteServer::ConcreteServer(string mainsecret, string cloudsecret):
          mMainSecret(mainsecret),mCloudSecret(cloudsecret) {}
    Node ConcreteServer::operator[](string b32cap) const {
        string rwcap = b32cap;
        string rocap = b32cap;
        char const * cstr=b32cap.c_str();
        bool validcap=(b32cap.size() == 55 ) &&
                (cstr[0] == 'r') &&
                ((cstr[1] == 'o') || (cstr[1] == 'w')) &&
                (cstr[2] == '-');
        for (size_t index=3;index<55;index++) {
          if ((cstr[index] < '2') ||
            (cstr[index] > 'Z') ||
            ((cstr[index] > '7') && (cstr[index] < 'A'))) {
               validcap=false;
          }
        }
        if (validcap) {
           uint8_t storagekey[32];
           if (cstr[1] == 'w') {
               rocap = rwtoro(rwcap,storagekey);
           } else {
               rwcap = "";
               rotostoragekey(rocap,storagekey);
           }
           string storagepath = rotostoragepath(storagekey);
           return Node(new ConcreteNode(rwcap,rocap,storagepath,storagekey),this);
        } else {
            uint8_t buf[32];
            memset(buf,0,32);
            return Node(new ConcreteNode("","","",buf),this);
        }
    }

    void ConcreteServer::rotostoragekey(string rocap,uint8_t *storagekey) const {
        b32decode<32>(rocap.substr(3,52),storagekey);
    }

    string ConcreteServer::rwtoro(string rwcap,uint8_t *storagekey) const {
        uint8_t rwkey[32];
        b32decode<32>(rwcap.substr(3,52),rwkey);
        CryptoPP::HMAC<CryptoPP::SHA256> hmac(rwkey,32);
        std::string data= "read-only::nosalt";
        hmac.CalculateDigest(storagekey,reinterpret_cast<const unsigned char *>(data.c_str()),data.size());        
        return string("ro-") + b32encode<32>(storagekey);
    }

    string ConcreteServer::rotostoragepath(uint8_t *storagekey) const {
        CryptoPP::HMAC<CryptoPP::SHA256> hmac(storagekey,32);
        string data = string("storage::") + mCloudSecret;
        uint8_t storagepathkey[32];
        hmac.CalculateDigest(storagepathkey,reinterpret_cast<const unsigned char *>(data.c_str()),data.size());
        string b32=b32encode<32>(storagepathkey);
        return b32.substr(0,2) + "/" + b32.substr(2,2) + "/" + b32.substr(4,48);
    }

    Node ConcreteServer::operator()(Node const *parent, std::string child) const {
        uint8_t const *storagekey = parent->storage().crypto_key();
        CryptoPP::HMAC<CryptoPP::SHA256> hmac(storagekey,32);
        string data = child + "::" +  mMainSecret;
        uint8_t childrwkey[32];
        uint8_t childrokey[32];
        hmac.CalculateDigest(childrwkey,reinterpret_cast<const unsigned char *>(data.c_str()),data.size());
        string rwcap = string("rw-") + b32encode<32>(childrwkey);
        CryptoPP::HMAC<CryptoPP::SHA256> hmac2(childrwkey,32);
        std::string data2= "read-only::nosalt";
        hmac2.CalculateDigest(childrokey,reinterpret_cast<const unsigned char *>(data2.c_str()),data2.size());
        if (parent->is_attenuated()) {
           return Node(new ConcreteNode("",
                                        string("ro-") + b32encode<32>(childrokey),
                                        rotostoragepath(childrokey),
                                        childrokey),this);
        } else {
           return Node(new ConcreteNode(string("rw-") + b32encode<32>(childrwkey),
                                        string("ro-") + b32encode<32>(childrokey),
                                        rotostoragepath(childrokey),
                                        childrokey),this);
        }
    }
    Node ConcreteServer::attenuated(Node const *n) const{
        return Node(new ConcreteNode("",n->attenuated_cap(),n->storage().path(), n->storage().crypto_key()),this);
    }
}
