#ifndef QNWINDOW_H
#define QNWINDOW_H

#include <QMainWindow>
class QLabel;
class QLineEdit;
class QPushButton;

class QNWindow : public QWidget
{
    Q_OBJECT
private:
    QLabel *fileNameLabel;
    QLabel *fileETagLabel;
    QLineEdit *fileNameEdit;
    QLineEdit *fileEtagEdit;
    QPushButton *browseFileBtn;
    QPushButton *calcETagBtn;
public:
    explicit QNWindow(QWidget *parent = 0);

signals:

public slots:
    void calBtnClicked();
};

#endif // QNWINDOW_H
