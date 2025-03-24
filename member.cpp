#include "member.h"

member::member():
    name(""),
    membershipNum(0),
    membershipType(""),
    totalSpent(0),
    purchaseHead(nullptr),
    transactions(0)
{
    setExpDate(0, 0, 0);
}


member::member(std::string name, int membershipNum,                     //constructor
       std::string membershipType, int membershipExpDate[]) :
    name(name),
    membershipNum(membershipNum),
    membershipType(membershipType),
    totalSpent(0),
    purchaseHead(nullptr),
    transactions(0)
{
    setExpDate(membershipExpDate[0], membershipExpDate[1], membershipExpDate[2]);
}

member::member(const class p_member& otherMember):
    name(otherMember.name),
    membershipNum(otherMember.membershipNum),
    membershipType(otherMember.membershipType),
    totalSpent(otherMember.totalSpent),
    transactions(otherMember.transactions)
{
    setExpDate(otherMember.getExpDate(0), otherMember.getExpDate(1), otherMember.getExpDate(2));

    /*
    int i = 0;
    for (purchase* thisPtr = purchaseHead, *otherPtr = otherMember.purchaseHead;
         i < otherMember.transactions; i++, thisPtr = thisPtr->link, otherPtr = otherPtr->link)
    {
        thisPtr = new purchase;
        thisPtr->item = otherPtr->item;
        for (int i = 0; i < 3; i++)
            thisPtr->date[i] = otherPtr->date[i];

        thisPtr->link = purchaseHead;
        purchaseHead = thisPtr;
        thisPtr = nullptr;
    }*/

    purchaseHead = _copy_list<purchase>(otherMember.purchaseHead);
}

member::member(const class b_member& otherMember):
    name(otherMember.name),
    membershipNum(otherMember.membershipNum),
    membershipType(otherMember.membershipType),
    totalSpent(otherMember.totalSpent),
    transactions(otherMember.transactions)
{
    setExpDate(otherMember.getExpDate(0), otherMember.getExpDate(1), otherMember.getExpDate(2));
/*
    int i = 0;
    for (purchase* thisPtr = purchaseHead, *otherPtr = otherMember.purchaseHead;
         i < otherMember.transactions; i++, thisPtr = thisPtr->link, otherPtr = otherPtr->link)
    {
        thisPtr = new purchase;
        thisPtr->item = otherPtr->item;
        for (int i = 0; i < 3; i++)
            thisPtr->date[i] = otherPtr->date[i];

        thisPtr->link = purchaseHead;
        purchaseHead = thisPtr;
        thisPtr = nullptr;
    }*/

    purchaseHead = _copy_list<purchase>(otherMember.purchaseHead);
}

member::~member() {
    int i = 0;
    for (node<purchase>* current = purchaseHead; i < transactions ; i++)
    {
        node<purchase>* placehold = current->_next;
        delete current;
        current = placehold;
        placehold = nullptr;
    }
    _clear_list(purchaseHead);

}
/*
void member::reportPurchases() {
    int i = 0;
    for (node<purchase>* current = purchaseHead; i < transactions; i++, current = current->_next)
    {
<<<<<<< HEAD
        std::cout << current->date[0] << "/" << current->date[1] << "/" << current->date[2] << std::endl;
        std::cout << "Product: " << current->item.getName() << std::endl;
        std::cout << "Price: " << current->item.getPrice() << std::endl;
        std::cout << "Quantity: " << current->item.getQuantity() << std::endl;
=======
        std::cout << current->_item.date[0] << "/" << current->_item.date[1] << "/" << current->_item.date[2] << std::endl;
        std::cout << "Product: " << current->_item.item.name << std::endl;
        std::cout << "Price: " << current->_item.item.price << std::endl;
        std::cout << "Quantity: " << current->_item.quantity << std::endl;
>>>>>>> 6a7f705e46a782fbcca26ef9d2333fa6ddeb6e67
        std::cout << "---------------------------------------------\n";
    }
}*/


bool member::operator ==(const b_member& otherMember) {
    if (membershipNum == otherMember.membershipNum)
        return true;
    else
        return false;
}

bool member::operator ==(const p_member& otherMember) {
    if (membershipNum == otherMember.getMembershipNum())
        return true;
    else
        return false;
}


void member::setName(std::string name) {
    this->name = name;
}


void member::setMembershipNum(int membershipNum) {
    this->membershipNum = membershipNum;
}


void member::setType(std::string membershipType) {
    this->membershipType = membershipType;
}


void member::setExpDate(int month, int day, int year) {
    this->membershipExpDate[0] = month;
    this->membershipExpDate[1] = day;
    this->membershipExpDate[2] = year;
}


void member::setSpent(double totalSpent) {
    this->totalSpent = totalSpent;
}


void member::setPurchaseHead(node<purchase> *purchaseHead) {
    this->purchaseHead = purchaseHead;
}

void member::setTransactions(int transactions) {
    this->transactions = transactions;
}


member* member::clone(const b_member& otherMember) {
    member* newMember = new b_member(otherMember);

    return newMember;
}


member* member::clone(const p_member& otherMember) {
    member* newMember = new p_member(otherMember);

    return newMember;
}


p_member::~p_member() {
    int i = 0;
    for (node<purchase>* current = getPurchaseHead(); i < getTransactions() ; i++)
    {
        node<purchase>* placehold = current->_next;
        delete current;
        current = placehold;
        placehold = nullptr;
    }
}

bool p_member::recommendSwitch() {
    double annualCostB, annualCostP;

    annualCostB = getSpent() + (getSpent() * SALES_TAX) + BASIC_DUE;
    annualCostP = getSpent() + (getSpent() * SALES_TAX) - (getSpent() * REBATE) + PREFERRED_DUE;

    if (annualCostB < annualCostP)
        return true;
    else
        return false;
}



void p_member::spend(const product& item, int date[]) {
    node<purchase>* newPurchase = new node<purchase>;
    newPurchase->_item.item = item;
    for (int i = 0; i < 3; i++)
        newPurchase->_item.date[i] = date[i];

    newPurchase->_next = getPurchaseHead();
    setPurchaseHead(newPurchase);
    newPurchase = nullptr;

    setSpent(getSpent() + getPurchaseHead()->_item.item.getPrice() * getPurchaseHead()->_item.item.getQuantity());
    setTransactions(getTransactions() + 1);

    calcRebate();
}


void p_member::calcRebate() {
    rebateAmount = getSpent() * REBATE;
}


b_member::~b_member() {
    int i = 0;
    for (node<purchase>* current = getPurchaseHead(); i < getTransactions() ; i++)
    {
        node<purchase>* placehold = current->_next;
        delete current;
        current = placehold;
        placehold = nullptr;
    }
}

bool b_member::recommendSwitch() {
    double annualCostB, annualCostP;

    annualCostB = getSpent() + (getSpent() * SALES_TAX) + BASIC_DUE;
    annualCostP = getSpent() + (getSpent() * SALES_TAX) - (getSpent() * REBATE) + PREFERRED_DUE;

    if (annualCostB > annualCostP)
        return true;
    else
        return false;
}


void b_member::spend(const product& item, int date[]) {
    node<purchase>* newPurchase = new node<purchase>;
    newPurchase->_item.item = item;
    for (int i = 0; i < 3; i++)
        newPurchase->_item.date[i] = date[i];

    newPurchase->_next = getPurchaseHead();
    setPurchaseHead(newPurchase);
    newPurchase = nullptr;

    setSpent(getSpent() + getPurchaseHead()->_item.item.getPrice() * getPurchaseHead()->_item.item.getQuantity());
    setTransactions(getTransactions() + 1);
}
