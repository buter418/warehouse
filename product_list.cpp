#include "mainwindow.h"

//To do: Implement member container class so that can use the names collected in this method
product_list::product_list(const QString filename/*, member** todayMembers*/) {
    head = nullptr;
    size = 0;

    QFile infile(filename);
    infile.open(QIODevice::ReadOnly | QIODevice::Text);

    while (true)
    {
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

        //Get member id
        id = infile.readLine().toInt();

        //Get product name
        Qname = infile.readLine();
        name = Qname.toStdString();

        //Get price
        priceAndQuantity = infile.readLine();
        QStringList priceAndQuantityList = priceAndQuantity.split('\t');
        price = priceAndQuantityList[0].trimmed().toDouble();

        //Get quantity
        quantity = priceAndQuantityList[1].trimmed().toInt();

        setDate(month, day, year);
        product* newProd = new product(name, price, quantity);

        addProduct(newProd);

        if (infile.atEnd())
            break;
    }

    infile.close();
}

product_list::product_list(const product_list& otherList) {
    head = nullptr;
    size = 0;
    setDate(otherList.getMonth(), otherList.getDay(), otherList.getYear());

    for (product* current = otherList.head; current != nullptr; current = current->getLink())
    {
        product* newProd = new product(current->getName(), current->getPrice(), current->getQuantity());

        addProduct(newProd);
    }
}

product_list::~product_list() {
    int i = 0;
    for (product* current = head; current != nullptr ; i++)
    {
        if (current->getLink() != nullptr)
        {
            product* placehold = current->getLink();
            delete current;
            current = placehold;
            placehold = nullptr;
        }
        else
        {
            delete current;
            break;
        }
    }
}

bool product_list::isEmpty() {
    if (size == 0 || head == nullptr)
        return true;
    else
        return false;
}

void product_list::setHead(product* head) {
    this->head = head;
}

void product_list::setSize(int size) {
    this->size = size;
}

void product_list::incSize(int amount) {
    size += amount;
}

void product_list::setDate(int month, int day, int year) {
    date[0] = month;
    date[1] = day;
    date[2] = year;
}

product* product_list::checkProducts(product *prod) {
    if (isEmpty())
        return nullptr;

    for (product* current = head; current != nullptr;)
    {
        if (current->getName() == prod->getName())
            return current;

        if (current->getLink())
            current = current->getLink();
        else
            break;
    }

    return nullptr;
}

void product_list::addProduct(product *prod) {
    product* addSpot = checkProducts(prod);


    if (isEmpty())
    {
        addSpot = new product(*prod);
        addSpot->setLink(nullptr);
        head = addSpot;
        incSize();
    }
    else if (!addSpot)
    {
        addSpot = new product(*prod);
        addSpot->setLink(head);
        head = addSpot;
        incSize();
    }
    else
    {
        addSpot->increaseQuantity(prod->getQuantity());
    }
}

double product_list::calcTotal() {
    double result = 0;

    for (product* current = head; current != nullptr;)
    {
        result += current->getPrice() * current->getQuantity();

        if (current->getLink())
            current = current->getLink();
        else
            break;
    }

    return result;
}

