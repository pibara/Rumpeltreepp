#include "rumpelstiltskin.hpp"
#include <boost/filesystem.hpp>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <sys/types.h>
#include <pwd.h>

int main(int argc,char **argv) {
  if (argc < 3) {
      std::cout << "usage:" << std::endl << "\t" << argv[0] << " <root_cap_pass> <domain>" << std::endl;
      return 1;
  }
  std::string rootcappass=argv[1];
  std::string domain=argv[2];
  struct passwd *passwdfile_entry = getpwuid(geteuid());
  std::string secstore=std::string(passwdfile_entry->pw_dir) + "/.sitepassword";
  if ( !boost::filesystem::exists(secstore) ) {
    auto secret=rumpelstiltskin::randomsecret();
    std::ofstream newsecstorefile(secstore);
    newsecstorefile << secret;
    newsecstorefile.close();
  }
  std::ifstream secstorefile(secstore);
  std::string mysecret((std::istreambuf_iterator<char>(secstorefile)),
  std::istreambuf_iterator<char>());
  secstorefile.close();
  auto server = rumpelstiltskin::create_server(mysecret);
  auto rootcap = rumpelstiltskin::pass2rootcap(rootcappass);
  std::cout << rootcappass << " -> " << rootcap << std::endl;
  auto rootnode=server[rootcap];
  std::cout << rootcap << " => " << rootnode.attenuated_cap() << " !" << std::endl;
  auto domainnode = rootnode[domain];
  std::cout << domainnode.cap() << std::endl;
  return 0;
};
