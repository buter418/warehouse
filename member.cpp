#include "member.h"


member::~member() {                                                     //destructor
    _clear_list(purchaseHead);
}


void member::reportPurchases() {
    int i = 0;
    for (node<purchase>* current = purchaseHead; i < transactions; i++, current = current->_next)
    {
        std::cout << current->_item.date[0] << "/" << current->_item.date[1] << "/" << current->_item.date[2] << std::endl;
        std::cout << "Product: " << current->_item.item.name << std::endl;
        std::cout << "Price: " << current->_item.item.price << std::endl;
        std::cout << "Quantity: " << current->_item.quantity << std::endl;
        std::cout << "---------------------------------------------\n";
    }
}


bool member::recommendSwitch() {
    double annualCostB, annualCostP;

    annualCostB = totalSpent + (totalSpent * SALES_TAX) + BASIC_DUE;
    annualCostP = totalSpent + (totalSpent * SALES_TAX) - (totalSpent * REBATE) + PREFERRED_DUE;

    if (annualCostB > annualCostP)
        return true;
    else
        false;
}


bool member::operator ==(const member& otherMember) {
    if (membershipNum == otherMember.membershipNum)
        return true;
    else
        false;
}

bool member::operator ==(const p_member& otherMember) {
    if (membershipNum == otherMember.membershipNum)
        return true;
    else
        false;
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


void member::setExpDate(int membershipExpDate[3]) {
    for (int i = 0; i < 3; i++)
        this->membershipExpDate[i] = membershipExpDate[i];
}


void member::setSpent(int totalSpent) {
    this->totalSpent = totalSpent;
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


bool p_member::recommendSwitch() {
    return !member::recommendSwitch();
}


p_member& p_member::operator =(const p_member& otherMember) {
    name = otherMember.name;
    membershipNum = otherMember.membershipNum;
    membershipType = otherMember.membershipType;
    totalSpent = otherMember.totalSpent;
    transactions = otherMember.transactions;
    rebateAmount = otherMember.rebateAmount;

    for (int i = 0; i < 3; i++)
        this->membershipExpDate[i] = otherMember.membershipExpDate[i];

    purchaseHead = _copy_list<purchase>(otherMember.purchaseHead);

    return *this;
}


p_member& p_member::operator =(const member& otherMember) {
    name = otherMember.name;
    membershipNum = otherMember.membershipNum;
    membershipType = otherMember.membershipType;
    totalSpent = otherMember.totalSpent;
    transactions = otherMember.transactions;

    for (int i = 0; i < 3; i++)
        this->membershipExpDate[i] = otherMember.membershipExpDate[i];

    purchaseHead = _copy_list<purchase>(otherMember.purchaseHead);

    calcRebate();

    return *this;
}


void p_member::spend(const product& item, int quantity, int date[]) {
    member::spend(item, quantity, date);

    calcRebate();
}


void p_member::calcRebate() {
    rebateAmount = totalSpent * REBATE;
}
