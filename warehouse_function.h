#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "member.h"
#include "p_member.h"
#include "product.h"
#include <iostream>
#include <fstream>
#include <string>




//filter out all the preferred member in a single list, sorted by membership number
List<p_member> preferredMembers(const List<p_member>& allMembers);

//filter out all the regular member in a single list, sorted by membership number
List<member> regularMembers(const List<p_member>& allMembers);


void inputPurchase(List<p_member>& allMembers, const string& fileName);

void inputShopper(List<p_member>& allMembers, const string& fileName);




#endif