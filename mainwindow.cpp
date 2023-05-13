#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Connect the pushButton clicked() signal to the handleButtonClick slot function
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
}

void MainWindow::handleButtonClick() {
    // Your code to handle the button click  for card pairs  goes here
    ui->pushButton->setText("clicked");
}

MainWindow::~MainWindow()
{
    delete ui;
}

