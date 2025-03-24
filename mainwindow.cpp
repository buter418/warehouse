#include "mainwindow.h"
#include "product_list.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), day1Products(":/texts/day1.txt"), day2Products(":/texts/day2.txt"),
        day3Products(":/texts/day3.txt"), day4Products(":/texts/day4.txt"), day5Products(":/texts/day5.txt"),
        yearList(day1Products + day2Products + day3Products + day4Products + day5Products)
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
    tabWidget = new QTabWidget(this);

    // ----- Daily Sales Tab -----
    dayTabs = new QTabWidget();

    day1SalesTab = new QWidget();
    day2SalesTab = new QWidget();
    day3SalesTab = new QWidget();
    day4SalesTab = new QWidget();
    day5SalesTab = new QWidget();

    QVBoxLayout *day1Layout = new QVBoxLayout();
    QVBoxLayout *day2Layout = new QVBoxLayout();
    QVBoxLayout *day3Layout = new QVBoxLayout();
    QVBoxLayout *day4Layout = new QVBoxLayout();
    QVBoxLayout *day5Layout = new QVBoxLayout();

    day1SalesTable = new QTableWidget(day1Products.getSize() + 3, 5, this);
    day2SalesTable = new QTableWidget(day2Products.getSize() + 3, 5, this);
    day3SalesTable = new QTableWidget(day3Products.getSize() + 3, 5, this);
    day4SalesTable = new QTableWidget(day4Products.getSize() + 3, 5, this);
    day5SalesTable = new QTableWidget(day5Products.getSize() + 3, 5, this);
    day1SalesTable->setHorizontalHeaderLabels(QStringList() << "Product" << "Date" << "Member" << "Price" << "Quantity");
    day2SalesTable->setHorizontalHeaderLabels(QStringList() << "Product" << "Date" << "Member" << "Price" << "Quantity");
    day3SalesTable->setHorizontalHeaderLabels(QStringList() << "Product" << "Date" << "Member" << "Price" << "Quantity");
    day4SalesTable->setHorizontalHeaderLabels(QStringList() << "Product" << "Date" << "Member" << "Price" << "Quantity");
    day5SalesTable->setHorizontalHeaderLabels(QStringList() << "Product" << "Date" << "Member" << "Price" << "Quantity");

    day1Products.setSalesTable(day1SalesTable);
    day2Products.setSalesTable(day2SalesTable);
    day3Products.setSalesTable(day3SalesTable);
    day4Products.setSalesTable(day4SalesTable);
    day5Products.setSalesTable(day5SalesTable);

    day1Layout->addWidget(day1SalesTable);
    day2Layout->addWidget(day2SalesTable);
    day3Layout->addWidget(day3SalesTable);
    day4Layout->addWidget(day4SalesTable);
    day5Layout->addWidget(day5SalesTable);

    day1SalesTab->setLayout(day1Layout);
    day2SalesTab->setLayout(day2Layout);
    day3SalesTab->setLayout(day3Layout);
    day4SalesTab->setLayout(day4Layout);
    day5SalesTab->setLayout(day5Layout);

    dayTabs->addTab(day1SalesTab, tr("Day 1"));
    dayTabs->addTab(day2SalesTab, tr("Day 2"));
    dayTabs->addTab(day3SalesTab, tr("Day 3"));
    dayTabs->addTab(day4SalesTab, tr("Day 4"));
    dayTabs->addTab(day5SalesTab, tr("Day 5"));
    tabWidget->addTab(dayTabs, tr("Daily Sales"));


    // ----- Yearly Sales Tab -----
    yearlySalesTab = new QWidget();
    QVBoxLayout *yearlyLayout = new QVBoxLayout();

    yearlySalesTable = new QTableWidget(yearList.getSize() + 3, 3, this);

    yearlySalesTable->setHorizontalHeaderLabels(QStringList() << "Item" << "Total Sold" << "Revenue");
    yearList.setYearTable(yearlySalesTable);

    yearlyLayout->addWidget(yearlySalesTable);
    yearlySalesTab->setLayout(yearlyLayout);
    tabWidget->addTab(yearlySalesTab, tr("Yearly Sales"));

    // ----- Member Information Tab -----
    memberInfoTab = new QWidget();
    QVBoxLayout *memberLayout = new QVBoxLayout();

    // Search area for member lookup
    QHBoxLayout *searchLayout = new QHBoxLayout();
    QLabel *searchLabel = new QLabel("Search Member:");
    searchMemberLineEdit = new QLineEdit();
    searchButton = new QPushButton("Search");
    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchMemberLineEdit);
    searchLayout->addWidget(searchButton);
    memberLayout->addLayout(searchLayout);

    // Table showing member details
    memberTable = new QTableWidget(0, 4, this);
    memberTable->setHorizontalHeaderLabels(QStringList() << "Member No." << "Name" << "Type" << "Total Purchases");
    memberLayout->addWidget(memberTable);
    memberInfoTab->setLayout(memberLayout);
    tabWidget->addTab(memberInfoTab, tr("Member Info"));

    // ----- Item Sales Tab -----
    itemSalesTab = new QWidget();
    QVBoxLayout *itemLayout = new QVBoxLayout();
    itemSalesTable = new QTableWidget(0, 3, this);
    itemSalesTable->setHorizontalHeaderLabels(QStringList() << "Item Name" << "Quantity Sold" << "Total Sales");
    itemLayout->addWidget(itemSalesTable);
    itemSalesTab->setLayout(itemLayout);
    tabWidget->addTab(itemSalesTab, tr("Item Sales"));

    setCentralWidget(tabWidget);
}
