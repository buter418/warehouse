#include "member.h"

//forward declaration
#include "p_member.h"




//*********************************
//* Constructor
//*********************************
member::member(const p_member& otherMember):                            //copy constructor for p_members for switching memberships
                name(otherMember.getName()),
                membershipNum(otherMember.getMembershipNum()),
                membershipType(otherMember.getType()),
                totalSpent(otherMember.getSpent()),
                transactions(otherMember.getTransactions())
{
    for (int i = 0; i < 3; i++)
        this->membershipExpDate[i] = otherMember.getExpDate()[i];

    purchaseHead = _copy_list<purchase>(otherMember.getHead());
}








//*********************************
//* Destructor
//*********************************
member::~member() {                                                     
    _clear_list(purchaseHead);
}


//*********************************
//* 2 assignment operator
//*********************************
member& member::operator =(const member& otherMember) {
    name = otherMember.name;
    membershipNum = otherMember.membershipNum;
    membershipType = otherMember.membershipType;
    totalSpent = otherMember.totalSpent;
    transactions = otherMember.transactions;

    for (int i = 0; i < 3; i++)
        this->membershipExpDate[i] = otherMember.membershipExpDate[i];

    purchaseHead = _copy_list<purchase>(otherMember.purchaseHead);

    return *this;
}
member& member::operator =(const p_member& otherMember) {
    name = otherMember.name;
    membershipNum = otherMember.membershipNum;
    membershipType = otherMember.membershipType;
    totalSpent = otherMember.totalSpent;
    transactions = otherMember.transactions;

    for (int i = 0; i < 3; i++)
        this->membershipExpDate[i] = otherMember.membershipExpDate[i];

    purchaseHead = _copy_list<purchase>(otherMember.purchaseHead);

    return *this;
}


//*********************************
//* Comparison Operator
//*********************************
bool member::operator ==(const member& otherMember) {
    return (membershipNum == otherMember.membershipNum);
}
bool member::operator ==(const p_member& otherMember) {
    return (membershipNum == otherMember.membershipNum);
}



//*********************************
//* Mutators
//*********************************
void member::setExpDate(int membershipExpDate[3]) {
    for (int i = 0; i < 3; i++)
        this->membershipExpDate[i] = membershipExpDate[i];
}
void member::setExpDate(const int membershipExpDate[3]) {
    for (int i = 0; i < 3; i++)
        this->membershipExpDate[i] = membershipExpDate[i];
}

//*********************************
//* other member functions
//*********************************
void member::reportPurchases() {
    for (node<purchase>* current = purchaseHead; current != nullptr; current = current->_next){
        std::cout << current->_item.date[0] << "/" << current->_item.date[1] << "/" << current->_item.date[2] << std::endl;
        std::cout << "Product: " << current->_item.item.getName() << std::endl;
        std::cout << "Price: " << current->_item.item.getPrice() << std::endl;
        std::cout << "Quantity: " << current->_item.quantity << std::endl;
        std::cout << "---------------------------------------------\n";
    }
}


//recommendation for switching between basic and prime member
bool member::recommendSwitch() {
    double annualCostB, annualCostP;

    annualCostB = totalSpent + (totalSpent * SALES_TAX) + BASIC_DUE;
    annualCostP = totalSpent + (totalSpent * SALES_TAX) - (totalSpent * REBATE) + PREFERRED_DUE;

    if (annualCostB > annualCostP)
        return true;
    else
        return false;
}


void member::spend(const product& item, int quantity, int date[]) {
    purchase newPurchase = purchase();
    newPurchase.item = item;
    newPurchase.quantity = quantity;
    for (int i = 0; i < 3; i++)
        newPurchase.date[i] = date[i];

    insert_head<purchase>(purchaseHead, newPurchase);

    totalSpent += purchaseHead->_item.item.getPrice() * purchaseHead->_item.quantity;
    transactions++;
}
