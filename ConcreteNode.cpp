#include "rumpelstiltskin.hpp"
#include <string.h>
#include <new>
#include "ConcreteNode.hpp"
#include "ConcreteStorage.hpp"
namespace rumpelstiltskin {
      ConcreteNode::ConcreteNode(string rw,string ro, string loc, uint8_t const *key):mRwCap(rw),
                                                                                       mRoCap(ro),
                                                                                       mLocation(loc) {
          memcpy(mKey,key,32); //Copy the raw bytes of the key.
      }
      ConcreteNode::~ConcreteNode() {
          memclear32(mKey);
      }
      string ConcreteNode::unattenuated_cap() const {
         return mRwCap;
      }
      string ConcreteNode::attenuated_cap() const {
         return mRoCap;
      }
      Storage ConcreteNode::storage() const {
         return Storage(new ConcreteStorage(mKey,mLocation)); //Create and return a Storage object containing storage key and loc
      }
      bool ConcreteNode::is_attenuated() const {
         return (mRwCap == "");
      }
}
