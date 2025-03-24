#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include "product.h"
#include "linked_list_functions.h"
#include "node.h"


double const REBATE = 0.05, BASIC_DUE = 60.00, PREFERRED_DUE = 75.00, SALES_TAX = 0.0875;

//forward declaration needed for constructor that takes child object parameter
class p_member;


//Creates objects that represent purchases by a member.
struct purchase
{
    product item;       //CALC/OUT - The product being bought during this purchase
    int quantity;       //CALC/OUT - The quantity of the product being purchased
    int date[3];        //IN/OUT - The date that the purchase was made on, {month, day, year}

    purchase(){
        //might need implementation
    }

    purchase(const product& prod, int q, int d[]){
        item = prod;
        quantity = q;
        for(int i = 0; i < 3; i++)
            date[i] = d[i];
    }
};

class member
{
public:

    /******************************
    ** CONSTRUCTORS & DESTRUCTOR **
    ******************************/
    member():                                                       //default constructor
        name(""),
        membershipNum(0),
        membershipType(""),
        membershipExpDate({0, 0, 0}),
        totalSpent(0),
        purchaseHead(nullptr),
        transactions(0) {}

    member(string name, int membershipNum,                     //constructor
           string membershipType, int membershipExpDate[]) :
        name(name),
        membershipNum(membershipNum),
        membershipType(membershipType),
        membershipExpDate({membershipExpDate[0], membershipExpDate[1], membershipExpDate[2]}),
        totalSpent(0),
        purchaseHead(nullptr),
        transactions(0) {}

    member(const member& otherMember):                              //copy constructor
        name(otherMember.name),
        membershipNum(otherMember.membershipNum),
        membershipType(otherMember.membershipType),
        totalSpent(otherMember.totalSpent),
        transactions(otherMember.transactions)
    {
        for (int i = 0; i < 3; i++)
            this->membershipExpDate[i] = otherMember.membershipExpDate[i];

        purchaseHead = _copy_list<purchase>(otherMember.purchaseHead);
    }

    member(const p_member& otherMember):                            //copy constructor for p_members for switching memberships
        name(otherMember.name),
        membershipNum(otherMember.membershipNum),
        membershipType(otherMember.membershipType),
        totalSpent(otherMember.totalSpent),
        transactions(otherMember.transactions)
    {
        for (int i = 0; i < 3; i++)
            this->membershipExpDate[i] = otherMember.membershipExpDate[i];

        purchaseHead = _copy_list<purchase>(otherMember.purchaseHead);
    }

    ~member();                                                      //destructor

    /***************
    ** ACCESSORS **
    ***************/
    std::string getName() const {return name;}
    int getMembershipNum() const {return membershipNum;}
    std::string getType() const {return membershipType;}
    const int* getExpDate() const {return membershipExpDate;}       //return need be constant, no modification
    double getSpent() const {return totalSpent;}
    int getTransactions() const {return transactions;}
    const node<purchase>* getHead() const{ return purchaseHead; }

    void reportPurchases();
    bool recommendSwitch();

    bool operator==(const member& otherMember);
    bool operator==(const p_member& otherMember);

    /***************
    /** MUTATORS **
    ***************/
    inline void setName(string n){ name = n; }
    inline void setMembershipNum(int mNum){ membershipNum = mNum; };
    inline void setType(string mType) { membershipType = mType; };
    inline void setSpent(double spent){ totalSpent = spent; }
    inline void setTransactions(int t){ transactions = t; };
    void setExpDate(int membershipExpDate[]);
    void setExpDate(const int membershipExpDate[]);

    void spend(const product& item, int quantity, int date[]);

    member& operator= (const member& otherMember);
    member& operator= (const p_member& otherMember);

private:
    std::string name;               //IN/OUT - Name of the member
    int membershipNum;              //IN/OUT - Number used to identify the member
    std::string membershipType;     //IN/OUT - Membership type; either "basic" or "preferred"
    int membershipExpDate[3];       //IN/OUT - Date of membership expiration stored as an array of [month, day, year]
    double totalSpent;              //CALC/OUT - The total amount of money spent by this member's account in dollars
    node<purchase>* purchaseHead;         //CALC/OUT - Linked List holding the purchases of a member
    int transactions;               //CALC/OUT - Number representing the number of purchases made by the user, and
                                                //the size of the purchases linked list
};




#endif // MEMBER_H


/****************************************************************
* member Class
* This class represents a member object with a basic membership.
* It manages 8 attributes, name, membershipNumber, membershipType,
* membershipExpDate, totalSpent, link, purchaseHead, and transactions
***************************************************************/

/******************************
** CONSTRUCTOR & DESTRUCTOR **
******************************/

/****************************************************************
* member();
* Constructor; default constructor that sets all double and
* integer attributes to 0, all string attributes to an empty
* string, and pointer attributes to nullptr
* Parameters: none
* Return: none
***************************************************************/

