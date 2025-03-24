#include "p_member.h"






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


