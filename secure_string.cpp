#include "secure_string.hpp"
namespace sec {
  void allocator::deallocate(char *p, size_type num) {
     std::cerr << "Whiping " << num << " bytes of secure string content." << std::endl;
     memset((void *)p,20,num); //fill with ascii spaces
     std::allocator<char>::deallocate(p, num);
  }
}
