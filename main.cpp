#include <iostream>
#include <iomanip>
#include <vector>

#include "C:\Users\agu4\Documents\CS8Projects\Test_Ground_full\includes\member.h"
#include "C:\Users\agu4\Documents\CS8Projects\Test_Ground_full\includes\p_member.h"
#include "C:\Users\agu4\Documents\CS8Projects\Test_Ground_full\includes\product_list.h"
#include "C:\Users\agu4\Documents\CS8Projects\Test_Ground_full\includes\product.h"
using namespace std;










int main(int argv, char** argc) {
    typedef purchase type;
    List<type> Lst(true, true);
    List<type> c1;
    List<type>::Iterator currentIt = Lst.begin();
    bool getKey = true;
    char key;
    int num;
    string name, memberType;
    int membershipNum, totalSpent, transaction;
    int price, quantity;
    int date[3];

    //search
    //insert after
    //insert before
    //delete
    //copy
    //clear
    //at
    //insert sorted(a/d)
    //insert sorted and add(a/d)
    //last node

    while(getKey){
        cout << "[f] find, [a] insert after, [b] insert before, [d] delete, [c] copy, [~] clear" << endl;
        cout << "[@] at, [s] insert sorted, [+] insert sorted and add, [l] last node, [q] quit" << endl;
        Lst._print_sorted_list(currentIt);
        cin >> key;
        key = tolower(key);
        type ins;

        switch(key){
            //move right
            case '.':
            currentIt++;
            break;
            //move left
            case ',':
            currentIt--;
            break;
            //find
            case 'f':
                // cout << "Enter what you want find: 1 = name, 2 = membershipNum";
                // cin >> num;
                // switch(num){
                //     case 1:
                //         cout << "Enter name you want find: ";
                //         cin >> name;
                //         currentIt = Lst.member_search(name);
                //         cout << ((!currentIt.is_null()) ?  "Result: Found" : "Result: Not found") << endl;
                //     break;
                //     case 2:
                //         cout << "Enter num you want find: ";
                //         cin >> num;
                //         currentIt = Lst.member_search(num);
                //         cout << ((!currentIt.is_null()) ?  "Result: Found" : "Result: Not found") << endl;
                //     break;
                //     default:
                //     break;
                // }
                //**************************************************************************************************** */
                // cout << "Enter name you want find: ";
                // cin >> name;
                // currentIt = Lst.product_search(name);
                // cout << ((!currentIt.is_null()) ?  "Result: Found" : "Result: Not found") << endl;
            break;
            //insert after
            case 'a':
                // cout << "Enter value you want insert after: \n";
                // cout << "name membershipType membershipNum totalSpent transaction: \n";
                // cin >> name >> memberType >> membershipNum >> totalSpent >> transaction;
                // ins.setName(name);
                // ins.setType(memberType);
                // ins.setMembershipNum(membershipNum);
                // ins.setSpent(totalSpent);
                // ins.setTransactions(transaction);
                // Lst.insert(ins);
                //**************************************************************************************************** */
                // cout << "Enter value you want insert after: \n";
                // cout << "name price quantity: \n";
                // cin >> name >> price >> quantity;
                // ins.setName(name);
                // ins.setPrice(price);
                // ins.setQuantity(quantity);
                // Lst.insert(ins);
                //**************************************************************************************************** */
                cout << "Enter value you want insert after: \n";
                cout << "name price quantity: \n";
                cin >> name >> price >> quantity;
                cout << "quantity month day year: \n";
                cin >> quantity >> date[0] >> date[1] >> date[2];
                ins.item = product(name, price, quantity);
                ins.quantity = quantity;
                ins.date[0] = date[0];
                ins.date[1] = date[1];
                ins.date[2] = date[2];
                Lst.insert(ins);
            break;
            //insert before
            case 'b':
                // cout << "Enter value you want insert after: \n";
                // cout << "name membershipType membershipNum totalSpent transaction: \n";
                // cin >> name >> memberType >> membershipNum >> totalSpent >> transaction;
                // ins.setName(name);
                // ins.setType(memberType);
                // ins.setMembershipNum(membershipNum);
                // ins.setSpent(totalSpent);
                // ins.setTransactions(transaction);
                // Lst.insert_and_add(ins);
                //**************************************************************************************************** */
                // cout << "Enter value you want insert after: \n";
                // cout << "name price quantity: \n";
                // cin >> name >> price >> quantity;
                // ins.setName(name);
                // ins.setPrice(price);
                // ins.setQuantity(quantity);
                // Lst.insert_and_add(ins);
            break;
            //delete
            case 'd':
                Lst.Delete(currentIt);
                currentIt = Lst.begin();
            break;
            //copy
            case 'c':
                c1 = Lst;
                cout << "assignmnet operator: " << c1;
                c1 = List<type>(Lst);
                cout << "constructor: "<< c1;
            break;
            //clear
            case '~':
                Lst.~List();
                Lst = List<type>();
                currentIt = Lst.begin();
            break;
            //at
            case '@':
                cout << "Enter the index you want find: ";
                cin >> num;
                currentIt = Lst(num);
                cout << ((!currentIt.is_null()) ?  "Result: Found" : "Result: Not found") << endl;
            break;
            //insert sorted(a/d)
            case 's':
                
            break;
            //insert sorted and add(a/d)
            case '+':
            
            break;
            //last node
            case 'l':
                // currentNode = _last_node<type>(head);
            break;
            //Quit
            case 'q':
                getKey = false;
            break;

            default:
                cout << "Invalid Command, Try Again" << endl;
            break;
        }
    }
    
    return 0;
}



