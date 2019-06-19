//Alejandra Perez
//aeperez@myseneca.ca
//#035174150
#ifndef ICT_POSAPP_h
#define ICT_POSAPP_h

#include <iostream>
#include <cstring>
#include <fstream>
#include "PosApp.h"
#include "Error.h"
#include "Perishable.h"
#include "NonPerishable.h"
#include "Item.h"
#include "Date.h"
#include "POS.h"
#include "PosIO.h"



using namespace std;
namespace ict {
    class PosApp {
        /*PosApp uses the classes created in milestones1-4 to manage the items in a store
         and also works as a Point of Sales system to sell the items*/
    private:
        char m_filename[128];
        char m_billfname[128];
        Item* m_items[MAX_NO_ITEMS];
        int m_noOfItems;
        //private member functions:
        int menu();
        
        //data management member functions:
        void deallocateItems();
        void loadRecs();
        void saveRecs();
        int searchItems(const char* sku) const;
        void updateQty();
        void addItem(bool isPerishable); 
        void listItems()const;
        //point of sale member functions:
        void truncateBillFile();
        void showBill();
        void addToBill(Item& I);
        void POS();
        
    public:
        PosApp(const char* filename, const char* billfname);
        void run();
        
        
    };
}

#endif
