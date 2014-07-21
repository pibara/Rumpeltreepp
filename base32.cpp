//  Copyright (c) 2012, Rob J Meijer
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
#include "base32.hpp"
template <>
sec::string b32encode<5>(const unsigned char *binary) {
   char target[9];
   target[0]=(binary[0] >> 3) & 0x01f;
   target[1]=((binary[0] << 2) & 0x01c) | ((binary[1] >> 6) & 0x007);
   target[2]=(binary[1] >> 1) & 0x01f;
   target[3]=((binary[1] << 4) & 0x010) | ((binary[2] >>4) & 0x00f);
   target[4]=((binary[2] << 1 ) & 0x01e) | ((binary[3] >> 7) & 0x001);
   target[5]=(binary[3] >> 2) & 0x01f;
   target[6]=((binary[3] << 3) & 0x018) | ((binary[4] >> 5) & 0x007);
   target[7]=binary[4] & 0x01f;
   for (size_t index=0;index<8;index++) {
      target[index] += (target[index]<26) ? 'A' : '2' - 26;
   }
   target[8]=0;
   return target;
};

template <>
sec::string b32encode<0>(const unsigned char *binary) {
  return "";
};

template <>
sec::string b32encode<1>(const unsigned char *binary) {
  unsigned char padded[5];
  padded[0]=binary[0];
  padded[1]=padded[2]=padded[3]=padded[4]=0;
  return b32encode<5>(padded).substr(0,2);
};

template <>
sec::string b32encode<2>(const unsigned char *binary) {
  unsigned char padded[5];
  padded[0]=binary[0];
  padded[1]=binary[1];
  padded[2]=padded[3]=padded[4]=0;
  return b32encode<5>(padded).substr(0,4);
};

template <>
sec::string b32encode<3>(const unsigned char *binary) {
  unsigned char padded[5];
  padded[0]=binary[0];
  padded[1]=binary[1];
  padded[2]=binary[2];
  padded[3]=padded[4]=0;
  return b32encode<5>(padded).substr(0,5);
};

template <>
sec::string b32encode<4>(const unsigned char *binary) {
  unsigned char padded[5];
  padded[0]=binary[0];
  padded[1]=binary[1];
  padded[2]=binary[2];
  padded[3]=binary[3];
  padded[4]=0;
  return b32encode<5>(padded).substr(0,7);
};

template <>
void b32decode<8>(sec::string input,unsigned char *binary) {
   unsigned char numbers[8];
   for (size_t index=0;index<8;index++) {
      char c=input.c_str()[index];
      numbers[index]=0;
      if ((c > '@') and ( c < '[')) {
         numbers[index] = c - 'A';
      } else if ((c > '/') and ( c < ':')) {
         numbers[index] = c + 26 - '2';
      }
   }
   binary[0] = ((numbers[0] << 3) & 0x0f8) | ((numbers[1] >> 2) & 0x007);
   binary[1] = ((numbers[1] << 6) & 0x0d0)  | ((numbers[2] << 1) & 0x03e) | ((numbers[3] >> 4) & 0x001);
   binary[2] = ((numbers[3] << 4) & 0x0f0) | ((numbers[4] >> 1 ) & 0x00f);
   binary[3] = ((numbers[4] << 7) & 0x080)  | ((numbers[5] << 2) & 0x07c) | ((numbers[6] >> 3 ) & 0x003);
   binary[4] = ((numbers[6] << 5) & 0x0e0) | ((numbers[7]) & 0x01f);
};

template <>
void b32decode<48>(sec::string input,unsigned char *binary) {
  b32decode<8>(input.substr(0,8),binary);
  b32decode<8>(input.substr(8,8),binary+5);
  b32decode<8>(input.substr(16,8),binary+10);
  b32decode<8>(input.substr(24,8),binary+15);
  b32decode<8>(input.substr(32,8),binary+20);
  b32decode<8>(input.substr(40,8),binary+25);
};

template <>
void b32decode<52>(sec::string input,unsigned char *binary) {
  b32decode<48>(input.substr(0,48),binary);
  unsigned char work[5];
  b32decode<8>(input.substr(48,4)+"AAAA",work);
  binary[30]=work[0];
  binary[31]=work[1];
};