//Alejandra Perez
//aeperez@myseneca.ca
//#035174150

#ifndef ICT_ITEM_H__
#define ICT_ITEM_H__
// inlcude PosIO and POS header files
#include <iostream>
#include <cstring>
#include "PosIO.h"
#include "POS.h"

using namespace std;

namespace ict {
  // class Item
    class Item: public PosIO {
    private:
        char m_sku[MAX_SKU_LEN+1];
        char* m_name;
        double m_price;
        bool m_taxed;
        int m_quantity;
        
    public:
        Item();
        Item(const char* sku, const char* name, double price, bool tax = true);
        Item (const Item& I); /* do you need this one or is it just the other one!? (operator) */
        virtual ~Item();
        
        //setters
        void sku(const char* sku);
        void price(const double price);
        void name(const char* name);
        void taxed(const bool tax);
        void quantity(const int quantity);
        
        //getters
        const char* sku() const;
        double price() const;
        const char* name() const;
        bool taxed() const;
        int quantity() const;
        double cost() const;
        bool isEmpty() const;
        
        //member operator overloads
        Item& operator= (const Item& I);
        bool operator==(const char*);
        int operator+=(const int);
        int operator-=(const int);
        
    };
    
  // end class Item
  // operator += 
  double operator+=(double& d, Item& I);
  // operator << and operator >>
    std::istream& operator>>(std::istream& is, Item& I);
    std::ostream& operator<<(std::ostream& os, const Item& I);
}










#endif
