#include "QtRenderTool.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtRenderTool w;
    w.show();
    return a.exec();
}
