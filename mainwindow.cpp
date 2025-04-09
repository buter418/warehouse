#include "mainwindow.h"
#include "product_list.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , daySales(nullptr)
{
    setWindowTitle("Amazon");

    // Create the menu bar, toolbar, and status bar.
    createMenus();
    createToolBar();
    createStatusBar();

    // Set up the central widget with tabs.
    setupCentralWidget();
}

MainWindow::~MainWindow()
{
    for (node<product_list> *current = daySales; current != nullptr;) {
        node<product_list> *placehold = current->_next;
        delete current;
        current = placehold;
    }

    for (node<product_list> *current = yearList; current != nullptr;) {
        node<product_list> *placehold = current->_next;
        delete current;
        current = placehold;
    }
}

void MainWindow::createMenus()
{
    // File menu with an Exit action.
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QAction *exitAction = fileMenu->addAction(tr("Exit"));
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    // Reports menu can hold actions for different reports.
    QMenu *reportsMenu = menuBar()->addMenu(tr("&Reports"));
    // Example: reportsMenu->addAction("Daily Report");
}

void MainWindow::createToolBar()
{
    // Create a simple toolbar with a Refresh action.
    QToolBar *toolBar = addToolBar(tr("Main Toolbar"));
    QAction *refreshAction = toolBar->addAction(tr("Refresh"));
    // Connect refreshAction to a slot (e.g., refreshData) when implemented.
    // connect(refreshAction, &QAction::triggered, this, &MainWindow::refreshData);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}










void MainWindow::setupCentralWidget()
{
    inputShopper(allMembers, ":/texts/warehouse_shoppers.txt");
    pMembers = preferredMembers(allMembers);
    bMembers = regularMembers(allMembers);

    tabWidget = new QTabWidget(this);

    // ----- Daily Sales Tab -----------------------------------------------------------------------
    //Create tab for daily sales
    dayTabs = new QTabWidget();

    //Initialize the container for the product sales separated by date.
    getSales();

    node<node<p_member> *> *memberPtr = dailyMembers;
    //Loop for each container/different day of product sales.
    for (node<product_list> *current = daySales; current != nullptr;
         current = current->_next, memberPtr = memberPtr->_next) {
        //Create a widget and layout for a daily sales report
        QWidget *daySalesTab = new QWidget();
        QVBoxLayout *dayLayout = new QVBoxLayout();

        //Intialize the headers and dimensions of the table
        QTableWidget *daySalesTable = new QTableWidget(current->_item.getSize() + 3, 4, this);
        daySalesTable->setHorizontalHeaderLabels(QStringList()
                                                 << "Product" << "Member" << "Price" << "Quantity");

        //Allow table to stretch along with the window in order to stretch the boxes of the table
        daySalesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        //Fill the daily sales table and add the table to the layout, and add the layout to the widget.
        current->_item.setSalesTable(daySalesTable, allMembers, memberPtr->_item);
        dayLayout->addWidget(daySalesTable);
        daySalesTab->setLayout(dayLayout);

        //Add the widget to the tab widget
        dayTabs->addTab(daySalesTab, tr(current->_item.getDate().c_str()));
    }
    //Add the final tab widget with multiple tabs to the larger tab widget
    tabWidget->addTab(dayTabs, tr("Daily Sales"));

    memberPtr = nullptr;
    // ----- Daily Sales Tab -----------------------------------------------------------------------






    // ----- Yearly Sales Tab ------------------------------------------------------------------------
    //Create tab for yearly sales
    yearTabs = new QTabWidget();

    //Initialize contents of product_list container separated by year
    setYearList();

    //Loop for entries in yearList/number of different years purchases have been made in
    for (node<product_list> *current = yearList; current != nullptr; current = current->_next) {
        //Create widget and layout for a yearly sales report
        QWidget *yearlySalesTab = new QWidget();
        QVBoxLayout *yearlyLayout = new QVBoxLayout();

        //Initialize the dimensions and the headers of the table
        QTableWidget *yearlySalesTable = new QTableWidget(current->_item.getSize() + 4, 3, this);
        yearlySalesTable->setHorizontalHeaderLabels(QStringList()
                                                    << "Item" << "Total Sold" << "Revenue");

        //Allow table to stretch along with the window in order to stretch the boxes of the table
        yearlySalesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        //Fill the yearly sales table and add the table to the layout, and add the layout to the widget.
        current->_item.setYearTable(yearlySalesTable);
        yearlyLayout->addWidget(yearlySalesTable);
        yearlySalesTab->setLayout(yearlyLayout);

        //Add the widget to the tab widget
        yearTabs->addTab(yearlySalesTab, tr(std::to_string(current->_item.getYear()).c_str()));
    }
    //Add the final tab widget with multiple tabs to the larger tab widget
    tabWidget->addTab(yearTabs, tr("Yearly Sales"));

    //Set size based on cumulative list

    //Create table based on all 5 lists added together
    // ----- Yearly Sales Tab ------------------------------------------------------------------------



    // ----- Member Information Tab ------------------------------------------------------------------
    memberInfoTab = new QWidget();
    QVBoxLayout *memberLayout = new QVBoxLayout();

    // Search area for member lookup----------------
    QHBoxLayout *searchMemLayout = new QHBoxLayout();

    QLabel *searchMemLabel = new QLabel("Search Member:");
    searchMemberLineEdit = new QLineEdit();
    searchMemButton = new QPushButton("Search");
    searchMemLayout->addWidget(searchMemLabel);
    searchMemLayout->addWidget(searchMemberLineEdit);
    searchMemLayout->addWidget(searchMemButton);

    memberLayout->addLayout(searchMemLayout);
    //----------------------------------------------

    // Table showing member details
    memberTable = new QTableWidget(0, 7, this);
    memberTable->setHorizontalHeaderLabels(QStringList() << "Member No." << "Name" << "Type"
                                                         << "Total Purchases" << "Item" << "Quantity" << "Date");
    memberLayout->addWidget(memberTable);
    memberInfoTab->setLayout(memberLayout);
    tabWidget->addTab(memberInfoTab, tr("Member Info"));
    //----------------------------------------------

    //button event
    connect(searchMemButton, &QPushButton::clicked, this, &MainWindow::searchMemButtonClicked);
    // ----- Member Information Tab ------------------------------------------------------------------



    // ----- Item Sales Tab ---------------------------------------------------------------------------
    itemSalesTab = new QWidget();
    QVBoxLayout *itemLayout = new QVBoxLayout();
    itemSalesTable = new QTableWidget(allProduct.size() + 2, 3, this);
    itemSalesTable->setHorizontalHeaderLabels(QStringList()
                                              << "Item Name" << "Quantity Sold" << "Total Sales");

    QStringList nameList;

    int i = 0;
    double totalRevenue = 0;
    for (List<product>::Iterator current = allProduct.begin(); current != nullptr; i++, current++) {
        nameList.append(QString::number(i + 1));

        //Steps for creating items to fill table with
        std::string revenue;
        double p = current->getRevenue();
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
        qname = QString::fromStdString(current->getName());

        QVariant nameValue(qname);
        QVariant quantityValue(current->getQuantity());
        QVariant revenueValue(QString::fromStdString(revenue));

        QTableWidgetItem *nameItem = new QTableWidgetItem;
        QTableWidgetItem *quantityItem = new QTableWidgetItem;
        QTableWidgetItem *revenueItem = new QTableWidgetItem;

        nameItem->setData(Qt::DisplayRole, nameValue);
        quantityItem->setData(Qt::DisplayRole, quantityValue);
        revenueItem->setData(Qt::DisplayRole, revenueValue);

        //Add items to the table
        itemSalesTable->setItem(i, 0, nameItem);
        itemSalesTable->setItem(i, 1, quantityItem);
        itemSalesTable->setItem(i, 2, revenueItem);
    }

    //Create separate area to show best and worst products
    nameList.append("");
    nameList.append("Total Revenue");
    itemSalesTable->setVerticalHeaderLabels(nameList);

    std::string totalRevenueStr;
    int n = std::round(totalRevenue * 100);
    totalRevenueStr = "$" + to_string(n / 100) + ".";
    if (n % 100 > 0 && n % 100 < 10)
        totalRevenueStr += "0" + to_string(n % 100);
    else if (n % 100 == 0)
        totalRevenueStr += "00";
    else
        totalRevenueStr += to_string(n % 100);

    QTableWidgetItem *totalRevenueItem = new QTableWidgetItem;

    totalRevenueItem->setData(Qt::DisplayRole, QString::fromStdString(totalRevenueStr));
    itemSalesTable->setItem(i + 1, 0, totalRevenueItem);

    itemSalesTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    itemLayout->addWidget(itemSalesTable);
    itemSalesTab->setLayout(itemLayout);
    tabWidget->addTab(itemSalesTab, tr("Item Sales"));
    // ----- Item Sales Tab ---------------------------------------------------------------------------




    // ----- Sold Information Tab ---------------------------------------------------------------------------
    soldInfoTab = new QWidget();
    QVBoxLayout *soldLayout = new QVBoxLayout();

    // Search area for member lookup----------------
    QHBoxLayout *searchSoldLayout = new QHBoxLayout();

    QLabel *searchSoldLabel = new QLabel("Search Item:");
    searchSoldLineEdit = new QLineEdit();
    searchSoldButton = new QPushButton("Search");
    searchSoldLayout->addWidget(searchSoldLabel);
    searchSoldLayout->addWidget(searchSoldLineEdit);
    searchSoldLayout->addWidget(searchSoldButton);

    soldLayout->addLayout(searchSoldLayout);
    //----------------------------------------------

    // Table showing member details
    soldTable = new QTableWidget(0, 3, this);
    soldTable->setHorizontalHeaderLabels(QStringList() << "Name" << "Quantity" << "Total Sales Price");
    soldLayout->addWidget(soldTable);
    soldInfoTab->setLayout(soldLayout);
    tabWidget->addTab(soldInfoTab, tr("Sold Info"));
    //----------------------------------------------

    //button event
    connect(searchSoldButton, &QPushButton::clicked, this, &MainWindow::searchSoldButtonClicked);
    // ----- Purchase Information Tab ---------------------------------------------------------------------------



    setCentralWidget(tabWidget);
}

void MainWindow::getSales()
{
    QFile infile(":/texts/names.txt");
    infile.open(QIODevice::ReadOnly | QIODevice::Text);

    QString filename;
    node<QString> *filenames = nullptr;
    dailyMembers = new node<node<p_member> *>;

    //Loop til eof
    while (true) {
        filename = infile.readLine().trimmed();
        filename = ":/texts/" + filename;

        _insert_head(filenames, filename);

        node<product_list> *newDay = nullptr;
        newDay = new node<product_list>(
            product_list(filename, allMembers, allProduct, dailyMembers->_item));

        if (!infile.atEnd()) {
            _insert_head(dailyMembers, new node<p_member>);
        }

        if (daySales == nullptr)
            daySales = newDay;
        else {
            _insert_head(daySales, newDay->_item);
        }

        if (infile.atEnd())
            break;
    }

    infile.close();

    for (node<QString> *name = filenames; name != nullptr; name = name->_next) {
        inputPurchase(allMembers, name->_item);
    }

    for (node<QString> *current = filenames; current != nullptr;) {
        node<QString> *placehold = current->_next;
        delete current;
        current = placehold;
    }
}

void MainWindow::setYearList()
{
    int year;
    node<product_list> *newYear = new node<product_list>;
    yearList = newYear;
    for (node<product_list> *current = daySales; current != nullptr; current = current->_next) {
        if (current == daySales) {
            year = current->_item.getYear();
        }

        if (year != current->_item.getYear()) {
            newYear = new node<product_list>(current->_item);
            newYear->_next = yearList;
            yearList->_prev = newYear;
            yearList = newYear;
            year = current->_item.getYear();
            newYear->_item.setDate(current->_item.getMonth(),
                                   current->_item.getDay(),
                                   current->_item.getYear());
        } else {
            newYear->_item = newYear->_item + current->_item;
            newYear->_item.setDate(current->_item.getMonth(),
                                   current->_item.getDay(),
                                   current->_item.getYear());
        }
    }
}


void MainWindow::searchMemButtonClicked(){
    List<p_member>::Iterator target;
    string strSearch = searchMemberLineEdit->text().toStdString();
    try{
        int numSearch = stoi(strSearch);
        target = allMembers.member_search(numSearch);
    }catch(const exception& e){
        target = allMembers.member_search(strSearch);
    }

    if(target.is_null())
        return;

    memberTable->setRowCount(target->getTransactions());

    QVariant nameValue(QString::fromStdString(target->getName()));
    QVariant memValue(target->getMembershipNum());
    QVariant memType(QString::fromStdString(target->getType()));
    QVariant purValue(target->getTransactions());

    QTableWidgetItem *nameItem = new QTableWidgetItem;
    QTableWidgetItem *memNumItem = new QTableWidgetItem;
    QTableWidgetItem *memTypeItem = new QTableWidgetItem;
    QTableWidgetItem *purItem = new QTableWidgetItem;

    nameItem->setData(Qt::DisplayRole, nameValue);
    memNumItem->setData(Qt::DisplayRole, memValue);
    memTypeItem->setData(Qt::DisplayRole, memType);
    purItem->setData(Qt::DisplayRole, purValue);

    //Add items to the table
    memberTable->setItem(0, 0, nameItem);
    memberTable->setItem(0, 1, memNumItem);
    memberTable->setItem(0, 2, memTypeItem);
    memberTable->setItem(0, 3, purItem);

    int j = 0;
    List<purchase> allPur = target->getLst();
    for(List<purchase>::Iterator i = allPur.begin(); i != allPur.end(); i++, j++){
        QString date = QString::fromStdString((to_string(i->date[0]) + "/" + to_string(i->date[1]) + "/" + to_string(i->date[2])));

        QVariant pName(QString::fromStdString(i->item.getName()));
        QVariant pQuantity(i->quantity);
        QVariant pDate(date);

        QTableWidgetItem *nameItem = new QTableWidgetItem;
        QTableWidgetItem *quantityItem = new QTableWidgetItem;
        QTableWidgetItem *dateItem = new QTableWidgetItem;

        nameItem->setData(Qt::DisplayRole, pName);
        quantityItem->setData(Qt::DisplayRole, pQuantity);
        dateItem->setData(Qt::DisplayRole, pDate);

        memberTable->setItem(j, 4, nameItem);
        memberTable->setItem(j, 5, quantityItem);
        memberTable->setItem(j, 6, dateItem);
    }
}


void MainWindow::searchSoldButtonClicked(){
    string strSearch = searchSoldLineEdit->text().toStdString();
    List<product>::Iterator target = allProduct.product_search(strSearch);

    if(target.is_null()){
        statusBar()->showMessage(tr("not found"));
        return;
    }

    soldTable->setRowCount(1);

    int n = round(target->getRevenue() * 100.0);
    string totPrice = "$" + to_string(n / 100) + ".";
    if (n % 100 > 0 && n % 100 < 10)
        totPrice += "0" + to_string(n % 100);
    else if (n % 100 == 0)
        totPrice += "00";
    else
        totPrice += to_string(n % 100);

    QVariant nameValue(QString::fromStdString(target->getName()));
    QVariant quantityValue(target->getQuantity());
    QVariant totalPrice(QString::fromStdString(totPrice));

    QTableWidgetItem *nameItem = new QTableWidgetItem;
    QTableWidgetItem *quantityItem = new QTableWidgetItem;
    QTableWidgetItem *priceItem = new QTableWidgetItem;

    nameItem->setData(Qt::DisplayRole, nameValue);
    quantityItem->setData(Qt::DisplayRole, quantityValue);
    priceItem->setData(Qt::DisplayRole, totalPrice);

    //Add items to the table
    soldTable->setItem(0, 0, nameItem);
    soldTable->setItem(0, 1, quantityItem);
    soldTable->setItem(0, 2, priceItem);

}
