#!/bin/bash
clang++ -std=c++11 ConcreteNode.cpp  ConcreteServer.cpp ConcreteClient.cpp ConcreteStorage.cpp Client.cpp Node.cpp  Server.cpp  Storage.cpp rumpelstiltskin.cpp -lcrypto++  test.cpp -o test
