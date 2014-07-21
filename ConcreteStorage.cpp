#include "rumpelstiltskin.hpp"
#include "ConcreteStorage.hpp"
#include <string.h>
namespace rumpelstiltskin {
    ConcreteStorage::ConcreteStorage(uint8_t const * const key, sec::string paths):mPath(paths) {
        memcpy(mKey,key,32);
    }
    ConcreteStorage::~ConcreteStorage() {}
    sec::string ConcreteStorage::path() const { return mPath;}
    uint8_t const * const ConcreteStorage::crypto_key() const { return mKey;}
    void ConcreteStorage::operator delete(void * p, size_t s) {
       ::memset(p, 0, s);
       ::operator delete(p);
    }
}
