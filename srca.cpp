#include "srca.h"
#include "ui_srca.h"
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>

#include <QDebug>

QSerialPort *serial = new QSerialPort;

QString deviceWarning = "Dispositivo não conectado!";

SRCA::SRCA(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SRCA)
{
    ui->setupUi(this);

    //read avaible comports
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
            ui->comboBox->addItem(info.portName());
}

SRCA::~SRCA()
{
    delete ui;
    serial->close();
}

void SRCA::on_pushButton_clicked() // Conectar dispositivo
{
    //select name for our serial port from combobox
    if (serial->portName() != ui->comboBox->currentText())
    {
          serial->close();
          serial->setPortName(ui->comboBox->currentText());
    }

    //setup COM port
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QSerialPort::ReadWrite);

    connect(serial,SIGNAL(readyRead()),this,SLOT(serial_received()));

    if(serial->portName() != NULL)
        ui->label->setText("Conectado em " + serial->portName());
}

void SRCA::on_pushButton_2_clicked() // Enviar dados para controle
{
    QString string = ui->lineEdit->text(); // String que sera enviada

    if(serial->portName() == NULL) // Se não existir dispositivo definido
        QMessageBox::warning(0,0,deviceWarning);
    else if(ui->checkBox->isChecked()) // Checkbox ativado
        QMessageBox::warning(0,0,"Desabilite o Controle por Sensores!");
    else if(string == NULL)
        QMessageBox::warning(0,0,"Campo vazio!");
    else if(ui->radioButton_2->isChecked()) // Controle de posição
    {
        ui->label_2->setText("Controlando posição!");
        send_string(string,"p");
    }
    else if(ui->radioButton->isChecked()) // Controle de velocidade
    {
        ui->label_2->setText("Controlando velocidade!");
        send_string(string,"v");
    }

}

void SRCA::on_checkBox_clicked(bool checked) // Controle via sensores
{
    if(serial->portName() == NULL)
        QMessageBox::warning(0,0,deviceWarning);
    else if(checked == true)
    {
        ui->label_2->setText("Sistema sendo controlado pelos sensores!");

        QString send = "s";
        serial->write(send.toUtf8());
        qDebug()<<"Enviando: "<<send;
    }
}

void SRCA::serial_received()
{
    QString str;
    str = serial->readAll();

    ui->label_3->setText(str);

    qDebug()<<"Valor recebido: "<<str;

}

void SRCA::send_string(QString string, QString control)
{
    QString end = "t";
    QString all = control + string + end;

    serial->write(all.toUtf8()); // Tipo de controle

    qDebug()<<"Enviando: "<<all;

}

