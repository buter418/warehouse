#include "p_member.h"





//*********************************
//* 2 assignment operator
//*********************************
p_member& p_member::operator =(const p_member& otherMember) {
    setName(otherMember.getName());
    setMembershipNum(otherMember.getMembershipNum());
    setType(otherMember.getType());
    setSpent(otherMember.getSpent());
    setTransactions(otherMember.getTransactions());
    setExpDate(otherMember.getExpDate());
    setHead(_copy_list<purchase>(otherMember.getHead()));
    rebateAmount = otherMember.rebateAmount;

    return *this;
}
p_member& p_member::operator =(const member& otherMember) {
    setName(otherMember.getName());
    setMembershipNum(otherMember.getMembershipNum());
    setType(otherMember.getType());
    setSpent(otherMember.getSpent());
    setTransactions(otherMember.getTransactions());
    setExpDate(otherMember.getExpDate());
    setHead(_copy_list<purchase>(otherMember.getHead()));
    calcRebate();

    return *this;
}



//*********************************
//* other member functions
//*********************************
bool p_member::recommendSwitch(){
    return !member::recommendSwitch();
}



void p_member::spend(const product& item, int quantity, int date[]) {
    member::spend(item, quantity, date);
    calcRebate();
}


void p_member::calcRebate() {
    rebateAmount = getSpent() * REBATE;
}