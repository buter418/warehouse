#ifndef PRODUCT_H
#define PRODUCT_H


#include "linked_list_functions.h"
#include "node.h"


//-------------------------------------------------------------
//please write assignment operator to ensure proper copy in product list
//-------------------------------------------------------------


#include <iostream>
class product
{
public:
    product(std::string name = "", double price = 0, int quantity = 0);

    string getName() const{return name;}
    double getPrice() const{return price;}
    int getQuantity() const{return quantity;}

    void setName(string name);
    void setPrice(double price);
    void setQuantity(int quantity);
    void increaseQuantity(int amount = 1);

    friend ostream& operator<<(ostream& outs, product pt_this){
        outs << pt_this.getName() << "|"
             << pt_this.getPrice() << "|"
             << pt_this.getQuantity();
        return outs;
    }
    bool operator== (const product& otherProduct);
    bool operator>= (const product& otherProduct);
    bool operator<= (const product& otherProduct);

    product& operator+= (const product& otherProduct);


private:
    std::string name;
    double price;
    int quantity;
};




#endif // PRODUCT_H
