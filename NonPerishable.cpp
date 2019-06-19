//Alejandra Perez
//aeperez@myseneca.ca
//#035174150
#define _CRT_SECURE_NO_WARNINGS
// lib includes
#include "NonPerishable.h"
#include "Error.h"
#include "PosIO.h"
#include "POS.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip> //allows you to use setprecision

using namespace std;
namespace ict {
    bool NonPerishable::ok() const {
        //return m_err with NO message (clear it)
        return (m_err.isClear()); //use isclear from item class!!

    }
    
    void NonPerishable::error(const char* message) {
        //setting the error message to the one that is give by the value const char* message
        m_err.message(message);
    }
    
    char NonPerishable::signature() const {
        //return the letter N
        return 'N';
        
    }
    
    std::fstream& NonPerishable::save(std::fstream &file) const{
        
        /*In the file print out the signature, the sku, name, price, if the item will be taxed, the quantity of the item*/
        //accessing all this from your Item class (remeber that NonPerisable can access info from the class Item
        
        file << signature() << ',' << sku() << ',' << name() << ',' << price() << ',' << taxed() << ',' << quantity();
        
        //return the file with all this information
        return file;
    }
    
    std::fstream& NonPerishable::load(std::fstream& file) {
        //delcare temp values
        char ts[MAX_SKU_LEN+1];
        char tn[80]; //might cause problems double check
        double tp;
        bool tt ;
        int quant;
        
        
    
        //this will read all the fields from the file  & then set
        /*the first process below prompst the user to insert the value for each variable
         waits for them to input it and then inputs it into the file*/
        //sku
        //the best way to understand getline() is with this example (from online source):
        /*// istream::getline example
         #include <iostream>     // std::cin, std::cout
         
         int main () {
         char name[256], title[256];
         
         std::cout << "Please, enter your name: ";
         std::cin.getline (name,256);
         
         std::cout << "Please, enter your favourite movie: ";
         std::cin.getline (title,256);
         
         std::cout << name << "'s favourite movie is " << title;
         
         return 0;
         }*/
        
        //in this case the getline is coming from the system (or from the set up provided for us)
        
        file.getline(ts, MAX_SKU_LEN, ',');
        
        
        //name
        file.getline(tn, 80, ',');
        //file >> tn;
        
        
        //price
        file >> tp;
        file.ignore();
        
      
        //taxed
        file >> tt;
        file.ignore();
        
        //quantity
        file >> quant;
       //file.ignore();


        //load everything
        sku(ts);
        name(tn);
        price(tp);
        taxed(tt);
        quantity(quant);
        
        //return the file:
        
        return file;
        
        

    }
    
/*PREVIOUS WRITE AND READ DID NOT WORK >: ( */


ostream& NonPerishable::write(ostream& ostr, bool linear)const{
    //if the object is not ok() it simply prints the m_err using ostr and retursn ostr
    // if the object is ok() then depending on the value of linear, write prints the item in different format
    if (!ok()){
      ostr << (const char*)m_err;
    }
    else{
        //basically makes everything look pretty
      if (linear){//if linear format is true
        ostr << "| ";
        ostr.width(MAX_SKU_LEN);
        ostr.fill(' ');
        ostr << left << Item::sku() << "|";
        if (strlen(Item::name()) < 20){
          ostr.width(20);
          ostr.fill(' ');
          ostr << left << Item::name();
        }
        else{
          printf("%.20s", Item::name());
        }
        ostr << "|";
        ostr.width(7);
        ostr << right << fixed << setprecision(2);
        ostr << Item::price() << "|";
        ostr.width(2);
        ostr << (Item::taxed() ? "T" : " ");
        ostr << signature();
        ostr << "|";
        ostr.width(4);
        ostr << Item::quantity() << "|";
        ostr.width(9);
        ostr << Item::quantity() * Item::cost() << "|";
      }
      else{//this will be the linear
        ostr << "Name:" << endl;
        ostr << Item::name() << endl;
        ostr << "Sku: " << Item::sku() << endl;
        ostr << "Price: " << Item::price() << endl;
        ostr << "Price after tax: ";
        if (Item::taxed()){
          ostr << Item::cost() << endl;
          ostr << "Quantity: " << Item::quantity() << endl;
          ostr << "Total Cost: " << fixed << setprecision(2) << Item::quantity() * Item::cost() << endl;
        }
        else{
          ostr << "N/A" << endl;
          ostr << "Quantity: " << Item::quantity() << endl;
          ostr << "Total Cost: " << fixed << setprecision(2) << Item::quantity() * Item::price() << endl;
        }
      }
    }

    return ostr;
  }

  std::istream& NonPerishable::read(std::istream& is){
    //recieves the values using istream
      //basically this asked the user for the information in milestone 4
    char tsku[MAX_SKU_LEN+1];
    char tname[100];
    double tprice;
    char ttaxed; //will accept only 'y' or 'n'
    int tquantity;

    m_err.clear();

    if (signature() == 'N') {
      cout << endl << "Item Entry:" << endl; // NonPerishable
    }
    else{
      cout << endl << "Perishable Item Entry:" << endl; // Perishable
    }

    cout << "Sku: ";
    is >> tsku;

    if (!is.fail()){//----sku succss
      Item::sku(tsku);
      cout << "Name:" << endl;
      is >> tname;

      if (!is.fail()){//----name success
        Item::name(tname);
        cout << "Price: ";
        is >> tprice;

        if (!is.fail()){//----price success
          Item::price(tprice);
          cout << "Taxed: ";
          is >> ttaxed;
          if (!is.fail() && (ttaxed=='y' || ttaxed=='n')){//----taxed success
            if (ttaxed =='y'){
              Item::taxed(true);
            }
            else{
              Item::taxed(false);
            }
            cout << "Quantity: ";
            is >> tquantity;
            if (!is.fail()){//----is success
              Item::quantity(tquantity);
            }
            else{//----quantity failed
              error("Invalid Quantity Entry");
            }
          }
          else{//----taxed failed
            error("Invalid Taxed Entry, (y)es or (n)o");
            is.setstate(ios::failbit);
          }
        }
        else{//----price failed
          error("Invalid Price Entry");
        }
      }//----name cant fail
    }//----sku cant fail

    return is;
  }
    
    
    
    
    
    
}

