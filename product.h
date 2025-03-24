#ifndef PRODUCT_H
#define PRODUCT_H


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
    product* getLink() {return link;}

    double getRevenue() {return price * quantity;}

    void setName(std::string name);
    void setPrice(double price);
    void setQuantity(int quantity);
    void increaseQuantity(int amount = 1);
    void setLink(product* link);

    bool operator== (const product& otherProduct);


private:
    std::string name;
    double price;
    int quantity;
    product* link;
};

#endif // PRODUCT_H
