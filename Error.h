//Alejandra Perez
//aeperez@myseneca.ca
//#035174150

// compilation safegaurds
#ifndef ICT_ERROR_H_
#define ICT_ERROR_H_
#include <iostream>
#include <iostream>
#include <cstring>

namespace ict {
   class Error {
      char* m_message;
   public:
   // constructors
       Error(); //√
       Error(const char* errorMessage); //√
   // destructor
       //~Error(); //<---- erase comment if need be
       virtual ~Error(); //√
   // deleted constructor and operator=
       Error(const Error& em) = delete;
       Error& operator=(const Error& em) = delete;

   // operator= for c-style strings
       void operator=(const char* errorMessage); //√

   // methods
       void clear(); //√
       bool isClear()const; //√
       void message(const char* value); //√

   // cast overloads
       operator const char*() const; //eh? (erase)
       operator bool()const; //eh? (erase)

   };
   // operator << overload prototype for cout
    std::ostream& operator<<(std::ostream& os, const Error& M); //is this right?
}

#endif

