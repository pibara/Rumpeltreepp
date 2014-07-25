//  Copyright (c) 2014, Rob J Meijer
//
//Permission is hereby granted, free of charge, to any person or organization
//obtaining a copy of the software and accompanying documentation covered by
//this license (the "Software") to use, reproduce, display, distribute,
//execute, and transmit the Software, and to prepare derivative works of the
//Software, and to permit third-parties to whom the Software is furnished to
//do so, all subject to the following:
//
//The copyright notices in the Software and this entire statement, including
//the above license grant, this restriction and the following disclaimer,
//must be included in all copies of the Software, in whole or in part, and
//all derivative works of the Software, unless such copies or derivative
//works are solely in the form of machine-executable object code generated by
//a source language processor.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
//SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
//FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
//ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//DEALINGS IN THE SOFTWARE.
#ifndef _RUMPELSTILTSKIN_HPP
#define _RUMPELSTILTSKIN_HPP
#include <string>
#include <memory>
#include <iostream>
#include <inttypes.h>
namespace rumpelstiltskin {
  struct Node;
  struct Server;
  struct AbstractServer;
  struct string;
  //This forwarder class is a semi complete string replacement forwarder that wipes its content on destruction.
  //This is the base stringclass for this library for all strings that could contain sensistive data,
  struct string {
        string(const std::string &str);
        string(const std::string& str, size_t pos, size_t len = std::string::npos);
        string(const char* s);
        string(const char* s, size_t n);
        string (size_t n, char c);
        string(const string &str);
        string(const string& str, size_t pos, size_t len = std::string::npos);
        string (string&& str) noexcept;
        ~string();
        string& operator= (const string& str);
        string& operator= (const char* s);
        string& operator= (char c);
        string& operator= (string&& str) noexcept;
        string& operator= (std::string&& str) noexcept;
        size_t size() const noexcept;
        size_t length() const noexcept; 
        void clear() noexcept;
        bool empty() const noexcept;
        string& operator+= (const string& str);
        string& operator+= (const std::string& str);
        string& operator+= (const char* s);
        string& operator+= (char c);
        const char* c_str() const noexcept;
        string substr (size_t pos = 0, size_t len = std::string::npos) const;
        operator std::string &();
        bool operator==(const char *p) const;
        bool operator==(const std::string s) const;
        bool operator==(const string) const;
        bool operator!=(const char *p) const;
        bool operator!=(const std::string s) const;
        bool operator!=(const string) const;
        friend string operator+(const string &, const string &);
        friend string operator+(const std::string &, const string &);
        friend string operator+(const string &, const std::string &);
        friend string operator+(const string &s1, const char *s2);
        friend std::ostream& operator <<(std::ostream& stream, const string& s);
    private:
        void wipe() noexcept;
        mutable std::string mString;
  };
  string operator+(const string &s1, const string &s2);
  string operator+(const std::string &s1, const string &s2);
  string operator+(const string &s1, const std::string &s2);
  string operator+(const string &s1, const char *s2);
  std::ostream& operator <<(std::ostream& stream, const string& s);
  //When the node designated by a sparse cap as used in this library is serialized, a storage object should indicate
  //where it should be stored and what key should be used to encrypt it. Serialization and encryption are not done by this
  //library and should be done by the user of the library, primary on the server side of things. 
  struct AbstractStorage {
     virtual string path() const = 0; //Get the relative path where this node would have to be serialized.
     virtual uint8_t const * const crypto_key() const = 0; //Get raw pointer to the binary crypto key to use for serialisation.
  };
  struct Storage : public AbstractStorage {
         Storage(AbstractStorage *);
         string path() const;
         uint8_t const * const crypto_key() const;
     private:
         std::unique_ptr<AbstractStorage> pImpl;
  };
  //Node's in the tree
  struct AbstractNode {
      virtual string attenuated_cap() const  = 0;  // Get the sparsecap for attenuated access.
      virtual string unattenuated_cap() const = 0; //Get the sparse-cap for unatenuated access.
      virtual Storage storage() const = 0; //Get the relative path where this node would have to be serialized.
      virtual bool is_attenuated() const = 0; //Query if this node is unatenuated or read only.
  };
  struct Node : public AbstractNode {
      Node(AbstractNode *,AbstractServer const *);
      Node(Node &&) = default;
      Node & operator=(Node &&) = default;
      Node(Node const &) = delete;
      Node & operator=(Node const &) = delete;
      string attenuated_cap() const ;
      string unattenuated_cap() const ;
      string cap() const ; //Convenience method for getting the unattenuated cap if available or the attenuated cap if not.
      Storage storage() const ;
      Node operator[](std::string const &) const ; //Convenience method for getting at child node using weak name. Will throw for client side.
      bool is_attenuated() const;
      Node attenuated() const;
    private:
      AbstractServer const *sServer;
      std::unique_ptr<AbstractNode> pImpl;
  };

  //Server or File-system side.
  struct AbstractServer {
      virtual Node operator[](string const &) const = 0; //Get a Node from a sparse-cap string.
      virtual Node operator()(Node const *, std::string const &) const= 0; //Get a child node using a weak name and a parent node.
      virtual Node attenuated(Node const *) const = 0;
  };
  struct Server: public AbstractServer {
      Server(AbstractServer *s);
      Node operator[](string const &) const;
      Node operator()(Node const *, std::string const &) const;
      Node attenuated(Node const *) const;
    private:
      std::unique_ptr<AbstractServer> pImpl;
  };
  // Client or regular process side.
  struct AbstractClient {
      virtual string attenuate(string const &) const =0;
      virtual Storage storage(string const &) const =0; //Don't use this for client side en/decryption without an clear security architecture
  };
  struct Client: public AbstractClient {
      Client(AbstractClient *);
      string attenuate(string const &) const;
      Storage storage(string const &) const; //Don't use this for client side en/decryption without an clear security architecture
    private:
      std::unique_ptr<AbstractClient> pImpl;
  };

  //Function for creating a server object using one or two secrets. Use one secret for local storage or two
  //if you are using any kind of network storage server or service as underlying place to do serialization.
  Server create_server(string const & mainsecret, string const & cloudsecret="local");
  //Create a client object for client side attenuation and decryption.
  Client create_client(string const & cloudsecret="local");
  //Turn a password of kinds into a suitable root cap for a tree.
  string pass2rootcap(string const &pass);
  //Get a securely random suitable root cap for a tree.
  string randomrootcap();
  //Get a securely random secret usable as argument for create_server
  string randomsecret();
  //Utility function, mostly for library internal usage, we may move it out oth the API later.
  void memclear32(volatile unsigned char *p);
}
#endif
