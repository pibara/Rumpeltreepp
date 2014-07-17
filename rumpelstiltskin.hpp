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
namespace rumpelstiltskin {
  struct Node;
  struct AbstractNode {
      virtual std::string rocap() = 0;  // Get the sparsecap for read-only access.
      virtual std::string rwcap() = 0; //Get the sparse-cap for unatenuated access.
      virtual std::string location() = 0; //Get the relative path where this node would have to be serialized.
      virtual Node operator[](std::string) = 0; //Convenience method for getting at child node using weak name.
      virtual bool attenuated() = 0; //Query if this node is unatenuated or read only.
  };
  struct Node : public AbstractServer {
      std::string rocap();
      std::string rwcap();
      std::string location();
      Node operator[](std::string);
      bool attenuated();
    private:
      std::unique_ptr<AbstractNode> pImpl;
  }
  struct AbstractServer {
      virtual Node operator[](std::string)  = 0; //Get a Node from a sparse-cap string.
      virtual Node operator()(Node *, std::string) = 0; //Get a child node using a weak name and a parent node.
  };
  struct Server: public AbstractServer {
      Node operator[](std::string);
      Node operator()(Node *, std::string);
    private:
      AbstractServer *pImpl;
  };
  //Function for creating a server object using one or two secrets. Use one secret for local storage or two
  //if you are using any kind of network storage server or service as underlying place to do serialization.
  Server create_server(std::string mainsecret, std::string cloudsecret="local");
}
#endif