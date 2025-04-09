#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H

#include "node.h"
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

template<typename T>
void set_prev(node<T> *current, node<T> *prevNode = nullptr)
{
    if (current)
        current->_prev = prevNode;
}

template<typename T>
void set_next(node<T> *current, node<T> *nextNode = nullptr)
{
    if (current)
        current->_next = nextNode;
}

//I
template<typename T>
node<T> *insert_head(node<T> *&head_ptr, const T &item)
{
    node<T> *temp = new node<T>(item);
    set_next(temp, head_ptr);
    set_prev(head_ptr, temp);
    head_ptr = temp;
    return head_ptr;
}

//I
template<typename T>
void print_list(node<T> *head_ptr, node<T> *target = nullptr)
{
    node<T> *walker = head_ptr;
    while (walker != nullptr) {
        if (walker != target)
            cout << *walker;
        else
            cout << " {" << walker->_item << "} ->";

        walker = walker->_next;
    }
    cout << "|||" << endl;
}

//I C
//ptr to previous node
template<typename ITEM_TYPE>
node<ITEM_TYPE> *_previous_node(node<ITEM_TYPE> *head, node<ITEM_TYPE> *prev_to_this)
{
    if (prev_to_this) {
        return prev_to_this->_prev;
    } else {
        node<ITEM_TYPE> *walker = head;
        if (prev_to_this == walker)
            return nullptr;

        while (walker != nullptr) {
            if (walker->_next == prev_to_this)
                return walker;
            walker = walker->_next;
        }
        assert(false);
        return nullptr;
    }
}

template<typename ITEM_TYPE>
node<ITEM_TYPE> *_next_node(node<ITEM_TYPE> *head, node<ITEM_TYPE> *next_to_this)
{
    if (next_to_this == nullptr)
        return head;
    return next_to_this->_next;
}

//I C
//Linked List General Functions:
template<typename ITEM_TYPE>
void _print_list(node<ITEM_TYPE> *head)
{
    print_list<ITEM_TYPE>(head);
}

//I C
template<typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_head(node<ITEM_TYPE> *&head, ITEM_TYPE insert_this)
{
    return insert_head<ITEM_TYPE>(head, insert_this);
}

template<typename ITEM_TYPE>
ITEM_TYPE _delete_head(node<ITEM_TYPE> *&head)
{
    assert(head != nullptr);
    ITEM_TYPE save = head->_item;
    node<ITEM_TYPE> *saveNext = head->_next;
    delete head;
    head = saveNext;
    set_prev(head);
    return save;
}

//I C

template<typename ITEM_TYPE>
void _print_list_backwards(node<ITEM_TYPE> *head)
{
    node<ITEM_TYPE> *walker = head;
    node<ITEM_TYPE> *reversed = nullptr;
    while (walker != nullptr) {
        reversed = _insert_head<ITEM_TYPE>(reversed, walker->_item);
        walker = walker->_next;
    }
    _print_list<ITEM_TYPE>(reversed);
}

//DATA_TYPE()
//1 = member
//2 = p_member
//3 = product

//search_type
// name
// membership num
// total spent
// transaction
// rebate
// price
// quantity

// prime and regular membership()
// sorted by id()
// sorted by item name()
// find by expiration date()

template<typename ITEM_TYPE>
node<ITEM_TYPE> *_search_list(node<ITEM_TYPE> *head, ITEM_TYPE key)
{
    node<ITEM_TYPE> *walker = head;
    while (walker != nullptr) {
        if (walker->_item == key)
            return walker;
        walker = walker->_next;
    }
    return nullptr;
}

template<typename ITEM_TYPE>
node<ITEM_TYPE> *_member_search(node<ITEM_TYPE> *head, string name)
{
    node<ITEM_TYPE> *walker = head;
    while (walker != nullptr) {
        if (walker->_item.getName() == name)
            return walker;
        walker = walker->_next;
    }
    return nullptr;
}

template<typename ITEM_TYPE>
node<ITEM_TYPE> *_member_search(node<ITEM_TYPE> *head, int membershipNum)
{
    node<ITEM_TYPE> *walker = head;
    while (walker != nullptr) {
        if (walker->_item.getMembershipNum() == membershipNum)
            return walker;
        walker = walker->_next;
    }
    return nullptr;
}

