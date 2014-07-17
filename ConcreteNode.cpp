#include "rumpelstiltskin.hpp"
#include <string.h>
#include "ConcreteNode.hpp"
namespace rumpelstiltskin {
      ConcreteNode::ConcreteNode(std::string rw,std::string ro, std::string loc, uint8_t const *key):mRwcap(rw),
                                                                                       mRoCap(ro),
                                                                                       mLocation(loc) {
          memcpy(mKey,key,32);
      }
      std::string ConcreteNode::rocap() const {
         return mRoCap;
      }
      std::string ConcreteNode::rwcap() const {
         return mRwcap;
      }
      std::string ConcreteNode::location() const {
         return mLocation;
      }
      uint8_t const * const ConcreteNode::rawkey() const {
         return mKey;
      }
      bool ConcreteNode::is_attenuated() const {
         return (mRwcap == "");
      }
}
