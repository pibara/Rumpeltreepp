#ifndef _CONCRETENODE_HPP
#define _CONCRETENODE_HPP
#include "rumpelstiltskin.hpp"
#include <string.h>
namespace rumpelstiltskin {
  struct ConcreteNode : public AbstractNode {
      ConcreteNode(std::string rw,std::string ro, std::string loc, uint8_t const *key);
      std::string attenuated_cap() const ;
      std::string unattenuated_cap() const ;
      Storage storage() const;
      bool is_attenuated() const ;
    private:
      std::string const mRwCap;
      std::string const mRoCap;
      std::string const mLocation;
      uint8_t mKey[32];
  };
}
#endif