template<typename ITEM_TYPE>
node<ITEM_TYPE> *_member_search(node<ITEM_TYPE> *head, int expMonth, int expYear)
{
    node<ITEM_TYPE> *walker = head;
    while (walker != nullptr) {
        if (walker->_item.getExpDate()[1] == expMonth && walker->_item.getExpDate()[3] == expYear)
            return walker;
        walker = walker->_next;
    }
    return nullptr;
}

//true if preferred, false if regular
template<typename ITEM_TYPE>
node<ITEM_TYPE> *_member_search(node<ITEM_TYPE> *head, bool isPreferred)
{
    node<ITEM_TYPE> *walker = head;
    while (walker != nullptr) {
        if (walker->_item.getType() == "Preferred" && isPreferred
            || walker->_item.getType() == "Regular" && !isPreferred)
            return walker;
        walker = walker->_next;
    }
    return nullptr;
}

template<typename ITEM_TYPE>
string transformStr(string str) {
    string result;
    copy_if(str.begin(), str.end(), std::back_inserter(result),
                 [](char c){ return !std::isspace(c); });
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}


template<typename ITEM_TYPE>
node<ITEM_TYPE> *_product_search(node<ITEM_TYPE> *head, string name)
{
    node<ITEM_TYPE> *walker = head;
    while (walker != nullptr) {

        if (transformStr<string>(walker->_item.getName()) == transformStr<string>(name))
            return walker;
        walker = walker->_next;
    }
    return nullptr;
}

//I C
//insert after ptr
template<typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_after(node<ITEM_TYPE> *&head,
                               node<ITEM_TYPE> *after_this,
                               ITEM_TYPE insert_this)
{
    if (after_this == nullptr)
        return _insert_head<ITEM_TYPE>(head, insert_this);

    node<ITEM_TYPE> *nextPtr = after_this->_next;
    node<ITEM_TYPE> *insert_ptr = new node<ITEM_TYPE>(insert_this, nextPtr, after_this);
    set_next(after_this, insert_ptr);
    set_prev(nextPtr, insert_ptr);
    cout << endl;
    return insert_ptr;
}

//I C
//insert before ptr
template<typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_before(node<ITEM_TYPE> *&head,
                                node<ITEM_TYPE> *before_this,
                                ITEM_TYPE insert_this)
{
    node<ITEM_TYPE> *prevPtr = _previous_node<ITEM_TYPE>(head, before_this);
    if (prevPtr
        == nullptr) //in case if the iMarker is the first node                              //why dont you use insert head! ): ): ):
        return insert_head<ITEM_TYPE>(head, insert_this);

    node<ITEM_TYPE> *insert_ptr = new node<ITEM_TYPE>(insert_this, before_this, prevPtr);
    set_next(prevPtr, insert_ptr);
    set_prev(before_this, insert_ptr);
    return insert_ptr;
}

//I C Q: delete what if nullptr
//delete, return item
template<typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE> *&head, node<ITEM_TYPE> *delete_this)
{
    if (delete_this == nullptr) {
        cout << "_delete_node() Error: cannot delete nullptr" << endl;
        return ITEM_TYPE();
    }
    node<ITEM_TYPE> *prevPtr = _previous_node<ITEM_TYPE>(head, delete_this);
    //if deleteing the head node

    if (prevPtr == nullptr && delete_this == head)
        return _delete_head(head);
    set_next(prevPtr, delete_this->_next);
    set_prev(delete_this->_next, prevPtr);
    ITEM_TYPE save = delete_this->_item;
    delete delete_this;
    return save;
}

//I C
//duplicate the list...
template<typename ITEM_TYPE>
node<ITEM_TYPE> *_copy_list(node<ITEM_TYPE> *head)
{
    node<ITEM_TYPE> *rethead = nullptr;

    if (head != nullptr) {
        node<ITEM_TYPE> *walker1 = head;
        node<ITEM_TYPE> *walker2 = new node<ITEM_TYPE>(walker1->_item);
        rethead = walker2;

        while (walker1->_next != nullptr) {
            walker2->_next = new node<ITEM_TYPE>(ITEM_TYPE(), nullptr, walker2);
            walker2 = walker2->_next;
            walker1 = walker1->_next;
            walker2->_item = walker1->_item;
        }
    }
    return rethead;
}

