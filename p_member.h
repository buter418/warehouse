#ifndef P_MEMBER_H
#define P_MEMBER_H



#include "member.h"






class p_member: public member
{
public:

    /******************************
    ** CONSTRUCTORS & DESTRUCTOR **
    ******************************/
    p_member(): member(), rebateAmount(0) {}                                            //default constructor

    p_member(std::string name, int membershipNum,                                       //constructor
             std::string membershipType, int membershipExpDate[]):
        member(name, membershipNum, membershipType, membershipExpDate),
        rebateAmount(0) {}

    p_member(const p_member& otherP):                                                   //copy constructor
        member(otherP),
        rebateAmount(otherP.rebateAmount) {}

    p_member(const member& otherP):                                                   //copy constructor
        member(otherP) {calcRebate();}

    ~p_member() : ~member() {}                                                           //destructor

    /***************
    ** ACCESSORS **
    ***************/
    double getRebate() {return rebateAmount;}
    bool recommendSwitch();

    /***************
    /** MUTATORS **
    ***************/
    p_member& operator= (const p_member& otherMember);
    p_member& operator= (const member& otherMember);

    void spend(const product &item, int quantity, int date[]);
    void calcRebate();

private:
    double rebateAmount;            //CALC/OUT - Amount to be rebated at end of year, for preferred members only
};


#endif