/****************************************************************
* member(std::string name, int membershipNumber, std::string
*       membershipType, membershipExpDate);
* Constructor; Initializes the attributes with the corresponding
* names as the attributes, and initializes totalSpent and
* transactions to 0, and link and purchaseHead to nullptr.
* Parameters: name (string) ,membershipNumber(int),
* membershipType (string), membershipExpDate (int[])
* Return: none
***************************************************************/

/****************************************************************
* member(const member& otherMember);
* Constructor; Initializes the attributes with the attributes
* of the other member, and makes a deep copy of the otherMember's
* purchases linked list.
* Parameters: otherMember (const member&)
* Return: none
***************************************************************/

/****************************************************************
* member(const p_member& otherMember);
* Constructor; Initializes the attributes with the attributes
* of the preferred member, and makes a deep copy of the otherMember's
* purchases linked list. Meant for switching a member's membership
* type.
* Parameters: otherMember (const member&)
* Return: none
***************************************************************/

/****************************************************************
* ~member();
* Destructor: Deletes the link attribute and deletes each entry
* in the purchases linked list.
* Parameters: none
* Return: none
***************************************************************/

/***************
** ACCESSORS **
***************/

/*******************************************************************
* std::string getName() const;
*
* Accessor; This method returns the name attribute.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: name attribute
*******************************************************************/

/*******************************************************************
* int getMembershipNum() const;
*
* Accessor; This method returns the membershipNum attribute.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: membershipNum attribute
*******************************************************************/

/*******************************************************************
* std::string getMembershipType() const;
*
* Accessor; This method returns the membershipType attribute.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: membershipType attribute
*******************************************************************/

/*******************************************************************
* int* getMembershipExpDate() const;
*
* Accessor; This method returns a dynamic array containing the
* membershipExpDate attribute.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: array containing membershipExpDate attribute
*******************************************************************/

/*******************************************************************
* double getSpent() const;
*
* Accessor; This method returns the totalSpent attribute.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: totalSpent attribute
*******************************************************************/

/*******************************************************************
* member* getLink() const;
*
* Accessor; This method returns the link attribute.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: link attribute
*******************************************************************/

/*******************************************************************
* int getTransactions() const;
*
* Accessor; This method returns the transactions attribute.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: transactions attribute
*******************************************************************/

/*******************************************************************
* void reportPurchases();
*
* Accessor; This method outputs the purchase objects within its
* purchases linked list in a user-friendly way.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* bool recommendSwitch();
*
* Accessor; This method returns true if it is more cost-efficient
* to switch from a basic to a preferred membership based on the
* purchase data, rebate data, and yearly dues data.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: true if should switch, else false
*******************************************************************/

/*******************************************************************
* bool operator== (const member& otherMember);
*
* Accessor; This method compares the ids of both basic members to
* see if there is a repitition in the member numbers, which isn't
* allowed.
*------------------------------------------------------------------
* Parameter: otherMember (const member&)
*------------------------------------------------------------------
* Return: true if member numbers are equal, else false.
*******************************************************************/

/*******************************************************************
* bool operator== (const p_member& otherMember);
*
* Accessor; This method compares the ids of a basic member (this
* member) and a preferred member (otherMember) to see if there is
* a repitition in the member numbers, which isn't allowed.
*------------------------------------------------------------------
* Parameter: otherMember (const p_member&)
*------------------------------------------------------------------
* Return: true if member numbers are equal, else false.
*******************************************************************/

/***************
**  MUTATORS  **
***************/

/*******************************************************************
* void setName(std::string name);
*
* Mutator; This method sets the name attribute to the given
* parameter.
*------------------------------------------------------------------
* Parameter: name (string)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* void setMembershipNum(int membershipNum);
*
* Mutator; This method sets the membershipNum attribute to the given
* parameter.
*------------------------------------------------------------------
* Parameter: membershipNum (int)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* void setType(std::string membershipType);
*
* Mutator; This method sets the membershipType attribute to the given
* parameter.
*------------------------------------------------------------------
* Parameter: membershipType (string)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* void setMembershipExpDate(int membershipExpDate[]);
*
* Mutator; This method sets the membershipExpDate attribute to the given
* parameter.
*------------------------------------------------------------------
* Parameter: membershipExpDate (int[])
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* void setSpent(double totalSpent);
*
* Mutator; This method sets the totalSpent attribute to the given
* parameter.
*------------------------------------------------------------------
* Parameter: totalSpent (double)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* void setLink(member* link);
*
* Mutator; This method sets the link attribute to the given
* parameter.
*------------------------------------------------------------------
* Parameter: link (member*)
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* void spend(const product& item, int quantity, int date[]);
*
* Mutator; This method increments the transactions attribute,
* adds a purchase with the given product, quantity, and date to the
* front of the purchases linked list, and increases totalSpent by
* the appropriate amount.
*------------------------------------------------------------------
* Parameter: item (const product&), quantity (int), date (int[])
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* member& operator= (const member& otherMember);
*
* Mutator; This method overloads the assignment operator to assign
* the values/attributes of the otherMember to this object
*------------------------------------------------------------------
* Parameter: otherMember (const member&)
*------------------------------------------------------------------
* Return: assigns the values of the otherMember to this member
*******************************************************************/