//I C
//duplicate list and return the last node of the copy
template<typename ITEM_TYPE>
node<ITEM_TYPE> *_copy_list(node<ITEM_TYPE> *&dest, node<ITEM_TYPE> *src)
{
    node<ITEM_TYPE> *rethead = nullptr;
    node<ITEM_TYPE> *walker2 = nullptr;

    if (src != nullptr) {
        node<ITEM_TYPE> *walker1 = src;
        walker2 = new node<ITEM_TYPE>(walker1->_item);
        rethead = walker2;

        while (walker1->_next != nullptr) {
            walker2->_next = new node<ITEM_TYPE>(ITEM_TYPE(), nullptr, walker2);
            walker2 = walker2->_next;
            walker1 = walker1->_next;
            walker2->_item = walker1->_item;
        }
    }
    dest = rethead;
    return walker2;
}

//I  C
//delete all the nodes
template<typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE> *&head)
{
    while (head != nullptr) {
        node<ITEM_TYPE> *temp = head->_next;
        delete head;
        head = temp;
    }
}

//I C
//_item at this position
template<typename ITEM_TYPE>
ITEM_TYPE &_at(node<ITEM_TYPE> *head, int pos)
{
    node<ITEM_TYPE> *walker = head;
    int current = 0;
    while (walker != nullptr) {
        if (current == pos)
            break;
        walker = walker->_next;
        current++;
    }
    assert(walker != nullptr);
    return walker->_item;
}

template<typename ITEM_TYPE>
node<ITEM_TYPE> *_at_index(node<ITEM_TYPE> *head, int pos)
{
    node<ITEM_TYPE> *walker = head;
    int current = 0;
    while (walker != nullptr) {
        if (current == pos)
            break;
        walker = walker->_next;
        current++;
    }
    if (walker == nullptr)
        cout << "_at_index() Error: index out of bound" << endl;
    return walker;
}

//I  C
//node after which this item goes order: 0 ascending
template<typename ITEM_TYPE>
node<ITEM_TYPE> *_where_this_goes(node<ITEM_TYPE> *head, ITEM_TYPE item, bool ascending = true)
{
    node<ITEM_TYPE> *walker = head;

    if (walker == nullptr)
        return nullptr;

    if (((walker->_item >= item) && (ascending == true)) || //insert head
        ((walker->_item <= item) && (ascending == false)))  //
        return nullptr;

    while (walker->_next != nullptr) {
        if ((((walker->_next)->_item >= item) && (ascending == true))
            || (((walker->_next)->_item <= item) && (ascending == false))) {
            break;
        }
        walker = walker->_next;
    }
    return walker;
}

//I  C
template<typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_sorted(node<ITEM_TYPE> *&head, ITEM_TYPE item, bool ascending = true)
{
    node<ITEM_TYPE> *insertPt = _where_this_goes<ITEM_TYPE>(head, item, ascending);
    return _insert_after<ITEM_TYPE>(head, insertPt, item);
}

//I  C
//insert or add if a dup
template<typename ITEM_TYPE>
node<ITEM_TYPE> *_insert_sorted_and_add(node<ITEM_TYPE> *&head,
                                        ITEM_TYPE item,
                                        bool ascending = true)
{
    node<ITEM_TYPE> *insertPt = _where_this_goes<ITEM_TYPE>(head, item, ascending);
    node<ITEM_TYPE> *walker1 = _next_node<ITEM_TYPE>(head, insertPt);
    ITEM_TYPE total = item;

    while (walker1 && walker1->_item == item) {
        total += item;
        _delete_node<ITEM_TYPE>(head, walker1);
        walker1 = _next_node<ITEM_TYPE>(head, insertPt);
    }

    return _insert_after<ITEM_TYPE>(head, insertPt, total);
}

//Last Node in the list
template<typename ITEM_TYPE>
node<ITEM_TYPE> *_last_node(node<ITEM_TYPE> *head)
{
    node<ITEM_TYPE> *walker = head;

    if (walker == nullptr)
        return nullptr;

    while (walker != nullptr) {
        if (walker->_next == nullptr)
            return walker;
        walker = walker->_next;
    }
    assert(false);
    return walker;
} //never use this function.

#endif
