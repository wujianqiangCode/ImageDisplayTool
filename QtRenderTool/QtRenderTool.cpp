#include "QtRenderTool.h"
QtRenderTool::QtRenderTool(QWidget *parent)
    : QMainWindow(parent)
{
    m_pTcpClient = new CTcpClient();

}

QtRenderTool::~QtRenderTool()
{
    delete m_pTcpClient;
}

void QtRenderTool::on_checkBoxSetSocketPort_clicked(const QTime &time)
{
    do
    {

    } while (0);
}
