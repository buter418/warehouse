#include "product_list.h"

#include <fstream>

//To do: Implement member container class so that can use the names collected in this method
product_list::product_list(std::string filename) {
    std::ifstream infile;
    infile.open(filename);

    while (true)
    {
        int month, day, year, id, quantity;
        double price;
        std::string name, monthStr, dayStr, yearStr, idStr, quantityStr, priceStr;

        //Get date
        std::getline(infile, monthStr, '/');
        std::getline(infile, dayStr, '/');
        std::getline(infile, yearStr);
        month = std::stoi(monthStr);
        day = std::stoi(dayStr);
        year = std::stoi(yearStr);

        //Get member id
        std::getline(infile, idStr);
        id = std::stoi(idStr);

        //Get product name
        std::getline(infile, name);

        //Get price
        std::getline(infile, priceStr, '\t');
        price = std::stoi(priceStr);

        //Get quantity
        std::getline(infile, quantityStr);
        quantity = std::stoi(quantityStr);

        setDate(month, day, year);
        product newProd = product(name, price, quantity);

        addProduct(newProd);

        if (infile.eof())
            break;
    }

    infile.close();
}

product_list::product_list(const product_list& otherList) {
    size = otherList.size;
    setDate(otherList.getMonth(), otherList.getDay(), otherList.getYear());

    for (node<product>* current = otherList.head; current != nullptr; current = current->_next){

        //-------------------------------------------------------
        //make sure no ptr in product, or it will be shallow copy
        product newProd = current->_item;
        //-------------------------------------------------------

        addProduct(newProd);
    }
}

product_list::~product_list() {
    _clear_list<product>(head);
}

void product_list::setHead(node<product>* head) {
    this->head = head;
}

void product_list::setSize(int size) {
    this->size = size;
}

void product_list::incSize(int amount) {
    size += amount;
}

void product_list::setDate(int month, int day, int year) {
    date[0] = month;
    date[1] = day;
    date[2] = year;
}


//check if repeated product exist if so return ptr to that repeated product
node<product>* product_list::checkProducts(product prod) {
    return _search_list<product>(head, prod);
}

void product_list::addProduct(product prod) {
    node<product>* addSpot = checkProducts(prod);

    //if no repeated product
    if (!addSpot){
        _insert_head<product>(head, prod);
        incSize();
    }
    else{
        addSpot->_item.increaseQuantity(prod.getQuantity());
    }
}

double product_list::calcTotal() {
    double result = 0;

    for (node<product>* current = head; current != nullptr; current = current->_next)
        result += current->_item.getPrice() * current->_item.getQuantity();

    return result;
}

product_list& product_list::operator= (const product_list& otherList) {
    size = otherList.size;
    setDate(otherList.getMonth(), otherList.getDay(), otherList.getYear());

    for (node<product>* current = otherList.head; current != nullptr; current = current->_next){
        product newProd = current->_item;
        addProduct(newProd);
    }

    return *this;
}

product_list operator+ (const product_list& list1, const product_list& list2) {
    product_list newList = list1;

    for (node<product>* current = list2.head; current != nullptr; current = current->_next)
        newList.addProduct(current->_item);

    return newList;
}

