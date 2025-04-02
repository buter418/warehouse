#include "product.h"

product::product(std::string name, double price, int quantity) {
    this->name = name;
    this->price = price;
    this->quantity = quantity;
}

product::product(const product& otherProd) {
    this->name = otherProd.name;
    this->price = otherProd.price;
    this->quantity = otherProd.quantity;
}

void product::setName(std::string name) {
    this->name = name;
}

void product::setPrice(double price) {
    this->price = price;
}

void product::setQuantity(int quantity) {
    this->quantity = quantity;
}

void product::increaseQuantity(int amount) {
    this->quantity += amount;
}

bool product::operator== (const product& otherProduct) {
    return (this->name == otherProduct.name && this->price ==otherProduct.price);
}

bool product::operator>= (const product& otherProduct){
    return this->name >= otherProduct.getName();
}

bool product::operator<= (const product& otherProduct){
    return this->name <= otherProduct.getName();
}

product& product::operator+= (const product& otherProduct){
    quantity += otherProduct.quantity;
    return *this;
}

product& product::operator= (const product& otherProd) {
    name = otherProd.name;
    price = otherProd.price;
    quantity = otherProd.quantity;

    return *this;
}
