//Alejandra Perez
//aeperez@myseneca.ca
//#035174150
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
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
    int PosApp::menu() {
        //this will be the value that will determine which function to call
        int value;
        //options that are displayed to user
        cout << "The Sene-Store" << endl <<
        "1- List items" << endl <<
        "2- Add Perishable item" << endl <<
        "3- Add Non-Perishable item" << endl <<
        "4- Update item quantity" << endl <<
        "5- Show Item" << endl <<
        "6- POS" << endl <<
        "0- exit program" << endl <<
        "> ";
        cin >> value; //allows user to input the data
        //cin.ignore();
        
        //if the value is not readable or is outside of this range the selection will be set to -1
        //before the user's selection is returned, this function goes to new line
        if (cin.fail() || value > 6 || value < 0) { //options to end the program
            value = -1;
            
        }
        cin.clear(); //needs this to clear keyboard or it will continue doing something weird (it looks like its looping)
        cin.ignore(2000, '\n');
        return value;
    } //after user input selection it must go to new line
    
    void PosApp::deallocateItems() {
        //deallocating each individual element
        for (int i = 0; i < m_noOfItems; i++) {
            m_items[i] = nullptr;
        }
        
        /*
        THIS METHOD DIDN'T WORK CAUSE YOU AREN'T DEALLOCATING EACH INDIVIDUAL ELEMENT
        delete  m_items[m_noOfItems];
        *m_items = nullptr; */
        
        
        //make num of items equal to 0
        m_noOfItems = 0;
        
    }
    
    void PosApp::loadRecs() {
       
        
        
        //this function will load all the item records
        
        //first deallocate items to makre sure previous items loaded are removed from mem
        deallocateItems();
        
        //then opens data file to read using an instance of fstream
        //with filename kept in m_filename and ios::in flag
        fstream file;
        char id = 0;
        //open file for readings
        file.open(m_filename, ios::in);
        
        //if file is in fail state (if file does not exisit) it will clear and close
        if (file.is_open()) { // <---- this is the proper way to test if something is open not just file.fail()
            while (!file.fail()) { //while file is not in fail state
                id = file.get(); //=====added: gets id from file
                if(id == 'P' || id == 'N') {
                    //file.ignore();
                    if (id == 'P') {
                        file.ignore();
                        m_items[m_noOfItems] = new Perishable();
                    }
                    else {
                        file.ignore();
                        m_items[m_noOfItems] = new NonPerishable();
                    }
                    //cout << "hey there";
                    m_items[m_noOfItems]->load(file);
                    m_noOfItems++;
                }
                
            }
            //once loop is complete close the file
            file.close();

        }
        
        
        else {
            //clears the failure
            file.clear();
            //close
            file.close();
            //reopen the file for writting
            file.open(m_filename, ios::out);
            //close the file again
            file.close();
            //while files is not the end of the file do the following:
        }
    }
    
    void PosApp::saveRecs() {
        //overwrites data in file with the items pointed by m_items
        //instance of fstream:
        fstream file;
        
        //opens data file for overwriting:
        file.open(m_filename, std::ios::out);
        
        //loops through the m_items array [m_noofitems] times and writes them in save() function we created
        //will only save if quantity is more than 0:
        for (int i = 0; i < m_noOfItems; i++) {
            if (m_items[i]->quantity() > 0) {
                m_items[i]->save(file);
                file << endl;
            }
        }
        
        //close the file:
        file.close();
        
        //calls loadrecs to have recent update of items in PosApp
        //loadRecs();
    }
    
    int PosApp::searchItems(const char *sku) const {
        //our index variable
        int index = -1;
        
        //while i less than the number of items in the array m_item loops through
        for (int i = 0; i < m_noOfItems; i++) {
            if (*m_items[i] == sku) {
                index = i;
                
            }
        }
        
        return index;
            
    }
    
    void PosApp::updateQty() {
        //var you will store user sku in:
		char s[MAX_SKU_LEN+1];
        //var found item will be stored in:
        int sindex;
        //var num of items user inputs will be stored in:
        int numit;
        
        //prompt user for a sku:
        cout << endl << "Please enter the SKU: ";
        cin >> s; //holds the sku
        //cin.ignore();
        
        //call searchitem to look for s:
        sindex = searchItems(s); //should hold the index of where the sku is [BUT DOESN'T]
        if (sindex == -1) {
            cout << "Not found!" << endl << endl;
        }
        else {
            //function that will write everything non linearly:
            m_items[sindex]->write(cout,false); //will display info in non linear format
            //prompt user for quantity:
            cout << endl << "Please enter the number of purchased items: ";
            cin >> numit;
            cin.ignore();
            //add number of quantity to m_items, save it, inform the user you have!:
            *m_items[sindex] += numit;
            //cin.ignore(); //see if this needs to be deleted later
            saveRecs();
            cout << "Updated!" << endl;
            
        }
        
        
        
        
    }
        
    void PosApp::addItem(bool isPerishable) {
        if (isPerishable) { //if parishable is true
            Perishable* pr = new Perishable(); //make temp perishable
            pr->read(cin); //let it be read
            
            if (cin.fail()) { //if output is fail
                cin.clear(); //clear keyboard
                cin.ignore(2000, '\n'); //ignore until \n
                cout <<*pr << endl; // output error
            }
            else {
                m_items[m_noOfItems] = pr; // else copy all info into this object
                m_noOfItems++; // increase number of items by 1
                saveRecs(); //save info into file
                cout << "Item added." << endl; // let the user know that you added the file
            }
            //immediatly deallocate the temp perishable
            pr = nullptr;
        }
        else { //repeats  the process for this
            NonPerishable* np = new NonPerishable();
            np->read(cin);
            
            if (cin.fail()) {
                cin.clear();
                cin.ignore(2000,'\n');
                cout << *np << endl; //this prints the error
            }
            else {
                m_items[m_noOfItems] = np;
                m_noOfItems++;
                saveRecs();
                cout << "Item added." << endl;
            }
            
            np = nullptr;
        }
    }
    
    void PosApp::listItems()const {
        double total = 0; //has garbage value & not zero and i don't know why
        //double total2 = 0;
        int zero = 1;
        //print the header of your recipet
        cout << endl;
        cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total |" << endl;
        cout << "-----|--------|--------------------|-------|---|----|---------|" << endl;
        //loop through the array and display the cost
        
        for (int i = 0; i < m_noOfItems; i++) {
            if (m_items[i]->quantity() > 0){
                cout << setfill(' ') << right << setw(4) << zero << " ";
                cout << *m_items[i] << endl;
                total += m_items[i]->cost() * m_items[i]->quantity();
                zero++;
            }
            
        }
        
        cout << "-----^--------^--------------------^-------^---^----^---------^" << endl;
        cout << setw(45) << setfill(' ') << "Total Asset: $" << "  "<< fixed << setprecision(2) << "|" << setw(14) << total << "|" << endl;
        cout << "-----------------------------------------------^--------------^" << endl;
        
        
        
    }
    
    void PosApp::truncateBillFile() {
        //removes all the data from the m_billfname
        ofstream file;
        file.open(m_billfname, ios::out | ios::trunc);
        file.close();
        
    }
    
    void PosApp::showBill() {
        fstream file;
        file.open(m_billfname, std::ios::in);
        double sum = 0.0;
        char type; //P or N
        std::string line;
        
        std::cout << "v--------------------------------------------------------v" << std::endl;
        std::cout << "| " << Date() << std::endl;
        std::cout << "| SKU    | Item Name          | Price |TX |Qty |   Total |" << std::endl;
        std::cout << "|--------|--------------------|-------|---|----|---------|" << std::endl;
        
        if (!file.eof()){
            while (!file.eof()) {//.eof() checks for return; .fail() does not work cauz return is also a "success"
                file >> type;
                file.ignore(1);
                if (type == 'P') {
                    Perishable* pr = new Perishable();
                    pr->load(file);
                    pr->write(cout, true);
                    sum += (pr->cost() * pr->quantity());
                }
                else {
                    NonPerishable* np = new NonPerishable();
                    np->load(file);
                    np->write(cout, true);
                    sum += (np->cost() * np->quantity());
                }
                cout << endl;
            }
        }
        else{
            std::cout << "|" << setw(8) << "|" << setw(20) << "|" << setw(7) << "|" << setw(3) << "|" << setw(4) << "|" << setw(9) << "|" << endl;
        }
        
        std::cout << "^--------^--------------------^-------^---^----^---------^" << std::endl;
        std::cout << "|" << setw(39) << "Total: $" << "  |" << setw(14) << fixed << setprecision(2) << sum << "|" << std::endl;
        std::cout << "^-----------------------------------------^--------------^" << std::endl;
        
        sum = 0.0;
        file.close();
        truncateBillFile();

    }
    
    void PosApp::addToBill(Item& I) {
        //adds an item to the bill with wuantity of 1
        fstream file;
        int qty = 0;
        

        
        file.open(m_billfname, std::ios::out | std::ios::app); //open file
        qty = I.quantity();
        I.quantity(1); //quantity of 1
        I.save(file); //saves the file with the quantity of 1
        
        qty--;
        
        I.quantity(qty); //save all recrods
        saveRecs();
        file.close(); //close file
    }
    
    void PosApp::POS() { //gets stuck in a loop when you just hit enter! >:(
        int x = 0;
        int index = 0;
        char sku[MAX_SKU_LEN+1];
        //cout << endl; this doesn't work here
        while (x == 0) {
            cout << "Sku: "; //prompt user
            cin.getline(sku, MAX_SKU_LEN+1);
            
            if (sku[0] == 0) {
                showBill();
                x = 1;
            }
            
            index = searchItems(sku);
            
            if (index != -1) {
                cout
                << "v------------------->" << endl
                << "| " << m_items[index]->name() << endl //print the items name
                << "^------------------->" << endl;
                
                addToBill(*m_items[index]); //add it to the bill
            }
            
            if(index == -1 && sku[0] != '\0'){
                cout << "Not found!" << endl;
            }
            
        }
   
    }
    
    PosApp::PosApp(const char* filename, const char* billfname) {
        strcpy(m_filename, filename);
        strcpy(m_billfname, billfname);
        deallocateItems();
        
        loadRecs();
    }

    void PosApp::run() {
        int found = 0;
        char s[MAX_SKU_LEN];
        bool peace = false;
        
        //how my while loop works
        //do [PERFORMED ACTIONS] while exit equals false which is changed when user enters 0
        
        while (peace == false) {
            switch (menu()) {
                case 1:
                    listItems();
                    cout << endl;
                    break;
                
                case 2:
                    addItem(true);
                    cout << endl;
                    break;
                
                case 3:
                    addItem(false);
                    cout << endl;
                    break;
                
                case 4:
                    updateQty();
                    cout << endl;
                    break;
                
                case 5:
                    cout << endl << "Please enter the SKU: ";
                    cin >> s;
                    cin.ignore();
                    
                    found = searchItems(s);
                    
                    if (found != -1) { //this is giving me a headache LMFAO
                        //if found does not equal -1 it should perform the stuff below BUT it goes to not found ...
                        cout << "v-----------------------------------v" << endl;
                        m_items[found]->write(cout, false); //write in non linear format
                        cout << "^-----------------------------------^" << endl << endl;
                    }
                    else {
                        cout << "Not found!" << endl;
                    }
                    break;
                
                case 6:
                    cout << endl; 
                    POS();
                    cout << endl;
                    break;
                
                case 0:
                    
                    peace = true;
                    break;
                
                default:
                    cout << endl << "===Invalid Selection, try again===" << endl << endl;
                    break;
            }
        }

        cout << endl << "Goodbye!" << endl;
    }
    
    
    }
    
    
//moved output text to a seperate .txt file so I could see it better when running my program
