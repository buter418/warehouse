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
        product* newProd = new product(name, price, quantity);

        addProduct(newProd);

        if (infile.eof())
            break;
    }

    infile.close();
}

product_list::product_list(const product_list& otherList) {
    size = otherList.size;
    setDate(otherList.getMonth(), otherList.getDay(), otherList.getYear());

    for (product* current = otherList.head; current != nullptr; current = current->getLink())
    {
        product* newProd = new product(current->getName(), current->getPrice(), current->getQuantity());

        addProduct(newProd);
    }
}

product_list::~product_list() {
    int i = 0;
    for (product* current = head; i < size ; i++)
    {
        product* placehold = current->getLink();
        delete current;
        current = placehold;
        placehold = nullptr;
    }
}

void product_list::setHead(product* head) {
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

product* product_list::checkProducts(product *prod) {
    for (product* current = head; current != nullptr; current = current->getLink())
        if (*current == *prod)
            return current;

    return nullptr;
}

void product_list::addProduct(product *prod) {
    product* addSpot = checkProducts(prod);

    if (!addSpot)
    {
        prod->setLink(head);
        head = prod;
        incSize();
    }
    else
    {
        addSpot->increaseQuantity(prod->getQuantity());
    }
}

double product_list::calcTotal() {
    double result = 0;

    for (product* current = head; current != nullptr; current = current->getLink())
    {
        result += current->getPrice() * current->getQuantity();
    }

    return result;
}

product_list& product_list::operator= (const product_list& otherList) {
    size = otherList.size;
    setDate(otherList.getMonth(), otherList.getDay(), otherList.getYear());

    for (product* current = otherList.head; current != nullptr; current = current->getLink())
    {
        product* newProd = new product(current->getName(), current->getPrice(), current->getQuantity());

        addProduct(newProd);
    }

    return *this;
}

product_list operator+ (const product_list& list1, const product_list& list2) {
    product_list newList = list1;

    for (product* current = list2.head; current != nullptr; current = current->getLink()){
        newList.addProduct(current);
    }

    return newList;
}

