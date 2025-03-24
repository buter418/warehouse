#ifndef PRODUCT_H
#define PRODUCT_H


#include "linked_list_functions.h"
#include "node.h"


//-------------------------------------------------------------
//please write assignment operator to ensure proper copy in product list
//-------------------------------------------------------------


#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QTableWidget>
class product
{
public:
    product(std::string name = "", double price = 0, int quantity = 0);

    std::string getName() {return name;}
    double getPrice() {return price;}
    int getQuantity() {return quantity;}

    double getRevenue() {return price * quantity;}

    void setName(std::string name);
    void setPrice(double price);
    void setQuantity(int quantity);
    void increaseQuantity(int amount = 1);

    bool operator== (const product& otherProduct);


private:
    std::string name;
    double price;
    int quantity;
};

#endif // PRODUCT_H
