
#include "warehouse_function.h"


List<p_member> preferredMembers(const List<p_member>& allMembers){
    List<p_member> result(true, true);
    for(List<p_member>::Iterator i = allMembers.begin(); i != allMembers.end(); i++){
        if(i->getType() == "Preferred")
            result.insert_and_add(*i);
    }
    return result;
}



List<member> regularMembers(const List<p_member>& allMembers){
    List<member> result(true, true);
    for(List<p_member>::Iterator i = allMembers.begin(); i != allMembers.end(); i++){
        if(i->getType() == "Regular")
            result.insert_and_add(*i);
    }
    return result;
}




// 03/06/2013
// 61616
// 1 gallon milk
// 2.49	5
void inputPurchase(List<p_member>& allMembers, const string& fileName){
    ifstream file(fileName);            // Open the file for reading

    if (!file) { // Check if file opened successfully
        std::cerr << "Error: Could not open the file " << fileName << endl;
        return;
    }

    string line, name;
    int lineCtr = 1;
    int membershipNum, price, quantity, size;
    int Date[3];
    while (getline(file, line)) { // Read file line by line
        if(lineCtr == 5){
            List<p_member>::Iterator current = allMembers.member_search(membershipNum);
            if(!current.is_null())
                current->spend(product(name, price, quantity), quantity, Date);
            lineCtr = 1;
        }

        switch(lineCtr){
            case 1:
            Date[0] = stoi(line.substr(0, 2));
            Date[1] = stoi(line.substr(3, 2));
            Date[2] = stoi(line.substr(6, 4));
            break;
            case 2:
            membershipNum = stoi(line);
            break;
            case 3:
            name = line;
            break;
            case 4:
            size = line.find(' ');
            price = stoi(line.substr(0, size));
            quantity = stoi(line.substr(size + 1));
            break;
            default:

            break;
        }
        lineCtr++;
    }
    file.close(); // Close the file
}



// Sally Shopper
// 12345
// Basic
// 11/01/2013
void inputShopper(List<p_member>& allMembers, const string& fileName){
    ifstream file(fileName);            // Open the file for reading

    if (!file) { // Check if file opened successfully
        std::cerr << "Error: Could not open the file " << fileName << endl;
        return;
    }

    string line, name, type;
    int lineCtr = 1;
    int membershipNum;
    int ExpDate[3];
    while (getline(file, line)) { // Read file line by line
        if(lineCtr == 5){
            allMembers.insert_and_add(p_member(name, membershipNum, type, ExpDate));
            lineCtr = 1;
        }

        switch(lineCtr){
            case 1:
            name = line;
            break;
            case 2:
            membershipNum = stoi(line);
            break;
            case 3:
            type = line;
            break;
            case 4:
            ExpDate[0] = stoi(line.substr(0, 2));
            ExpDate[1] = stoi(line.substr(3, 2));
            ExpDate[2] = stoi(line.substr(6, 4));
            break;
            default:

            break;
        }
        lineCtr++;
    }
    file.close(); // Close the file
}