#include "product.h"

product::product(std::string name, double price, int quantity) {
    this->name = name;
    this->price = price;
    this->quantity = quantity;
    link = nullptr;
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

void product::setLink(product *link) {
    this->link = link;
}

bool product::operator== (const product& otherProduct) {
    if (this->name == otherProduct.name)
        return true;
    else
        return false;
}