void product_list::setSalesTable(QTableWidget *tableWidget) {
    QStringList nameList;

    int basic, preferred, i = 0;
    for (product* current = head; current != nullptr; i++)
    {
        nameList.append(QString::number(i + 1));

        QString qname, qdate, qmember;
        qname = QString::fromStdString(current->getName());
        qdate = QString::number(getMonth()) + "/" + QString::number(getDay()) + "/" + QString::number(getYear());
        //qmember = day1Members[i]->getName();

        QVariant nameValue(qname);
        QVariant dateValue(qdate);
        //QVariant memberValue(qmember);
        QVariant priceValue(current->getPrice());
        QVariant quantityValue(current->getQuantity());

        QTableWidgetItem* nameItem = new QTableWidgetItem;
        QTableWidgetItem* dateItem = new QTableWidgetItem;
        //QTableWidgetItem* memberItem = new QTableWidgetItem;
        QTableWidgetItem* priceItem = new QTableWidgetItem;
        QTableWidgetItem* quantityItem = new QTableWidgetItem;

        nameItem->setData(Qt::DisplayRole, nameValue);
        dateItem->setData(Qt::DisplayRole, dateValue);
        //memberItem->setData(Qt::DisplayRole, memberValue);
        priceItem->setData(Qt::DisplayRole, priceValue);
        quantityItem->setData(Qt::DisplayRole, quantityValue);

        tableWidget->setItem(i, 0, nameItem);
        tableWidget->setItem(i, 1, dateItem);
        tableWidget->setItem(i, 3, priceItem);
        tableWidget->setItem(i, 4, quantityItem);

        /*
        if (members[i]->getType() == "preferred")
            preferred++;
        else
            basic++;
        */

        if (current->getLink())
            current = current->getLink();
        else
        {
            i++;
            break;
        }
    }

    nameList.append("");
    nameList.append("Basic Members");
    nameList.append("Preferred Members");
    tableWidget->setVerticalHeaderLabels(nameList);

    QTableWidgetItem* basicItem = new QTableWidgetItem;
    basicItem->setData(Qt::DisplayRole, basic);
    QTableWidgetItem* preferredItem = new QTableWidgetItem;
    preferredItem->setData(Qt::DisplayRole, preferred);

    //tableWidget->setItem(i + 1, 0, basicItem);
    //tableWidget->setItem(i + 2, 0, preferredItem);
}

void product_list::setYearTable(QTableWidget* tableWidget) {
    QStringList nameList;
    product* best, *worst;
    best = worst = nullptr;

    int i = 0;
    for (product* current = head; current != nullptr; i++)
    {
        if (best == nullptr)
        {
            best = current;
            worst = current;
        }
        else
        {
            if (best->getRevenue() < current->getRevenue())
                best = current;

            if (worst->getRevenue() > current->getRevenue())
                worst = current;
        }

        nameList.append(QString::number(i + 1));

        QString qname;
        qname = QString::fromStdString(current->getName());

        QVariant nameValue(qname);
        QVariant quantityValue(current->getQuantity());
        QVariant revenueValue(current->getRevenue());

        QTableWidgetItem* nameItem = new QTableWidgetItem;
        QTableWidgetItem* quantityItem = new QTableWidgetItem;
        QTableWidgetItem* revenueItem = new QTableWidgetItem;

        nameItem->setData(Qt::DisplayRole, nameValue);
        quantityItem->setData(Qt::DisplayRole, quantityValue);
        revenueItem->setData(Qt::DisplayRole, revenueValue);

        tableWidget->setItem(i, 0, nameItem);
        tableWidget->setItem(i, 1, quantityItem);
        tableWidget->setItem(i, 2, revenueItem);

        if (current->getLink())
            current = current->getLink();
        else
        {
            i++;
            break;
        }
    }

    nameList.append("");
    nameList.append("Best");
    nameList.append("Worst");
    tableWidget->setVerticalHeaderLabels(nameList);

    QString qbest, qworst;

    qbest = QString::fromStdString(best->getName());
    qworst = QString::fromStdString(worst->getName());

    QVariant bestValue(qbest);
    QVariant worstValue(qworst);

    QTableWidgetItem* bestItem = new QTableWidgetItem;
    QTableWidgetItem* worstItem = new QTableWidgetItem;

    bestItem->setData(Qt::DisplayRole, bestValue);
    worstItem->setData(Qt::DisplayRole, worstValue);

    tableWidget->setItem(i + 1, 0, bestItem);
    tableWidget->setItem(i + 2, 0, worstItem);
}

product_list& product_list::operator= (const product_list& otherList) {
    if (this == &otherList) return *this;

    setDate(otherList.getMonth(), otherList.getDay(), otherList.getYear());

    for (product* current = otherList.head; current != nullptr;)
    {
        product* newProd = new product(current->getName(), current->getPrice(), current->getQuantity());

        addProduct(newProd);

        if (current->getLink())
            current = current->getLink();
        else
        {
            break;
        }
    }

    return *this;
}

product_list operator+ (const product_list& list1, const product_list& list2) {
    product_list newList = list1;

    for (product* current = list2.head; current != nullptr; current = current->getLink()){
        newList.addProduct(current);
    }

    return newList;
}

