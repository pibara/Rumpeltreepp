#ifndef _CONCRETENODE_HPP
#define _CONCRETENODE_HPP
#include "rumpelstiltskin.hpp"
#include <string.h>
namespace rumpelstiltskin {
  struct ConcreteNode : public AbstractNode {
      ConcreteNode(sec::string rw,sec::string ro, sec::string loc, uint8_t const *key);
      ~ConcreteNode();
      sec::string attenuated_cap() const ;
      sec::string unattenuated_cap() const ;
      Storage storage() const;
      bool is_attenuated() const ;
    private:
      sec::string const mRwCap;
      sec::string const mRoCap;
      sec::string const mLocation;
      uint8_t mKey[32];
  };
}
#endif
