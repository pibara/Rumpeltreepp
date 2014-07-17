Rumpeltree++
============

C++ Rumpelstiltskin tree-graph library

For a description of what this library does, please have a look at these two blog posts:

* http://minorfs.wordpress.com/2014/02/20/rumpelstiltskin-and-his-children/
* http://minorfs.wordpress.com/2014/03/21/rumpelstiltskin-and-his-children-part-2/

Intended usage:

  auto rs = rumpelstiltskin::create_server("somelocalsecret");
  
  auto root = rs[rumpelstiltskin::pick_root("rumpelstiltskin")];

  auto child = root["bob"];

  auto rochild = child();

  std::string path = std::string("/someroot/") + rochild.location();
