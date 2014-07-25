#ifndef _CONCRETENODE_HPP
#define _CONCRETENODE_HPP
#include "rumpelstiltskin.hpp"
#include <string.h>
namespace rumpelstiltskin {
  struct ConcreteNode : public AbstractNode {
      ConcreteNode(string rw,string ro, string loc, uint8_t const *key);
      ~ConcreteNode();
      string attenuated_cap() const ;
      string unattenuated_cap() const ;
      Storage storage() const;
      bool is_attenuated() const ;
    private:
      string const mRwCap;
      string const mRoCap;
      string const mLocation;
      uint8_t mKey[32];
  };
}
#endif
