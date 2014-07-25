#include "rumpelstiltskin.hpp"
#include <string.h>
//Implementation of the sensitive data wiping string class.
namespace rumpelstiltskin {
   string::string(const std::string &str):mString(str){}
   string::string(const std::string& str, size_t pos, size_t len):mString(str,pos,len){}
   string::string(const char* s):mString(s){}
   string::string(const char* s, size_t n):mString(s,n){}
   string::string (size_t n, char c):mString(n,c){}
   string::string(const string &str):mString(str.mString){}
   string::string(const string& str, size_t pos, size_t len):mString(str.mString,pos,len){}
   string::string (string&& str) noexcept: mString(std::move(str.mString)){}
   string::~string() {
      this->wipe();
   }
   string& string::operator= (const string& str){
        this->wipe();
        mString=str.mString;
        return *this;
   }
   string& string::operator= (const char* s){
        this->wipe();
        mString=s;
        return *this;
   }
   string& string::operator= (char c) {
        this->wipe();
        mString=c;
        return *this;
   }
   string& string::operator= (string&& str) noexcept{
        this->wipe();
        mString=str.mString;
        return *this;
   }
   string& string::operator= (std::string&& str) noexcept {
        this->wipe();
        mString=std::move(str);
        return *this;
   }
   size_t string::size() const noexcept{
        return mString.size();
   }
   size_t string::length() const noexcept{
        return mString.length();
   }
   void string::clear() noexcept {
        this->wipe();
        mString.clear();
   }
   bool string::empty() const noexcept{
        return mString.empty();
   }
   string& string::operator+= (const string& str) {
        mString += str.mString;
        return *this;
   }
   string& string::operator+= (const std::string& str) {
       mString += str;
       return *this;
   }
   string& string::operator+= (const char* s) {
       mString += s;
       return *this;
   }
   string& string::operator+= (char c){
       mString += c;
       return *this;
   }
   const char* string::c_str() const noexcept {
       return mString.c_str();
   }
   string string::substr (size_t pos, size_t len) const{
      return string(mString.substr(pos,len));
   }
   string::operator std::string &() {
       return mString;
   }
   void string::wipe() noexcept {
       volatile char *p=&mString[0];
       size_t len=mString.size();
       for (size_t index=0;index<len;index++) {
           p[index]=0;
       }
   }
   string operator+(const string &s1, const string &s2) {
       return s1.mString + s2.mString;
   }
   string operator+(const std::string &s1, const string &s2) {
      return s1 + s2.mString;
   }
   string operator+(const string &s1, const std::string &s2) {
       return s1.mString + s2;
   }
   string operator+(const string &s1, const char *s2) {
       return s1.mString + s2;
   }
   bool string::operator==(const char *p) const {
       return mString == p;
   }
   bool string::operator==(const std::string s) const {
       return mString == s;
   }
   bool string::operator==(const string s) const {
       return mString == s.mString;
   }
   bool string::operator!=(const char *p) const {
       return mString != p;
   }
   bool string::operator!=(const std::string s) const {
       return mString != s;
   }
   bool string::operator!=(const string s) const {
       return mString != s.mString;
   }
   std::ostream& operator <<(std::ostream& stream, const string& s){
      stream << s.mString;
      return stream;
   }
}