/*******************************************************************
* member& operator= (const p_member& otherMember);
*
* Mutator; This method overloads the assignment operator to assign
* the values/attributes of the otherMember to this object. Meant
* for use to switch membership type of a member.
*------------------------------------------------------------------
* Parameter: otherMember (const member&)
*------------------------------------------------------------------
* Return: assigns the values of the otherMember to this member
*******************************************************************/


/****************************************************************
* p_member Class
* This class represents a member object with a preferred membership.
* It manages 7 attributes, name, membershipNumber, membershipType,
* membershipExpDate, totalSpent, link, and rebateAmount
***************************************************************/

/******************************
** CONSTRUCTOR & DESTRUCTOR **
******************************/

/****************************************************************
* p_member();
* Constructor; default constructor that sets all double and
* integer attributes to 0, all string attributes to an empty
* string, and pointer attributes to nullptr
* Parameters: none
* Return: none
***************************************************************/

/****************************************************************
* member(std::string name, int membershipNumber, std::string
*       membershipType, membershipExpDate);
* Constructor; Initializes the attributes with the corresponding
* names as the attributes, initializes totalSpent and rebateAmount
* to 0, and link to nullptr.
* Parameters: name (string) ,membershipNumber(int),
* membershipType (string), membershipExpDate (int[])
* Return: none
***************************************************************/

/****************************************************************
* member(std::string name, int membershipNumber, std::string
*       membershipType, membershipExpDate);
* Constructor; Initializes the attributes with the corresponding
* names as the attributes, and initializes totalSpent to 0, and
* link to nullptr
* Parameters: name (string) ,membershipNumber(int),
* membershipType (string), membershipExpDate (int[])
* Return: none
***************************************************************/

/****************************************************************
* p_member(const p_member& otherMember);
* Constructor; Initializes the attributes with the attributes
* of the other member
* Parameters: otherMember (const p_member&)
* Return: none
***************************************************************/

/****************************************************************
* p_member(const member& otherMember);
* Constructor; Initializes the attributes with the attributes
* of the other member, and then calculates rebate. Meant for
* switching the membership type of a member.
* Parameters: otherMember (const member&)
* Return: none
***************************************************************/

/****************************************************************
* ~p_member();
* Destructor: Deletes the link attribute and deletes each entry
* in the purchases linked list.
* Parameters: none
* Return: none
***************************************************************/

/***************
** ACCESSORS **
***************/

/*******************************************************************
* double getRebate() const;
*
* Accessor; This method returns the rebateAmount attribute.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: rebateAmount attribute
*******************************************************************/

/*******************************************************************
* bool recommendSwitch();
*
* Accessor; This method returns true if it is more cost-efficient
* to switch from a preferred to a basic membership based on the
* purchase data, rebate data, and yearly dues data.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: true if should switch, else false
*******************************************************************/

/***************
**  MUTATORS  **
***************/

/*******************************************************************
* p_member& operator= (const p_member& otherMember);
*
* Mutator; This method overloads the assignment operator to assign
* the values/attributes of the otherMember to this object
*------------------------------------------------------------------
* Parameter: otherMember (const p_member&)
*------------------------------------------------------------------
* Return: assigns the values of the otherMember to this member
*******************************************************************/

/*******************************************************************
* p_member& operator= (const member& otherMember);
*
* Mutator; This method overloads the assignment operator to assign
* the values/attributes of the otherMember to this object, and then
* calculates the rebate amount. Meant for sake of switching
* membership type of the member.
*------------------------------------------------------------------
* Parameter: otherMember (const member&)
*------------------------------------------------------------------
* Return: assigns the values of the otherMember to this member
*******************************************************************/

/*******************************************************************
* void spend(const product& item, int quantity, int date[]);
*
* Mutator; This method increments the transactions attribute,
* adds a purchase with the given product, quantity, and date to the
* front of the purchases linked list, increases totalSpent by the
* appropriate amount, and then recalculates the rebate ammount.
*------------------------------------------------------------------
* Parameter: item (const product&), quantity (int), date (int[])
*------------------------------------------------------------------
* Return: none
*******************************************************************/

/*******************************************************************
* void calcRebate();
*
* Mutator; This method calculates and reassigns the rebate amount
* based on the totalSpent attribute.
*------------------------------------------------------------------
* Parameter: none
*------------------------------------------------------------------
* Return: none
*******************************************************************/
