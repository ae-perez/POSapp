//Alejandra Perez
//aeperez@myseneca.ca
//#035174150

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
#include <cstring>
using namespace std;
#include "Date.h"
#include "POS.h"


namespace ict{
    
/****************************PRIVATE MEMBER FUNCTIONS****************************/

    void Date::set(){
    time_t t = time(NULL);
    tm lt = *localtime(&t);
    m_day = lt.tm_mday;
    m_mon = lt.tm_mon + 1;
    m_year = lt.tm_year + 1900;
    if (dateOnly()){
      m_hour = m_min = 0;
    }
    else{
      m_hour = lt.tm_hour;
      m_min = lt.tm_min;
    }
  }

    int Date::value()const{
    return m_year * 535680 + m_mon * 44640 + m_day * 1440 + m_hour * 60 + m_min;
  }

    int Date::mdays()const{
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
    mon--;
    return days[mon] + int((mon == 1)*((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
  }
    
    void Date::errCode(int errorCode){
        //one of the defines is passed to errorCode and then set to m_readErrorCode
        m_readErrorCode = errorCode;
        
    }
    
    void Date::set(int year, int mon, int day, int hour, int min) {
        m_year = year;
        m_mon = mon;
        m_day = day;
        m_hour = hour;
        m_min = min;
        m_readErrorCode = NO_ERROR;
        
        
    }
    
    
/****************************PUBLIC CONSTRUCTORS****************************/
    
    Date::Date() {
        m_dateonly = false;
        set();
        
    }
    
    Date::Date(int year, int mon, int day) {
        //sets m_dateonly to true
        m_dateonly = true;
        
        //accepts three int values to set m_year, m_mon, m_day
        m_year = year;
        m_mon = mon;
        m_day = day;
        
        //sets m_hour,m_min to 0
        m_hour = 0;
        m_min = 0;
    }
    
    Date::Date(int year, int mon, int day, int hour, int min) {
        //set m_dateonly to false
        m_dateonly = false;
        
        //accepts 5 ints to set
        m_year = year;
        m_mon = mon;
        m_day = day;
        m_hour = hour;
        m_min = min;
        //sets m_readerrorcode to no error
        m_readErrorCode = NO_ERROR;
        
        //min has default value of d (put in .h file)
        
    }
    
    
/****************************PUBLIC OPERATORS****************************/
    
    
    bool Date::operator==(const Date& D) const {
        return this->value() == D.value();
    }
    
    bool Date::operator!=(const Date&D) const {
        return this->value() != D.value();
    }
    
    bool Date::operator<(const Date& D) const {
        return this->value() < D.value();
    }
    
    bool Date::operator>(const Date& D) const {
        return this->value() > D.value();
    }
    
    bool Date::operator<=(const Date& D) const {
        return this->value() <= D.value();
    }
    
    bool Date::operator>=(const Date& D) const {
        return this->value() >= D.value();
    }
    
    
/****************************PUBLIC METHOD FUNCTIONS****************************/
    
    int Date::errCode() const {
        return m_readErrorCode;
    }
    
    bool Date::bad() const {
        return m_readErrorCode != 0 ? true : false;
    }
    
    bool Date::dateOnly() const {
        return m_dateonly;
        
    }
    
    bool Date::dateOnly(bool value) {
        m_dateonly = value;
        if (value == true) {
            m_hour = 0;
            m_min = 0;
        }
        
        return m_dateonly; //uuuuuh is this right?
    } // NOT SURE ABOUT THIS

    
/****************************ISTREAM/OSTREAM METHODS****************************/
    
    std::istream& ict::Date::read(std::istream& is) {
        
        char slash; // holds /
        char comma; // ,
        char semi; // :
        if (dateOnly() == true) {
            is >> m_year >> slash >> m_mon >> slash >> m_day;
        }
        
        else {
            is >> m_year >> slash >> m_mon >> slash >> m_day >> comma >> m_hour >> semi >> m_min;
        }
        
        if (is.fail()) {
            m_readErrorCode = CIN_FAILED;
        }
        
        else { //-------------
            if (m_year > MAX_YEAR || m_year < MIN_YEAR) {
                // four digit integer
                int count = 0;
                int year = m_year;
                while (count > 0) {
                    year = year / 10;
                    count++;
                }
                if (count != 4) {
                    m_readErrorCode = YEAR_ERROR;
                }
            }
            else if (m_mon > 12 || m_mon < 1) {// month between 1 and 12
                m_readErrorCode = MON_ERROR;
            }
            else if (m_day > (Date::mdays()) || m_day < 1) { // leap year accomaded
                m_readErrorCode = DAY_ERROR;
            }
            else if (m_hour < 0 || m_hour > 23) { // hour between 0 and 23
                m_readErrorCode = HOUR_ERROR;
            }
            else if (m_min < 0 || m_min > 59) { // min between 0 and 59
                m_readErrorCode = MIN_ERROR;
            }
            else {
                m_readErrorCode = NO_ERROR;// all numbers good
            }

            
        }       //-------------
        
        return is;
    } //not complete
    
    std::ostream& ict::Date::write(std::ostream& ostr) const {
        if (dateOnly()) {
            //writes data to ostream object YYYY/MM/DD
            ostr << m_year << '/';
            ostr.fill('0');
            ostr.width(2);
            ostr << m_mon << '/';
            ostr.fill('0');
            ostr.width(2);
            ostr << m_day;
        }
        else {
            // if dateonly false YYYY/MM/DD, hh:mm
            ostr << m_year << '/';
            ostr.fill('0');
            ostr.width(2);
            ostr << m_mon << '/';
            ostr.fill('0');
            ostr.width(2); 
            ostr << m_day << ", "<< m_hour << ':' << m_min;
        }
        //returns reference to ostream object
        return ostr;

    }
    
    

    
    
/****************************ISTREAM/OSTREAM NONMEMBERS****************************/

    std::ostream& operator<<(std::ostream& os, const Date& D) {
        D.write(os);
        return (os);
    }
    
    std::istream& operator>>(std::istream& is, Date& D) {
        D.read(is);
        return (is);
    }

}

