#include "QNWindow.h"
#include "QNETag.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
QNWindow::QNWindow(QWidget *parent) :
    QWidget(parent)
{
    //row 1
    fileNameLabel = new QLabel("File");
    fileNameLabel->setFixedWidth(35);
    fileNameEdit = new QLineEdit;
    browseFileBtn = new QPushButton("...");

    QHBoxLayout *layout1=new QHBoxLayout;
    layout1->addWidget(fileNameLabel);
    layout1->addWidget(fileNameEdit);
    layout1->addWidget(browseFileBtn);

    //row 2
    fileETagLabel = new QLabel("ETag");
    fileETagLabel->setFixedWidth(35);
    fileEtagEdit = new QLineEdit;

    QHBoxLayout *layout2=new QHBoxLayout;
    layout2->addWidget(fileETagLabel);
    layout2->addWidget(fileEtagEdit);

    //row 3
    calcETagBtn = new QPushButton("Calculate");
    QHBoxLayout *layout3=new QHBoxLayout;
    layout3->addStretch();
    layout3->addWidget(calcETagBtn);

    QVBoxLayout *mainLayout=new QVBoxLayout;
    mainLayout->addLayout(layout1);
    mainLayout->addLayout(layout2);
    mainLayout->addLayout(layout3);

    setLayout(mainLayout);
    QSize size(450,160);
    setMinimumSize(size);
    setMaximumSize(size);

    openFileDialog=new QFileDialog(this);
    QObject::connect(openFileDialog,SIGNAL(fileSelected(QString)),this,SLOT(onFileSelected(QString)));

    QObject::connect(calcETagBtn,SIGNAL(clicked()),this,SLOT(calBtnClicked()));
    QObject::connect(browseFileBtn,SIGNAL(clicked()),this,SLOT(browseBtnClicked()));

}

void QNWindow::calBtnClicked()
{
    QString fileName=fileNameEdit->text().trimmed();
    QNETag x;
    QString etag=x.CalcETag(fileName);
    fileEtagEdit->setText(etag);
}

void QNWindow::browseBtnClicked()
{
    openFileDialog->show();
}

void QNWindow::onFileSelected(QString fileName)
{
    if(!fileName.isEmpty())
    {
        fileNameEdit->setText(fileName);
        fileEtagEdit->setText("");
    }
}
