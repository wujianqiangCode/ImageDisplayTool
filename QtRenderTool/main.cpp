#include <QtWidgets/QApplication>
#include <QtCore/QSharedMemory>
#include "QtRenderTool.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //使用QSharedMemory防止多开
	QSharedMemory shared_memory;
	shared_memory.setKey(QString("main_window"));
	if (shared_memory.attach())
	{
		return 0;
	}

    if (shared_memory.create(1))
	{
		QtRenderTool w;
		w.show();
		return a.exec();
	}

}
