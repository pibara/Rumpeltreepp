//FIXME, this must become where the real logic lives.
#include "rumpelstiltskin.hpp"
#include <string.h>
#include "ConcreteNode.hpp"
#include "ConcreteServer.hpp"
namespace rumpelstiltskin {
    ConcreteServer::ConcreteServer(sec::string mainsecret, sec::string cloudsecret) {}
    Node ConcreteServer::operator[](sec::string) const {
        //FIXME
        uint8_t buf[32];
        return Node(new ConcreteNode("rw-ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST","ro-ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST","AB/CD/EFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST",buf),this);
    }
    Node ConcreteServer::operator()(Node const *, sec::string) const {
        //FIXME
        uint8_t buf[32];
        return Node(new ConcreteNode("rw-ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST","ro-ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST","AB/CD/EFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST",buf),this);
    }
    Node ConcreteServer::attenuated(Node const *n) const{
        //FIXME
        uint8_t buf[32];
        return Node(new ConcreteNode("ro-ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST","ro-ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST","AB/CD/EFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST",buf),this);
    }
}
