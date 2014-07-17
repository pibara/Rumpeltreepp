#ifndef _CONCRETENODE_HPP
#define _CONCRETENODE_HPP
#include "rumpelstiltskin.hpp"
#include <string.h>
namespace rumpelstiltskin {
  struct ConcreteNode : public AbstractNode {
      ConcreteNode(std::string rw,std::string ro, std::string loc, uint8_t const *key);
      std::string rocap() const ;
      std::string rwcap() const ;
      std::string location() const ;
      uint8_t const * const rawkey() const ;
      bool is_attenuated() const ;
    private:
      std::string const mRwcap;
      std::string const mRoCap;
      std::string const mLocation;
      uint8_t mKey[32];
  };
}
#endif
