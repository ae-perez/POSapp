//Alejandra Perez
//aeperez@myseneca.ca
//#035174150

#define _CRT_SECURE_NO_WARNINGS
// Lib includes
#include <iostream>
#include <cstring>
// inlcude Item and POS header files
#include "Item.h"
#include "POS.h"
#include "PosIO.h"

using namespace std;
namespace ict{
  // class Item implementaion
    Item::Item() {
        m_sku [0] = '\0';
        m_name = nullptr;
        m_price = 0.0;
        m_taxed = false;
        m_quantity = 0;
    }
    
    Item::Item(const char* sku, const char* name, double price, bool tax) {
        //copies the sku into corresponding member
        strcpy(m_sku, sku);
        //allocates enough memory to hold the name in m_name
        m_name = new char [strlen(name)];
        strcpy(m_name, name);
        //set quantity to 0
        m_quantity = 0;
        //set reaming variables to receive parameter values
        m_price = price;
        //set default value of tax to true, so if not given
        //then it will become true
        m_taxed = tax;
        
    }
    
    Item::Item(const Item& I){
        //used lab 6
        m_name = nullptr;
        *this = I; //calls assignment operator
        
    }
    
    Item::~Item() {
        delete[] m_name;
        //m_name = nullptr;
    }
    
    Item& Item::operator=(const Item& I) {
        //SELF NOTE: ALE MAKE SURE THIS WORKS PROPERLY OR YOUR PROGRAM WON'T
        //WORK PROPERLY!!1 **
        //used lab 6 as an example to work off of
        
        //check for self assignment like in lab 6
        if (this != &I) {
            strcpy(m_sku, I.m_sku);
            m_price = I.m_price;
            m_taxed = I.m_taxed;
            m_quantity = I.m_quantity;
            
            //then deallocate previously allocated dynamic memory
            delete [] m_name;
            
            //allocate new dynamic memory and copy data into allocated memory
            if(I.m_name != nullptr) {
                m_name = new char [strlen(I.m_name)+1];
                strcpy(m_name, I.m_name);
                //m_price = I.m_price;
                //m_taxed = I.m_taxed;
                //m_quantity = I.m_quantity;
            }
            
            else {
                m_name = nullptr;
            }
            
            
        }
        
        return *this;
        
        
        
    } 
    
    //-----setters
    void Item::sku(const char *sku) {
        //set m_sku to sku
        strcpy(m_sku, sku);
    }
    
    void Item::price(const double price) {
       //set m_price to price
        m_price = price;
    }
    
    void Item::name(const char *name) {
        //set m_name to name
        //strcpy(m_name, name);
        //remember: name is dynamically allocated
        if (m_name != nullptr) {
            delete[] m_name;
        }
        m_name = new char [strlen(name) +1];
        strcpy(m_name, name);
    }
    
    void Item::taxed(const bool tax) {
        //set m_taxed to tax
        m_taxed = tax;
    }
    
    void Item::quantity(const int quantity) {
        //set m_quantity to quantity
        m_quantity = quantity;
    }
    
    //-----getters
    const char* Item::sku() const {
        //returning the OG variable sku
        return m_sku;
    }
    
    double Item:: price() const {
        //returning the OG variable price
        return m_price;
    }
    
    const char* Item::name() const {
        //returning the OG variable name
        return m_name;
    }
    
    bool Item::taxed() const {
        //returning the OG variable tax
        return m_taxed;
    }
    
    int Item::quantity() const {
        //returning the OG variable quantity
        return m_quantity;
    }
    
    double Item::cost() const {
        double ret = 0; // value that we will alter to return
        if (m_taxed == true) {
            ret = m_price * (1+ TAX);
        }
        else {
            ret = m_price;
        }
        
        return ret;
        
    }
    
    bool Item::isEmpty() const {
        return m_sku[0] == '\0' && m_name == nullptr && m_price == 0.0 && m_taxed == false && m_quantity == 0;
        
    } //double check this one
    
    bool Item::operator==(const char* sku) {
        return strcmp(m_sku, sku) == 0;
    }
    
    int Item::operator+=(int value) {
        return m_quantity += value;
    }
    
    int Item::operator-=(int value) {
        return m_quantity -= value;
    }

    double operator+=(double& d, Item& I) {
        d = I.quantity() * I.cost();
        return d;
    }
    
    std::ostream& operator<<(std::ostream& os, const Item& I) {
       return I.write(os, true);
    }
    
    std::istream& operator>>(std::istream& is, Item& I) {
        return I.read(is);
        
    } 
    


}
