#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdio.h>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->plot->addGraph();


    // Configurando o grafico para ter dois eixos
    ui->plot->yAxis->setTickLabels(false);
    connect(ui->plot->yAxis2, SIGNAL(rangeChanged(QCPRange)), ui->plot->yAxis, SLOT(setRange(QCPRange))); // left axis only mirrors inner right axis
    ui->plot->yAxis2->setVisible(true);
    ui->plot->axisRect()->addAxis(QCPAxis::atRight);
    ui->plot->axisRect()->axis(QCPAxis::atRight, 0)->setPadding(30); // add some padding to have space for tags
    ui->plot->axisRect()->axis(QCPAxis::atRight, 1)->setPadding(30); // add some padding to have space for tags

    // Criando oos graficos
    mGraph1 = ui->plot->addGraph(ui->plot->xAxis, ui->plot->axisRect()->axis(QCPAxis::atRight, 0));
    mGraph2 = ui->plot->addGraph(ui->plot->xAxis, ui->plot->axisRect()->axis(QCPAxis::atRight, 1));
    mGraph1->setPen(QPen(QColor(250, 120, 0)));
    mGraph2->setPen(QPen(QColor(0, 180, 60)));

    // Criando as tags que acompanharao os valores do grafico no eixo vertical
    mTag1 = new AxisTag(mGraph1->valueAxis());
    mTag1->setPen(mGraph1->pen());
    mTag2 = new AxisTag(mGraph2->valueAxis());
    mTag2->setPen(mGraph2->pen());

    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    mDataTimer.start(40);

    // Configuracao da conexao serial com arduino

    arduino = new QSerialPort;
    arduino_nome_porta = "";

  }

  MainWindow::~MainWindow()
  {
    delete ui;
  }

void MainWindow::fun_plot(QVector<double> temp, QVector<double> Y1, QVector<double> Y2)
  {
    // calculate and add a new data point to each graph:
    mGraph1->addData(temp, Y1);
    mGraph2->addData(temp, Y2);

    // make key axis range scroll with the data:
    ui->plot->xAxis->rescale();
    mGraph1->rescaleValueAxis(false, true);
    mGraph2->rescaleValueAxis(false, true);
    ui->plot->xAxis->setRange(ui->plot->xAxis->range().upper, 100, Qt::AlignRight);

    // update the vertical axis tag positions and texts to match the rightmost data point of the graphs:
    double graph1Value = mGraph1->dataMainValue(mGraph1->dataCount()-1);
    double graph2Value = mGraph2->dataMainValue(mGraph2->dataCount()-1);
    mTag1->updatePosition(graph1Value);
    mTag2->updatePosition(graph2Value);
    mTag1->setText(QString::number(graph1Value, 'f', 2));
    mTag2->setText(QString::number(graph2Value, 'f', 2));

    ui->plot->replot();
}

void MainWindow::addPoint()
{

}

void MainWindow::clearData()
{
}


// Funcao para comecar a ler os dados da porta serial
void MainWindow::on_btn_add_clicked()
{
    addPoint();

}
//Limpar buffer e dados do grafico
void MainWindow::on_btn_clear_clicked()
{
    clearData();
}

// Parar a conexao
void MainWindow::on_btn_stop_clicked()
{

}

// Os check buttons serao verificados para a plotagem no grafico
