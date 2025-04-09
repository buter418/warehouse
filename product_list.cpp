#include "mainwindow.h"

//To do: Implement member container class so that can use the names collected in this method
product_list::product_list(const QString filename,
                           List<p_member> allMembers,
                           List<product> &allProduct,
                           node<p_member> *&todayMembers)
{
    head = nullptr;
    size = 0;

    //Open file through qrc file
    QFile infile(filename);
    infile.open(QIODevice::ReadOnly | QIODevice::Text);

    //Loop til eof
    while (true) {
        int month, day, year, id, quantity;
        double price;
        std::string name;
        QString Qname, dateStr, priceAndQuantity;

        //Get date
        dateStr = infile.readLine();
        QStringList date = dateStr.split('/');

        month = date[0].trimmed().toInt();
        day = date[1].trimmed().toInt();
        year = date[2].trimmed().toInt();

        //Get member id (implement to use this eventually
        id = infile.readLine().toInt();

        p_member newMember = *(allMembers.member_search(id));

        if (size == 0) {
            delete todayMembers;
            todayMembers = new node<p_member>(newMember);
        } else
            _insert_head(todayMembers, newMember);

        //Get product name
        Qname = infile.readLine();
        name = Qname.toStdString();

        //Get price
        priceAndQuantity = infile.readLine();
        QStringList priceAndQuantityList = priceAndQuantity.split('\t');
        price = priceAndQuantityList[0].trimmed().toDouble();

        //Get quantity
        quantity = priceAndQuantityList[1].trimmed().toInt();

        //Create and add the new product
        setDate(month, day, year);
        product newProd = product(name, price, quantity);

        addProduct(newProd, true);
        allProduct.insert_and_add(newProd);

        if (infile.atEnd())
            break;
    }

    //Reverse order to match dailyMembers
    node<product> *walker = head;
    node<product> *reversed = nullptr;
    while (walker != nullptr) {
        reversed = _insert_head<product>(reversed, walker->_item);
        walker = walker->_next;
    }

    for (node<product> *current = head; current != nullptr;) {
        node<product> *placehold = current->_next;
        delete current;
        current = placehold;
    }
    head = reversed;
    walker = reversed = nullptr;

    infile.close();
}

product_list::product_list(const product_list &otherList)
{
    //Initialize static attribute
    head = nullptr;
    size = 0;
    setDate(otherList.getMonth(), otherList.getDay(), otherList.getYear());

    //Add copy of each product entry to this list
    for (node<product> *current = otherList.head; current != nullptr; current = current->_next) {
        //-------------------------------------------------------
        //make sure no ptr in product, or it will be shallow copy
        product newProd = current->_item;
        //-------------------------------------------------------

        addProduct(newProd, true);
    }
}

product_list::~product_list()
{
    _clear_list<product>(head);
}

std::string product_list::getDate() const
{
    std::string dateStr = std::to_string(date[0]) + "/" + std::to_string(date[1]) + "/"
                          + std::to_string(date[2]);
    return dateStr;
}

bool product_list::isEmpty()
{
    if (size == 0 || head == nullptr)
        return true;
    else
        return false;
}

void product_list::setHead(node<product> *head)
{
    this->head = head;
}

void product_list::setSize(int size)
{
    this->size = size;
}

void product_list::incSize(int amount)
{
    size += amount;
}

void product_list::setDate(int month, int day, int year)
{
    date[0] = month;
    date[1] = day;
    date[2] = year;
}

//check if repeated product exist if so return ptr to that repeated product
node<product> *product_list::checkProducts(product prod)
{
    return _search_list<product>(head, prod);
}

//If product exists, add to its quantity, else add new product node to head
void product_list::addProduct(product prod, bool unique)
{
    node<product> *addSpot = checkProducts(prod);

    if (addSpot && !unique) {
        addSpot->_item.increaseQuantity(prod.getQuantity());
    } else {
        _insert_head<product>(head, prod);
        incSize();
    }
}

//Calc revenue of all products in list
double product_list::calcTotal()
{
    double result = 0;
    for (node<product> *current = head; current != nullptr; current = current->_next)
        result += current->_item.getRevenue();

    return result;
}

//Sets values of cells for a given day report
void product_list::setSalesTable(QTableWidget *tableWidget,
                                 List<p_member> allMembers,
                                 node<p_member> *todayMembers)
{
    QStringList nameList;

    int basic = 0, preferred = 0, i = 0;
    node<p_member> *currentMember = todayMembers;
    for (node<product> *current = head; current != nullptr;
         i++, currentMember = currentMember->_next) {
        //Add vertival head labels per row
        nameList.append(QString::number(i + 1));

        //Steps to create items that can be used to set values in given table widget
        std::string price;
        QString qname, qdate, qmember;
        qname = QString::fromStdString(current->_item.getName());
        qdate = QString::number(getMonth()) + "/" + QString::number(getDay()) + "/"
                + QString::number(getYear());
        qmember = QString::fromStdString(currentMember->_item.getName());

        double p = current->_item.getPrice();
        int n = std::round(p * 100);
        price = "$" + to_string(n / 100) + ".";
        if (n % 100 > 0 && n % 100 < 10)
            price += "0" + to_string(n % 100);
        else if (n % 100 == 0)
            price += "00";
        else
            price += to_string(n % 100);

        QVariant nameValue(qname);
        QVariant memberValue(qmember);
        QVariant priceValue(QString::fromStdString(price));
        QVariant quantityValue(current->_item.getQuantity());

        QTableWidgetItem *nameItem = new QTableWidgetItem;
        QTableWidgetItem *memberItem = new QTableWidgetItem;
        QTableWidgetItem *priceItem = new QTableWidgetItem;
        QTableWidgetItem *quantityItem = new QTableWidgetItem;

        nameItem->setData(Qt::DisplayRole, nameValue);
        memberItem->setData(Qt::DisplayRole, memberValue);
        priceItem->setData(Qt::DisplayRole, priceValue);
        quantityItem->setData(Qt::DisplayRole, quantityValue);

        //Set cells of widget (missing one for the member right now
        tableWidget->setItem(i, 0, nameItem);
        tableWidget->setItem(i, 1, memberItem);
        tableWidget->setItem(i, 2, priceItem);
        tableWidget->setItem(i, 3, quantityItem);

        if (currentMember->_item.getType() == "Preferred")
            preferred++;
        else
            basic++;

        if (current->_next)
            current = current->_next;
        else {
            i++;
            break;
        }
    }

    //Separate place to show count of each member type
    nameList.append("");
    nameList.append("Basic Members");
    nameList.append("Preferred Members");
    tableWidget->setVerticalHeaderLabels(nameList);

    QTableWidgetItem *basicItem = new QTableWidgetItem;
    basicItem->setData(Qt::DisplayRole, basic);
    QTableWidgetItem *preferredItem = new QTableWidgetItem;
    preferredItem->setData(Qt::DisplayRole, preferred);

    tableWidget->setItem(i + 1, 0, basicItem);
    tableWidget->setItem(i + 2, 0, preferredItem);
}

