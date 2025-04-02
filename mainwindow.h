#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "product_list.h"
#include "p_member.h"
#include "qmenubar.h"
#include "list_sorted.h"
#include "warehouse_function.h"
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
#include <QHeaderView>
#include <fstream>

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
    void getSales();
    void setYearList();


    node<product_list>* daySales;
    node<product_list>* preferredDaySales;
    node<product_list>* basicDaySales;
    node<product_list>* yearList;
    node<product_list>* preferredYearList;
    node<product_list>* basicYearList;
    node<node<p_member>*>* dailyMembers;
    List<p_member> allMembers;
    List<p_member> pMembers;
    List<member> bMembers;
    List<product> allProduct;
    List<product> preferredPurchases;
    List<product> basicPurchases;

    QTabWidget *tabWidget;

    // Daily Sales Tab
    QTabWidget *dayTabs;
    QTabWidget *yearTabs;

    // Yearly Sales Tab

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

