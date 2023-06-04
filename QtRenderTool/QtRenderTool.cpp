#include "QtRenderTool.h"
QtRenderTool::QtRenderTool(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    //信号槽绑定
    connect(
		ui.pushButtonConnect,    // 对象a, 必须是一个QObject*类型
		SIGNAL(clicked()),   // a的信号
		this,// 对象b
		SLOT(on_checkBoxSetSocketPort_clicked()) // b的槽
		);

    m_pTcpServer = new CTcpServer(NULL);

    m_nTimerID = startTimer(10);

}

QtRenderTool::~QtRenderTool()
{
    delete m_pTcpServer;
}


void QtRenderTool::on_checkBoxSetSocketPort_clicked()
{
    int nPort = ui.lineSocketPortEdit->text().toInt();

    bool bFlag = m_pTcpServer->InitServer(nPort);
    if (bFlag == false)
    {
        QMessageBox::critical(this, tr("消息框"), tr("初始化InitServer失败!"));
    }

    m_pTcpServer->Create();
    
    return;
}



void QtRenderTool::timerEvent(QTimerEvent * event)
{

	if (event->timerId() == m_nTimerID)
	{
        if (m_pTcpServer->m_strLogInfo[0] != '\0')
        {
            ui.plainTextEdit->appendPlainText(QString(QString::fromLocal8Bit(m_pTcpServer->m_strLogInfo)));
            m_pTcpServer->m_strLogInfo[0] = '\0';
        }
        else if ((m_pTcpServer->m_nImageHeight != 0) && (m_pTcpServer->m_nImageWidth != 0) && (m_pTcpServer->m_pImageData != nullptr))
        {
            QImage image = QImage(m_pTcpServer->m_pImageData, m_pTcpServer->m_nImageWidth, m_pTcpServer->m_nImageHeight, QImage::Format_RGB32);//Format_RGB32：BGRABGRA
        
            image = image.mirrored(false, true);

            QPixmap pixmap;
            pixmap = pixmap.fromImage(image);

            QPixmap fitpixmap = pixmap.scaled(m_pTcpServer->m_nImageWidth, m_pTcpServer->m_nImageHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
        
            ui.label->setPixmap(fitpixmap);
            ui.label->setScaledContents(true);

            m_pTcpServer->m_nImageHeight = 0;
            m_pTcpServer->m_nImageWidth = 0;
            delete[] m_pTcpServer->m_pImageData;
            m_pTcpServer->m_pImageData = nullptr;
        }
		
	}
}