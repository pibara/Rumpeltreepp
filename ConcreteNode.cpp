#include "rumpelstiltskin.hpp"
#include <string.h>
#include <new>
#include "ConcreteNode.hpp"
#include "ConcreteStorage.hpp"
namespace rumpelstiltskin {
      ConcreteNode::ConcreteNode(std::string rw,std::string ro, std::string loc, uint8_t const *key):mRwCap(rw),
                                                                                       mRoCap(ro),
                                                                                       mLocation(loc) {
          memcpy(mKey,key,32);
      }
      ConcreteNode::~ConcreteNode() {
          memset(mKey,20,32); //fill with ascii spaces.
      }
      std::string ConcreteNode::unattenuated_cap() const {
         return mRwCap;
      }
      std::string ConcreteNode::attenuated_cap() const {
         return mRoCap;
      }
      Storage ConcreteNode::storage() const {
         return Storage(new ConcreteStorage(mKey,mLocation));
      }
      bool ConcreteNode::is_attenuated() const {
         return (mRwCap == "");
      }
      void ConcreteNode::operator delete(void * p, size_t s) {
         ::memset(p, 0, s);
         ::operator delete(p);
      }
}
