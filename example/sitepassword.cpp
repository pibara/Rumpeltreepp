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
  if (argc < 4) {
      std::cout << "usage:" << std::endl << "\t" << argv[0] << " <root_cap_pass> <domain> <username>" << std::endl;
      return 1;
  }
  std::string rootcappass=argv[1];
  std::string domain=argv[2];
  std::string account=argv[3];
  /*Determine where the server secres should be stored*/
  struct passwd *passwdfile_entry = getpwuid(geteuid());
  std::string secstore=std::string(passwdfile_entry->pw_dir) + "/.sitepassword";
  /*If no secret exists, create a new one*/
  if ( !boost::filesystem::exists(secstore) ) {
    auto secret=rumpelstiltskin::randomsecret();
    std::ofstream newsecstorefile(secstore);
    newsecstorefile << secret;
    newsecstorefile.close();
  }
  /*Read the server secret from the filesystem*/
  std::ifstream secstorefile(secstore);
  std::string mysecret((std::istreambuf_iterator<char>(secstorefile)),
  std::istreambuf_iterator<char>());
  secstorefile.close();
  /*Create a server object using the secret*/
  auto server = rumpelstiltskin::create_server(mysecret);
  /*Use the supplied password to create a root cap/node*/
  auto rootcap = rumpelstiltskin::pass2rootcap(rootcappass);
  auto rootnode=server[rootcap];
  /*Get a child node using the domain*/
  auto domainnode = rootnode[domain];
  /*Get a child node of the domain node using the account name */
  auto accountnode = domainnode[account];
  /*Strip the 'rw-' part from our password*/
  std::cout << accountnode.cap().substr(3,52) << std::endl;
  return 0;
};
