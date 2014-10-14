#include <QApplication>
#include "QNETag.h"
#include "QNWindow.h"
#include <stdio.h>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QNWindow *wnd=new QNWindow;
    wnd->setWindowTitle("Calculate ETag - Qiniu");
    wnd->show();
    return app.exec();
}
