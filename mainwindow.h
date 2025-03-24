#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "product_list.h"
#include "qmenubar.h"
#include <QMainWindow>
#include <QTabWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QStringList>

class product_list;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createMenus();
    void createToolBar();
    void createStatusBar();
    void setupCentralWidget();

    product_list day1Products;
    product_list day2Products;
    product_list day3Products;
    product_list day4Products;
    product_list day5Products;
    product_list yearList;

    QTabWidget *tabWidget;

    // Daily Sales Tab
    QTabWidget *dayTabs;
    QWidget *day1SalesTab;
    QWidget *day2SalesTab;
    QWidget *day3SalesTab;
    QWidget *day4SalesTab;
    QWidget *day5SalesTab;
    QTableWidget *day1SalesTable;
    QTableWidget *day2SalesTable;
    QTableWidget *day3SalesTable;
    QTableWidget *day4SalesTable;
    QTableWidget *day5SalesTable;

    // Yearly Sales Tab
    QWidget *yearlySalesTab;
    QTableWidget *yearlySalesTable;

    // Member Information Tab
    QWidget *memberInfoTab;
    QLineEdit *searchMemberLineEdit;
    QPushButton *searchButton;
    QTableWidget *memberTable;

    // Item Sales Tab
    QWidget *itemSalesTab;
    QTableWidget *itemSalesTable;
};

#endif // MAINWINDOW_H

