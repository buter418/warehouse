#include "mainwindow.h"
#include "qmenubar.h"
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
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
    dailySalesTab = new QWidget();
    QVBoxLayout *dailyLayout = new QVBoxLayout();
    dailySalesTable = new QTableWidget(0, 5, this);
    dailySalesTable->setHorizontalHeaderLabels(QStringList() << "Date" << "Member" << "Item" << "Price" << "Quantity");
    dailyLayout->addWidget(dailySalesTable);
    dailySalesTab->setLayout(dailyLayout);
    tabWidget->addTab(dailySalesTab, tr("Daily Sales"));

    // ----- Yearly Sales Tab -----
    yearlySalesTab = new QWidget();
    QVBoxLayout *yearlyLayout = new QVBoxLayout();
    yearlySalesTable = new QTableWidget(0, 5, this);
    yearlySalesTable->setHorizontalHeaderLabels(QStringList() << "Item" << "Total Sold" << "Revenue" << "Best/Worst" << "Comments");
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
