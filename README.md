Rumpeltree++
============

C++ Rumpelstiltskin tree-graph library

For a description of what this library does, please have a look at these two blog posts:

* http://minorfs.wordpress.com/2014/02/20/rumpelstiltskin-and-his-children/
* http://minorfs.wordpress.com/2014/03/21/rumpelstiltskin-and-his-children-part-2/

Please have a look at test.cpp to view how the API is  coming along.

RumpelTree++ is still very much a work in progress, while functionaly complete and tested, I'm currently
trying to track down a memory leak in the library, most likely related to my attempts to create
a user friendly string that is suitable for storing sensitive information in a way that prevents
temporary tokens from lingering in process or system memory.  
As a result of this memory leak you should not yet be usingin production systems yet. 

I hope to release a patched (and documented) version in the comming weeks. 

The current version should at least be sufficient to play around with, and possibly suplying me with feedback on the API.

To build you will need to:

* Make sure cmake, llvm and clang are installed.
* Make sure Crypto++ is installed (both library and development headers)
* Create a directory 'build'
* Change your working dir to the new 'build' dir
* Run 'cmake ..'
* Run 'make'
* Run 'make test'
* If all tests succeed (there are still more test needed before release), run 'sudo make install'

An important note regarding the client side API. The client side API can be used to make systems
with many clients more scalable by moving attenuation and decryption to the client side.
That is, converting unattenuated access caps to their attenuated counterpart, and decrypting encrypted data
are tasks that can without problems be moved to the client side as a way to scale. Decomposition CAN only be 
done server side, and encryption SHOULD only be done server side.
Technically encryption CAN be done on the client side, but doing so will most likely involve relatively dangerous
constructs that go against good practices regarding the Principle Of Least Priviledge (POLP). 
If you are considering using this library together with client side encryption, 
the author of this library advices strongly against this, unless you happen to be one of the worlds top 100 
security architects who knows exactly what (s)he is doing.
