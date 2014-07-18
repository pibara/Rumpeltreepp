//FIXME, this must become where the real logic lives.
#include "rumpelstiltskin.hpp"
#include <string.h>
#include "ConcreteNode.hpp"
#include "ConcreteServer.hpp"
#include "base32.hpp"
namespace rumpelstiltskin {
    ConcreteServer::ConcreteServer(std::string mainsecret, std::string cloudsecret) {}
    Node ConcreteServer::operator[](std::string) const {
        uint8_t buf[32];
        return Node(new ConcreteNode("rw-ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST","ro-ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST","AB/CD/EFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST",buf),this);
    }
    Node ConcreteServer::operator()(Node const *, std::string) const {
        uint8_t buf[32];
        return Node(new ConcreteNode("rw-ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST","ro-ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST","AB/CD/EFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST",buf),this);
    }
    Node ConcreteServer::attenuated(Node const *n) const{
        uint8_t buf[32];
        return Node(new ConcreteNode("ro-ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST","ro-ABCDEFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST","AB/CD/EFGHIJKLMNOPQRSTUVWXYZ234567ABCDEFGHIJKLMNOPQRST",buf),this);
    }
}
