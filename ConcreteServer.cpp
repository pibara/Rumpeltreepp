//FIXME, this must become where the real logic lives.
#include "rumpelstiltskin.hpp"
#include <string.h>
#include "ConcreteNode.hpp"
#include "ConcreteServer.hpp"
namespace rumpelstiltskin {
    ConcreteServer::ConcreteServer(sec::string mainsecret, sec::string cloudsecret):
          mMainSecret(mainsecret),mCloudSecret(cloudsecret) {}
    Node ConcreteServer::operator[](sec::string b32cap) const {
        sec::string rwcap = b32cap;
        sec::string rocap = b32cap;
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
           sec::string storagepath = rotostoragepath(storagekey);
           return Node(new ConcreteNode(rwcap,rocap,storagepath,storagekey)); 
        } else {
            uint8_t buf[32];
            memset(buf,0,32);
            return Node(new ConcreteNode("","","",buf));
        }
    }

    void ConcreteServer::rotostoragekey(sec::string rocap,uint8_t *storagekey) {
        b32decode<52>(b32cap.substr(3,52),storagekey);
    }

    sec::string ConcreteServer::rwtoro(sec::string rwcap,uint8_t *storagekey){
        uint8_t rwkey[32];
        b32decode<52>(rwcap.substr(3,52),rwkey);
        CryptoPP::HMAC<CryptoPP::SHA256> hmac(rwkey,32);
        sec::string data= "read-only::nosalt";
        hmac.CalculateDigest(storagekey,(const unsigned char *)(data.c_str()),data.size());        
        return sec::string("ro-") + b32encode<CryptoPP::SHA256::DIGESTSIZE>(storagekey);
    }

    sec::string ConcreteServer::rotostoragepath(uint8_t *storagekey) {
        CryptoPP::HMAC<CryptoPP::SHA256> hmac(storagekey,32);
        sec::string data = sec::string("storage::") + mCloudSecret;
        uint8_t storagepathkey[32];
        hmac.CalculateDigest(storagepathkey,(const unsigned char *)(data.c_str()),data.size());
        sec::string b32=b32encode<CryptoPP::SHA256::DIGESTSIZE>(storagepathkey);
        return b32.substr(0,2) + "/" + b32.substr(2,2) + "/" + b32.substr(4,48);
    }

    Node ConcreteServer::operator()(Node const *parent, sec::string child) const {
        uint8_t *storagekey = parent->storage().crypto_key();
        CryptoPP::HMAC<CryptoPP::SHA256> hmac(storagekey,32);
        sec::string data = child + "::" +  mMainSecret;
        uint8_t childrwkey[32];
        uint8_t childrokey[32];
        hmac.CalculateDigest(childrwkey,(const unsigned char *)(data.c_str()),data.size());
        sec::string rwcap = sec::string("rw-") + b32encode<CryptoPP::SHA256::DIGESTSIZE>(childrwkey);
        CryptoPP::HMAC<CryptoPP::SHA256> hmac2(childrwkey,32);
        sec::string data2= "read-only::nosalt";
        hmac.CalculateDigest(childrokey,(const unsigned char *)(data2.c_str()),data2.size());
        return Node(new ConcreteNode(sec::string("rw-") + b32encode<32>(childrwkey),
                                     sec::string("ro-") + b32encode<32>(childrokey),
                                     rotostoragepath(childrokey),
                                     childrokey);
    }
    Node ConcreteServer::attenuated(Node const *n) const{
        return Node(new ConcreteNode("",n->attenuated_cap(),n->storage().path(), n->storage().crypto_key()),this);
    }
}
