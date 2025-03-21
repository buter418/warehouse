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


void member::setLink(member* link) {
    this->link = link;
}


void member::spend(const product& item, int quantity, int date[]) {
    purchase* newPurchase = new purchase;
    newPurchase->item = item;
    newPurchase->quantity = quantity;
    for (int i = 0; i < 3; i++)
        newPurchase->date[i] = date[i];

    newPurchase->link = purchaseHead;
    purchaseHead = newPurchase;
    newPurchase = nullptr;

    totalSpent += purchaseHead->item.getPrice() * purchaseHead->quantity;
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

    int i = 0;
    for (purchase* thisPtr = purchaseHead, *otherPtr = otherMember.purchaseHead;
         i < otherMember.transactions; i++, thisPtr = thisPtr->link, otherPtr = otherPtr->link)
    {
        thisPtr = new purchase;
        thisPtr->item = otherPtr->item;
        thisPtr->quantity = otherPtr->quantity;
        for (int i = 0; i < 3; i++)
            thisPtr->date[i] = otherPtr->date[i];

        thisPtr->link = purchaseHead;
        purchaseHead = thisPtr;
        thisPtr = nullptr;
    }

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

    int i = 0;
    for (purchase* thisPtr = purchaseHead, *otherPtr = otherMember.purchaseHead;
         i < otherMember.transactions; i++, thisPtr = thisPtr->link, otherPtr = otherPtr->link)
    {
        thisPtr = new purchase;
        thisPtr->item = otherPtr->item;
        thisPtr->quantity = otherPtr->quantity;
        for (int i = 0; i < 3; i++)
            thisPtr->date[i] = otherPtr->date[i];

        thisPtr->link = purchaseHead;
        purchaseHead = thisPtr;
        thisPtr = nullptr;
    }

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

    int i = 0;
    for (purchase* thisPtr = purchaseHead, *otherPtr = otherMember.purchaseHead;
         i < otherMember.transactions; i++, thisPtr = thisPtr->link, otherPtr = otherPtr->link)
    {
        thisPtr = new purchase;
        thisPtr->item = otherPtr->item;
        thisPtr->quantity = otherPtr->quantity;
        for (int i = 0; i < 3; i++)
            thisPtr->date[i] = otherPtr->date[i];

        thisPtr->link = purchaseHead;
        purchaseHead = thisPtr;
        thisPtr = nullptr;
    }

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

    int i = 0;
    for (purchase* thisPtr = purchaseHead, *otherPtr = otherMember.purchaseHead;
         i < otherMember.transactions; i++, thisPtr = thisPtr->link, otherPtr = otherPtr->link)
    {
        thisPtr = new purchase;
        thisPtr->item = otherPtr->item;
        thisPtr->quantity = otherPtr->quantity;
        for (int i = 0; i < 3; i++)
            thisPtr->date[i] = otherPtr->date[i];

        thisPtr->link = purchaseHead;
        purchaseHead = thisPtr;
        thisPtr = nullptr;
    }

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
