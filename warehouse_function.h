#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "member.h"
#include "p_member.h"
#include "product.h"





List<p_member> preferredMembers(const List<p_member>& allMembers);
List<member> regularMembers(const List<p_member>& allMembers);












#endif