#include "rumpelstiltskin.hpp"
#include "ConcreteStorage.hpp"
namespace rumpelstiltskin {
    ConcreteStorage::ConcreteStorage(uint8_t const * const key, std::string path):mPath(path) {
           //FIXME,copy
    }
    ConcreteStorage::~ConcreteStorage() {}
    std::string ConcreteStorage::path() const { return mPath;}
    uint8_t const * const ConcreteStorage::crypto_key() const { return mKey;}
}
