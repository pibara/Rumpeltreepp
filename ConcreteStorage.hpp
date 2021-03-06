#ifndef _CONCRETESTORAGE_HPP
#define _CONCRETESTORAGE_HPP
#include "rumpelstiltskin.hpp"
namespace rumpelstiltskin {
  struct  ConcreteStorage: public AbstractStorage {
        ConcreteStorage(uint8_t const * const, string const &);
        ~ConcreteStorage();
        string path() const;
        uint8_t const * const crypto_key() const;
    private:
        uint8_t mKey[32];
        string const mPath; //Note that this is a string that is wiped on destruction.
  };
}
#endif
