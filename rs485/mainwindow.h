#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostAddress>
#include <iostream>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void onReadyCmdRead();

private slots:
    void readData();

    void handleError(QSerialPort::SerialPortError error);

    void on_btnConnect_clicked();

    void on_btnDisConnect_clicked();


    void on_write_clicked();

private:
    Ui::MainWindow *ui;

    QSerialPort* m_serialPort = nullptr;
};
#endif // MAINWINDOW_H
