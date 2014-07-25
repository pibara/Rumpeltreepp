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
        /*A valid cap starts with 'ro-' or 'rw-' folowed by 52 base32 characters*/
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
               rocap = rwtoro(rwcap,storagekey); //Convert valid unattenuated authority cap to an attenuated authority key and
                                                 //update the storagekey in the process.
           } else {
               rwcap = ""; //No unattenuated access using this cap
               rotostoragekey(rocap,storagekey); //Convert the attenuated authority cap to its binary representation.
           }
           string storagepath = rotostoragepath(storagekey); //Convert the storage key to the storagepath.
           Node nod(new ConcreteNode(rwcap,rocap,storagepath,storagekey),this); //Return a new node.
           memclear32(storagekey); //Wipe the storagekey memory.
           return nod;
        } else {
            uint8_t buf[32];
            memclear32(buf);
            return Node(new ConcreteNode("","","",buf),this); //Invalid cap, return an invalid node.
        }
    }

    void ConcreteServer::rotostoragekey(string rocap,uint8_t *storagekey) const {
        b32decode<32>(rocap.substr(3,52),storagekey); //The storagekey is simply the binary representation of the 
                                                      //attenuated authority cap
    }

    string ConcreteServer::rwtoro(string rwcap,uint8_t *storagekey) const {
        uint8_t rwkey[32];
        b32decode<32>(rwcap.substr(3,52),rwkey);
        CryptoPP::HMAC<CryptoPP::SHA256> hmac(rwkey,32); //Create an HMAC object using the binary unattenuated cap as key.
        memclear32(rwkey); //Wipe the rwkey memory.
        std::string data= "read-only::nosalt";
        hmac.CalculateDigest(storagekey,reinterpret_cast<const unsigned char *>(data.c_str()),data.size()); //Calculate the HMAC
        return string("ro-") + b32encode<32>(storagekey); //This results in the attenuated authority cap
    }

    string ConcreteServer::rotostoragepath(uint8_t *storagekey) const {
        CryptoPP::HMAC<CryptoPP::SHA256> hmac(storagekey,32); //Create an HMAC object using the binary storagekey as key
        string data = string("storage::") + mCloudSecret; //Use the cloud secret to potentially allow client side decryption.
        uint8_t storagepathkey[32];
        hmac.CalculateDigest(storagepathkey,reinterpret_cast<const unsigned char *>(data.c_str()),data.size()); //calculate new key
        string b32=b32encode<32>(storagepathkey); //Convert to base32
        memclear32(storagepathkey); //Wipe the storagepathkey memory.
        return b32.substr(0,2) + "/" + b32.substr(2,2) + "/" + b32.substr(4,48); //Make something of a pseudo path from the base32.
    }

    //Decomposition
    Node ConcreteServer::operator()(Node const *parent, std::string child) const {
        uint8_t const *storagekey = parent->storage().crypto_key(); //Get the parents storage crypto key.
        CryptoPP::HMAC<CryptoPP::SHA256> hmac(storagekey,32); //Use the key as key for HMAC
        string data = child + "::" +  mMainSecret; //Use the main secret for digest calculation as to disalow dangerous
                                                   //client side decomposition.
        uint8_t childrwkey[32];
        uint8_t childrokey[32];
        hmac.CalculateDigest(childrwkey,reinterpret_cast<const unsigned char *>(data.c_str()),data.size()); //Use HMAC as child cap
        string rwcap = string("rw-") + b32encode<32>(childrwkey);
        CryptoPP::HMAC<CryptoPP::SHA256> hmac2(childrwkey,32); //Create a second HMAC for attenuation.
        std::string data2= "read-only::nosalt";
        hmac2.CalculateDigest(childrokey,reinterpret_cast<const unsigned char *>(data2.c_str()),data2.size()); //Use hmac as 
                                                                                                         //attenuated auth cap
        if (parent->is_attenuated()) {
           //If the parrent is attenuated, make the child attenuated by not relaying the unattenuated authority cap.
           Node nod(new ConcreteNode("",
                                        string("ro-") + b32encode<32>(childrokey),
                                        rotostoragepath(childrokey),
                                        childrokey),this);
           memclear32(childrwkey); //Wipe the childrwkey memory.
           memclear32(childrokey); //Wipe the childrwkey memory.
           return nod;
        } else {
           //Unatenuated yields unatenuated children.
           Node nod(new ConcreteNode(string("rw-") + b32encode<32>(childrwkey),
                                        string("ro-") + b32encode<32>(childrokey),
                                        rotostoragepath(childrokey),
                                        childrokey),this);
           memclear32(childrwkey); //Wipe the childrwkey memory.
           memclear32(childrokey); //Wipe the childrwkey memory.
           return nod;
        }
    }
    Node ConcreteServer::attenuated(Node const *n) const{
        //Get an attenuated version of this node.
        return Node(new ConcreteNode("",n->attenuated_cap(),n->storage().path(), n->storage().crypto_key()),this);
    }
}
