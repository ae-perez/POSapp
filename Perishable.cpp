//Alejandra Perez
//aeperez@myseneca.ca
//#035174150
#define _CRT_SECURE_NO_WARNINGS
// lib includes
#include "Perishable.h"
#include "NonPerishable.h"
#include "Date.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

namespace ict {
    Perishable::Perishable(){
        //returns the date
        m_expiry.dateOnly(true); //remember m_expiry date is a class of date
        
    }
    
    char Perishable::signature() const{
        return 'P';
    }
    
    
    fstream& Perishable::save(fstream& file) const {
        /*you could also make your life easy by calling the Nonperishable:: version of this */
        //i realized this later and got lazy ....
        //question: do we have to put NonPerishable:: / Item:: before the function? or nah ... ?
        
        //all the info is saved into the file
        file << signature() << ',' << sku() << ',' << name() << ',' << price() << ',' << taxed() << ',' << quantity() << ',' << m_expiry;
        
        
        //returns the file with data in it
        return file;
    }
    
    fstream& Perishable::load(fstream& file) {
        
        //call the nonperishable::load file
        NonPerishable::load(file);
        file.ignore(); //ignores/discards character(s) from the input buffer
        //now we load the info in m_expiry to the file
        file >> m_expiry;
        
        //return the file with this new data
        return file;
        
    }
    
    ostream& Perishable::write(ostream& os, bool linear) const {
       //call upon the other classes write
        NonPerishable::write(os, linear);
        
        //if ok is clear and linear do the following
        if (ok() && linear == false) {
            os << "Expiry date: " << m_expiry << endl;
        }
        //return to the screen with Expiry date showing
        return os;
    }
    
    istream& Perishable::read(istream& istr) {

        //call the NonPerishable
        NonPerishable::read(istr);
        //if file doesn't fail do the following:
        //display the expirdy date yyyy/mm//dd
        //then read m_expiry
        //ask the user to input a date
        //validate the date entirly ... year...month...day ...
        //return to screen
        if (!istr.fail()) {
            //display expiry date tag
            cout << "Expiry date (YYYY/MM/DD): ";
            m_expiry.read(istr);
            
            if (m_expiry.bad()){
                if (m_expiry.errCode() == CIN_FAILED){
                    error("Invalid Date Entry");
                }
                else if (m_expiry.errCode() == YEAR_ERROR){
                    error("Invalid Year in Date Entry");
                }
                else if (m_expiry.errCode() == MON_ERROR){
                    error("Invalid Month in Date Entry");
                }
                else if (m_expiry.errCode() == DAY_ERROR){
                    error("Invalid Day in Date Entry");
                }
                istr.setstate(ios::failbit);
            }
        }
        
        
        return istr;
    }
    
    
    
    
    
}