//Sets table for yearly report
void product_list::setYearTable(QTableWidget *tableWidget)
{
    QStringList nameList;
    node<product> *best, *worst; //points to best and worst performing products
    best = worst = nullptr;

    int i = 0;
    double totalRevenue = 0;
    for (node<product> *current = head; current != nullptr; i++) {
        //If first cycle, set both to first value.
        if (best == nullptr) {
            best = current;
            worst = current;
        } else {
            //If not first, switch the best and worst pointers if the given value is greater than best or less than worst
            if (best->_item.getRevenue() < current->_item.getRevenue())
                best = current;

            if (worst->_item.getRevenue() > current->_item.getRevenue())
                worst = current;
        }

        nameList.append(QString::number(i + 1));

        //Steps for creating items to fill table with
        std::string revenue;
        double p = current->_item.getRevenue();
        totalRevenue += p;

        int n = std::round(p * 100);
        revenue = "$" + to_string(n / 100) + ".";
        if (n % 100 > 0 && n % 100 < 10)
            revenue += "0" + to_string(n % 100);
        else if (n % 100 == 0)
            revenue += "00";
        else
            revenue += to_string(n % 100);

        QString qname;
        qname = QString::fromStdString(current->_item.getName());

        QVariant nameValue(qname);
        QVariant quantityValue(current->_item.getQuantity());
        QVariant revenueValue(QString::fromStdString(revenue));

        QTableWidgetItem *nameItem = new QTableWidgetItem;
        QTableWidgetItem *quantityItem = new QTableWidgetItem;
        QTableWidgetItem *revenueItem = new QTableWidgetItem;

        nameItem->setData(Qt::DisplayRole, nameValue);
        quantityItem->setData(Qt::DisplayRole, quantityValue);
        revenueItem->setData(Qt::DisplayRole, revenueValue);

        //Add items to the table
        tableWidget->setItem(i, 0, nameItem);
        tableWidget->setItem(i, 1, quantityItem);
        tableWidget->setItem(i, 2, revenueItem);

        //If next exists, continue, else break
        if (current->_next)
            current = current->_next;
        else {
            i++;
            break;
        }
    }

    //Create separate area to show best and worst products
    nameList.append("");
    nameList.append("Total Revenue");
    nameList.append("Best");
    nameList.append("Worst");
    tableWidget->setVerticalHeaderLabels(nameList);

    std::string totalRevenueStr;
    int n = std::round(totalRevenue * 100);
    totalRevenueStr = "$" + to_string(n / 100) + ".";
    if (n % 100 > 0 && n % 100 < 10)
        totalRevenueStr += "0" + to_string(n % 100);
    else if (n % 100 == 0)
        totalRevenueStr += "00";
    else
        totalRevenueStr += to_string(n % 100);

    QString qbest, qworst;

    qbest = QString::fromStdString(best->_item.getName());
    qworst = QString::fromStdString(worst->_item.getName());

    QVariant bestValue(qbest);
    QVariant worstValue(qworst);

    QTableWidgetItem *totalRevenueItem = new QTableWidgetItem;
    QTableWidgetItem *bestItem = new QTableWidgetItem;
    QTableWidgetItem *worstItem = new QTableWidgetItem;

    totalRevenueItem->setData(Qt::DisplayRole, QString::fromStdString(totalRevenueStr));
    bestItem->setData(Qt::DisplayRole, bestValue);
    worstItem->setData(Qt::DisplayRole, worstValue);

    tableWidget->setItem(i + 1, 0, totalRevenueItem);
    tableWidget->setItem(i + 2, 0, bestItem);
    tableWidget->setItem(i + 3, 0, worstItem);
}

//Assignment operator
product_list &product_list::operator=(const product_list &otherList)
{
    //Self assignment case
    if (this == &otherList)
        return *this;

    _clear_list(head);
    size = 0;

    setDate(otherList.getMonth(), otherList.getDay(), otherList.getYear());

    for (node<product> *current = otherList.head; current != nullptr; current = current->_next) {
        product newProd = current->_item;
        addProduct(newProd);
    }

    return *this;
}

product_list operator+(const product_list &list1, const product_list &list2)
{
    product_list newList = list1;

    for (node<product> *current = list2.head; current != nullptr; current = current->_next) {
        newList.addProduct(current->_item);
    }
    return newList;
}
