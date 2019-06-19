//Alejandra Perez
//aeperez@myseneca.ca
//#035174150

#ifndef ICT_NONPERISHABLE_H__
#define ICT_NONPERISHABLE_H__
//include the Item.h because its going to call from it and from Error.h
#include <iostream>
#include <fstream>
#include "Item.h"
#include "Error.h"

using namespace std;

namespace ict {
    
    class NonPerishable: public Item {
    
    private:
        Error m_err; //will hold your error message

        
    protected:
        bool ok() const; //returns true if there is no error message
        void error(const char* message); //sets the error message
        virtual char signature() const; //will print a P
        
    public:
        //these are your virtual funtions from PosIO 
        std::fstream& save(std::fstream& file) const;
        std::fstream& load(std::fstream& file);
        std::ostream& write(ostream& ostr, bool linear)const;
        std::istream& read(std::istream& is);
        
        
    
    };
}







#endif