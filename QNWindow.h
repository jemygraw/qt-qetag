#ifndef QNWINDOW_H
#define QNWINDOW_H

#include <QMainWindow>
class QLabel;
class QLineEdit;
class QPushButton;
class QFileDialog;

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
    QFileDialog *openFileDialog;
public:
    explicit QNWindow(QWidget *parent = 0);

signals:

public slots:
    void calBtnClicked();
    void browseBtnClicked();
    void onFileSelected(QString fileName);
};

#endif // QNWINDOW_H
