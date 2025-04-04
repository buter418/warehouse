#include "product.h"

product::product(std::string name, double price, int quantity) {
    this->name = name;
    this->price = price;
    this->quantity = quantity;
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
    return (this->name == otherProduct.name);
}

//Z>A
bool product::operator>= (const product& otherProduct){
    return this->name >= otherProduct.getName();
}

//A<Z
bool product::operator<= (const product& otherProduct){
    return this->name <= otherProduct.getName();
}

product& product::operator+= (const product& otherProduct){
    quantity += otherProduct.quantity;
    return *this;
}