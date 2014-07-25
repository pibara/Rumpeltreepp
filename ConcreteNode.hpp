#ifndef _CONCRETENODE_HPP
#define _CONCRETENODE_HPP
#include "rumpelstiltskin.hpp"
#include <string.h>
namespace rumpelstiltskin {
  /*Concrete implementation class for Node's*/
  struct ConcreteNode : public AbstractNode {
      ConcreteNode(string const &rw,string const &ro, string const &loc, uint8_t const *key);
      ~ConcreteNode(); //Destructor wipes the key.
      string attenuated_cap() const ;
      string unattenuated_cap() const ;
      Storage storage() const;
      bool is_attenuated() const ;
    private:
      string const mRwCap; //Note, these strings are of a type wiped on destruction.
      string const mRoCap; //Note, these strings are of a type wiped on destruction.
      string const mLocation; //Note, these strings are of a type wiped on destruction.
      uint8_t mKey[32];
  };
}
#endif
