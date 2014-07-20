#include "rumpelstiltskin.hpp"
namespace rumpelstiltskin {
  Storage::Storage(AbstractStorage *as): pImpl(as) {}
  sec::string Storage::path() const {
      return pImpl->path();
  }
  uint8_t const * const Storage::crypto_key() const{
      return pImpl->crypto_key();
  }
}
