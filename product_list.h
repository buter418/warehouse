#ifndef PRODUCT_LIST_H
#define PRODUCT_LIST_H

#include "product.h"
#include "member.h"
#include "linked_list_functions.h"
#include "list_sorted.h"
#include "node.h"

class MainWindow;


class product_list
{
public:

    /******************************
    ** CONSTRUCTORS & DESTRUCTOR **
    ******************************/
    product_list(): head(nullptr), size(0) {setDate(0, 0, 0);}                      //Default constructor
    product_list(const QString filename,
                 List<p_member> allMembers,
                 List<product>& allProduct,
                 node<p_member>*& todayMembers);                //Constructor from filename
    product_list(const product_list& otherList);                                    //Copy constructor
    ~product_list();                                                                //destructor

    /***************
    ** ACCESSORS **
    ***************/
    node<product>* getHead() const {return head;}
    int getSize() const {return size;}
    int getMonth() const {return date[0];}
    int getDay() const {return date[1];}
    int getYear() const {return date[2];}
    std::string getDate() const;
    bool isEmpty();

    node<product>* checkProducts(product prod);
    double calcTotal();

    void setSalesTable(QTableWidget* tableWidget, List<p_member> allMembers, node<p_member>* todayMembers);
    void setYearTable(QTableWidget* tableWidget);


    /***************
    /** MUTATORS **
    ***************/
    void setHead(node<product>* head);
    void setSize(int size);
    void incSize(int amount = 1);
    void setDate(int month, int day, int year);

    void addProduct(product prod, bool unique = false);

    product_list& operator= (const product_list& otherList);
    friend product_list operator+ (const product_list& list1, const product_list& list2);

private:
    node<product>* head;
    int size;
    int date[3];
};

#endif // PRODUCT_LIST_H
