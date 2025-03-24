#ifndef PRODUCT_LIST_H
#define PRODUCT_LIST_H

#include "product.h"
#include "member.h"
#include "linked_list_functions.h"
#include "node.h"

class MainWindow;


class product_list
{
public:
    product_list(): head(nullptr), size(0) {setDate(0, 0, 0);}
    product_list(const QString filename/*, member** todayMembers*/);
    product_list(const product_list& otherList);
    ~product_list();

    node<product>* getHead() const {return head;}
    int getSize() const {return size;}
    int getMonth() const {return date[0];}
    int getDay() const {return date[1];}
    int getYear() const {return date[2];}
    bool isEmpty();

    void setHead(node<product>* head);
    void setSize(int size);
    void incSize(int amount = 1);
    void setDate(int month, int day, int year);

    node<product>* checkProducts(product prod);
    void addProduct(product prod);
    double calcTotal();

    void setSalesTable(QTableWidget* tableWidget);
    void setYearTable(QTableWidget* tableWidget);

    product_list& operator= (const product_list& otherList);

    friend product_list operator+ (const product_list& list1, const product_list& list2);

private:
    node<product>* head;
    int size;
    int date[3];
};

#endif // PRODUCT_LIST_H
