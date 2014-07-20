#include "rumpelstiltskin.hpp"
#include <string.h>
#include "ConcreteNode.hpp"
#include "ConcreteStorage.hpp"
namespace rumpelstiltskin {
      ConcreteNode::ConcreteNode(sec::string rw,sec::string ro, sec::string loc, uint8_t const *key):mRwCap(rw),
                                                                                       mRoCap(ro),
                                                                                       mLocation(loc) {
          memcpy(mKey,key,32);
      }
      ConcreteNode::~ConcreteNode() {
          memset(mKey,20,32); //fill with ascii spaces.
      }
      sec::string ConcreteNode::unattenuated_cap() const {
         return mRwCap;
      }
      sec::string ConcreteNode::attenuated_cap() const {
         return mRoCap;
      }
      Storage ConcreteNode::storage() const {
         return Storage(new ConcreteStorage(mKey,mLocation));
      }
      bool ConcreteNode::is_attenuated() const {
         return (mRwCap == "");
      }
}
