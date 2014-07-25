#include "rumpelstiltskin.hpp"
#include "ConcreteStorage.hpp"
#include <string.h>
namespace rumpelstiltskin {
    ConcreteStorage::ConcreteStorage(uint8_t const * const key, string const &paths):mPath(paths) {
        memcpy(mKey,key,32);
    }
    ConcreteStorage::~ConcreteStorage() {
       memclear32(mKey);
    }
    string ConcreteStorage::path() const { return mPath;}
    uint8_t const * const ConcreteStorage::crypto_key() const { return mKey;}
}
