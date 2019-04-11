#ifndef JIBENCANSHUSHEZHI_H
#define JIBENCANSHUSHEZHI_H

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QListView>
#include <QProgressDialog>
#include <QTimer>
#include <QCoreApplication>
#include "mymysql.h"
#include "pubfunc.h"

class jibencanshushezhi : public QDialog
{
    Q_OBJECT
public:
    explicit jibencanshushezhi(QWidget *parent = 0);

private:
    QLineEdit *MenJin1lineEdit;
    QCheckBox *WhetherConnectMenjin;

    QLineEdit *qishiID1LineEdit;
    QLineEdit *qishiID2LineEdit;
    QLineEdit *qishiID3LineEdit;
    QLineEdit *qishiID4LineEdit;

    QComboBox *UnitNumcomBox;
    QComboBox *PlantNamecomBox;
    QComboBox *UnitTypecomBox;

    QPushButton     *genggaiBtn;

    QPushButton     *chazhao1Btn;
    QPushButton     *chazhao2Btn;
    QPushButton     *chazhao3Btn;
    QPushButton     *chazhao4Btn;

    QPushButton     *shezhi1Btn;
    QPushButton     *shezhi2Btn;
    QPushButton     *shezhi3Btn;
    QPushButton     *shezhi4Btn;

    QProgressDialog *progress;
    QTimer          *timer;
    int             currentValue;

signals:

public slots:
    void on_updatejibencanshu();

    void on_chazhao1Btn();
    void on_chazhao2Btn();
    void on_chazhao3Btn();
    void on_chazhao4Btn();

    void on_shezhi1Btn();
    void on_shezhi2Btn();
    void on_shezhi3Btn();
    void on_shezhi4Btn();
};

#endif // JIBENCANSHUSHEZHI_H
