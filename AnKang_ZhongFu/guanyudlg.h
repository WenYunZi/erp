#ifndef GUANYUDLG_H
#define GUANYUDLG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QSound>

class guanyuDlg : public QDialog
{
    Q_OBJECT
public:
    explicit guanyuDlg(QWidget *parent = 0);

private:
    QLabel      *label1;
    QLabel      *label2;
    QPushButton *Btn;

private slots:
    void on_queding();

};

#endif // GUANYUDLG_H
