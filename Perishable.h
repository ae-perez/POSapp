//Alejandra Perez
//aeperez@myseneca.ca
//#035174150
#ifndef ICT_PERISHABLE_H__
#define ICT_PERISHABLE_H__
#include <iostream>
#include <fstream>
#include "NonPerishable.h"
#include "Date.h"
#include "Error.h"
#include "NonPerishable.h"
#include "POS.h"
#include "PosIO.h"

using namespace std;
namespace ict {
    /*implement the perishable class to be derived out of a nonperishable class.
     Essentially perisable is a nonperishable class with an expiry date*/
    //QUE?
    
    class Perishable: public NonPerishable {
    private:
        Date m_expiry; //creating a date class that will hold a date
    protected:
        char signature()const; //will print the letter P
        
    public:
        Perishable(); //question (even if its dumb:) are all constructors public?
        //googled: it depends on the program, constructor can be private or protected too!
        std::fstream& save(std::fstream& file) const;
        std::fstream& load(std::fstream& file);
        std::ostream& write(ostream& os, bool linear)const;
        std::istream& read(std::istream& istr);
    };
}








#endif
