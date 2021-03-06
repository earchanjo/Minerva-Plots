#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "axistag.h"

namespace Ui {
class MainWindow;
}
class QSerialPort;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addPoint();
    void clearData();

private slots:
    void on_btn_add_clicked();
    void on_btn_clear_clicked();
    void on_btn_stop_clicked();
    void fun_plot(QVector<double> temp, QVector<double> x, QVector<double> y);

private:
    Ui::MainWindow *ui;
    QSerialPort *arduino;
    QString arduino_nome_porta;
    bool arduino_disponivel;
    QPointer<QCPGraph> mGraph1;
    QPointer<QCPGraph> mGraph2;
    AxisTag *mTag1;
    AxisTag *mTag2;
    QTimer mDataTimer;
    QVector<double> qv_altidude, qv_pressao, qv_temperatura, qv_aceleracao;
};

#endif // MAINWINDOW_H
