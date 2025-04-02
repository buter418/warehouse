#ifndef LIST_SORTED_H
#define LIST_SORTED_H
#include "linked_list_functions.h"

#include <iostream>
using namespace std;

template <class T>
class List {
public:

    class Iterator {
    public:
        friend class List; // give access to List to access _ptr

        Iterator() : _ptr(nullptr) , _save(nullptr), end(2){} // default ctor

        Iterator(node<T>* p) : _ptr(p), _save(p), end(2) {} // Point Iterator to where p is pointing to

        T& operator*() { return _ptr->_item; } // dereference operator

        T* operator->() { return &_ptr->_item; } // member access operator

        bool is_null() { return _ptr == nullptr; } // true if _ptr is NULL

        node<T>* get_ptr() { return _ptr; }

        friend bool operator!=(const Iterator& left, const Iterator& right) { return left._ptr != right._ptr; } // true if left != right
        friend bool operator==(const Iterator& left, const Iterator& right) { return left._ptr == right._ptr; } // true if left == right

        Iterator& operator++() { // member operator:  ++it; or  ++it = new_value
            if(_ptr){
                if(_ptr->_next == nullptr){
                    _save = _ptr;
                    _ptr = _ptr->_next;
                    end = 0;
                }
                else{
                    _ptr = _ptr->_next;
                    end = 2;
                }
            }
            else{
                if(end == 0){
                    cout << "++ reached end of list" << endl;
                    end = 0;
                }
                else if(end == 1){
                    _ptr = _save;
                    end = 2;
                }
            }
            return *this;
        }

        friend Iterator operator++(Iterator& it, int unused) { // friend operator: it++
            Iterator temp = it;
            ++it;
            return temp;
        }

        Iterator& operator--() { // member operator:  ++it; or  ++it = new_value
            if(_ptr){
                if(_ptr->_prev == nullptr){
                    _save = _ptr;
                    _ptr = _ptr->_prev;
                    end = 1;
                }
                else{
                    _ptr = _ptr->_prev;
                    end = 2;
                }
            }
            else{
                if(end == 1){
                    cout << "-- reached head of list" << endl;
                    end = 1;
                }
                else if(end == 0){
                    _ptr = _save;
                    end = 2;
                }
            }
            return *this;
        }

        friend Iterator operator--(Iterator& it, int unused) { // friend operator: it++
            Iterator temp = it;
            --it;
            return temp;
        }

    private:
        node<T>* _ptr; // pointer being encapsulated
        node<T>* _save; // save _ptr at end and head
        int end;         //which side is the iterator on, 0 = end or 1 = head, 2 = null
    };

    List(bool order = true, bool unique = false) // CTOR: default args
    {
        _head_ptr = nullptr;
        _order = order;
        _unique = unique;
        _size = 0;
    }

    // BIG 3:
    ~List() {
        _clear_list(_head_ptr);
        _size = 0;
        _order = false;
        _unique = true;
    }

    List(const List<T>& copyThis) {
        _head_ptr = nullptr;
        _copy_list(_head_ptr, copyThis._head_ptr);
        _size = copyThis._size;
        _order = copyThis._order;
        _unique = copyThis._unique;
    }

    List& operator=(const List& RHS) {
        if (this != &RHS) { // Self-assignment check
            _clear_list(_head_ptr);
            _head_ptr = _copy_list(RHS._head_ptr);
            _order = RHS._order;
            _unique = RHS._unique;
            _size = RHS._size;
        }
        return *this;
    }

    Iterator insert(const T& i) { // Insert i
        _size++;
        return _insert_sorted(_head_ptr, i, _order);
    }

    Iterator insert_and_add(const T& i) { // Insert i
        node<T>* found = _search_list(_head_ptr, i);
        if (!_unique && found) { // Unique mode and item already exists
            found->_item += i;
            return found;
        }
        else {
            _size++;
            return _insert_sorted(_head_ptr, i, _order);
        }
    }

    T Delete(List<T>::Iterator iMarker) { // delete node at marker
        T deleted_value = _delete_node(_head_ptr, iMarker._ptr);
        _size--;
        return deleted_value;
    }

    void Print() const {
        _print_list(_head_ptr);
    }

    Iterator search(const T& key) const { // return Iterator to node [key]
        return _search_list(_head_ptr, key);
    }

    Iterator member_search(const string& name) const { // return Iterator to node [key]
        return _member_search(_head_ptr, name);
    }

    Iterator member_search(const int& membershipNum) const { // return Iterator to node [key]
        return _member_search(_head_ptr, membershipNum);
    }

    Iterator member_search(const int& Month, const int& Year) const { // return Iterator to node [key]
        return _member_search(_head_ptr, Month, Year);
    }

    Iterator member_search(const bool& Preferred) const { // return Iterator to node [key]
        return _member_search(_head_ptr, Preferred);
    }

    Iterator product_search(const string& name) const { // return Iterator to node [key]
        return _product_search(_head_ptr, name);
    }

    Iterator prev(Iterator iMarker) { // previous node: marker
        return _previous_node(_head_ptr, iMarker._ptr);
    }

    const T& operator[](int index) const { // const version of the operator [ ]
        return _at(_head_ptr, index);
    }

    T& operator[](int index) {
        return _at(_head_ptr, index);
    }

    const Iterator operator()(int index) const { // const version of the operator ()
        return _at_index(_head_ptr, index);
    }

    Iterator operator()(int index) {
        return _at_index(_head_ptr, index);
    }

    Iterator begin() const {
        return _head_ptr;
    }

    Iterator end() const {
        return nullptr;
    }

    Iterator last_node() const {
        return _last_node(_head_ptr);
    }

    bool empty() const { return _head_ptr == nullptr; }

    template <class U>
    friend ostream& operator<<(ostream& outs, const List<U>& l);

    void _print_sorted_list(Iterator& current = Iterator()){
        print_list(_head_ptr, current.get_ptr());
    }

    int size() const { return _size; }

private:
    node<T>* _head_ptr;
    bool _order;                //ascending == true, descending == false
    bool _unique;
    int _size;
};

template <class U>
ostream& operator<<(ostream& outs, const List<U>& l) {
    _print_list(l._head_ptr);
    return outs;
}

#endif
