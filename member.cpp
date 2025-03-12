#include "member.h"


member::~member() {                                                     //destructor
    delete link;

    int i = 0;
    for (purchase* current = purchaseHead; i < transactions ; i++)
    {
        purchase* placehold = current->link;
        delete current;
        current = placehold;
        placehold = nullptr;
    }
}


void member::reportPurchases() {
    int i = 0;
    for (purchase* current = purchaseHead; i < transactions; i++, current = current->link)
    {
        std::cout << current->date[0] << "/" << current->date[1] << "/" << current->date[2] << std::endl;
        std::cout << "Product: " << current->item.name << std::endl;
        std::cout << "Price: " << current->item.price << std::endl;
        std::cout << "Quantity: " << current->quantity << std::endl;
        std::cout << "---------------------------------------------\n";
    }
}


bool member::recommendSwitch() {

}
