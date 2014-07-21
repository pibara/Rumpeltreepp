#ifndef _SECURE_STRING_HPP
#define _SECURE_STRING_HPP
#include <string>
#include <string.h>
namespace sec {
  class allocator : public std::allocator<char> {
    //This does not actually get fired on Linux+clang apparently, but on other compilers/platforms it might
    //so we leave it in for now unless users urge us to remove it and move everything back to std::string.
    void deallocate(char *p, size_type num);
  };
  typedef std::basic_string<char, std::char_traits<char>, allocator > string;
}
#endif
