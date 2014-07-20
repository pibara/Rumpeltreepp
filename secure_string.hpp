#ifndef _SECURE_STRING_HPP
#define _SECURE_STRING_HPP
#include <string>
#include <string.h>
#include <iostream>
namespace sec {
  class allocator : public std::allocator<char> {
    void deallocate(char *p, size_type num) {
       std::cerr << "Whiping " << num << " bytes of secure string content." << std::endl;
       memset((void *)p,20,num); //fill with ascii spaces
       std::allocator<char>::deallocate(p, num);
    }
  };
  typedef std::basic_string<char, std::char_traits<char>, allocator > string;
}
#endif
