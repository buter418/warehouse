#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenu>
#include <QPushButton>
#include <QStatusBar>
#include <QStringList>
#include <QTabWidget>
#include <QTableWidget>
#include <QToolBar>
#include <QVBoxLayout>
#include "list_sorted.h"
#include "p_member.h"
#include "product_list.h"
#include "qmenubar.h"
#include "warehouse_function.h"
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
    void searchMemButtonClicked();
    void delMemButtonClicked();
    void addMemButtonClicked();
    void searchSoldButtonClicked();

    node<product_list> *daySales;
    node<product_list> *preferredDaySales;
    node<product_list> *basicDaySales;
    node<product_list> *yearList;
    node<product_list> *preferredYearList;
    node<product_list> *basicYearList;
    node<node<p_member> *> *dailyMembers;
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
    QPushButton *searchMemButton;
    QPushButton *delMemButton;
    QPushButton *addMemButton;
    QTableWidget *memberTable;

    // Item Sales Tab
    QWidget *itemSalesTab;
    QTableWidget *itemSalesTable;

    //Sold Information Tab
    QWidget *soldInfoTab;
    QLineEdit *searchSoldLineEdit;
    QPushButton *searchSoldButton;
    QTableWidget *soldTable;

};

#endif // MAINWINDOW_H
