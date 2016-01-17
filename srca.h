#ifndef SRCA_H
#define SRCA_H

#include <QMainWindow>

namespace Ui {
class SRCA;
}

class SRCA : public QMainWindow
{
    Q_OBJECT

public:
    explicit SRCA(QWidget *parent = 0);
    ~SRCA();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void send_string(QString,QString);

    void serial_received();

    void on_checkBox_clicked(bool checked);

private:
    Ui::SRCA *ui;
};

#endif // SRCA_H
