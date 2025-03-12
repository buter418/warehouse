#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>

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

    QTabWidget *tabWidget;

    // Daily Sales Tab
    QWidget *dailySalesTab;
    QTableWidget *dailySalesTable;

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

