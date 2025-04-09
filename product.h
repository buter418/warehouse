#ifndef PRODUCT_H
#define PRODUCT_H

#include "linked_list_functions.h"
#include "node.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>

//-------------------------------------------------------------
//please write assignment operator to ensure proper copy in product list
//-------------------------------------------------------------

#include <QFile>
#include <QStringList>
#include <QTableWidget>
#include <QTextStream>
#include <iostream>
class product
{
public:
    /******************************
    ** CONSTRUCTORS & DESTRUCTOR **
    ******************************/
    product(std::string name = "", double price = 0, int quantity = 0); //Default constructor
    product(const product &otherProd);                                  //Copy Constructor

    /***************
    ** ACCESSORS **
    ***************/
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    double getRevenue() { return price * quantity; }

    /***************
    ** MUTATORS **
    ***************/
    void setName(std::string name);
    void setPrice(double price);
    void setQuantity(int quantity);
    void increaseQuantity(int amount = 1);

    friend ostream &operator<<(ostream &outs, product pt_this)
    {
        outs << pt_this.getName() << "|" << pt_this.getPrice() << "|" << pt_this.getQuantity();

        return outs;
    }

    bool operator==(const product &otherProduct);
    bool operator>=(const product &otherProduct);
    bool operator<=(const product &otherProduct);

    product &operator+=(const product &otherProduct);

    product &operator=(const product &otherProd);

private:
    std::string name;
    double price;
    int quantity;
};

#endif // PRODUCT_H
