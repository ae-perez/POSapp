//Alejandra Perez
//aeperez@myseneca.ca
//#035174150

#define _CRT_SECURE_NO_WARNINGS

#include "Error.h"
#include <iostream>
#include <cstring>


namespace ict{

    Error::Error() {
        m_message = nullptr;
        //std::cout << m_message << std::endl;
    }
    
    Error::Error(const char* errorMessage) {
        //clear();
        m_message = nullptr;
        message(errorMessage);

    }
    
    Error::~Error() {

        delete[] m_message;
    }
    
    void Error::operator=(const char* errorMessage) {

        clear();
        message(errorMessage);
        //std::cout << m_message << std::endl;

        
    }
  
    void Error::clear() {

        delete[] m_message;
        m_message = nullptr;

    }
    
    bool Error::isClear() const {

        bool status = false;
        if (m_message == nullptr) {
            status = true;
        }
        return status;

    }
    
    void Error::message(const char* value) {

        delete[] m_message;
        m_message = new char[strlen(value)+1];
        strcpy(m_message, value);


    }
    
    Error::operator const char *() const {

        return m_message;
    }
    
    Error::operator bool() const {

        return isClear();
    }
    
    std::ostream& operator<< (std::ostream& os, const Error& M) {

        
        if (M.isClear()) {
            return os;
        }
        return os << M.operator const char *();

    }
    
}