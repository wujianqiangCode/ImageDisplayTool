#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtRenderTool.h"
#include <QtGui/QPainter>
#include "Socket.h"
class QtRenderTool : public QMainWindow
{
    Q_OBJECT

public:
    QtRenderTool(QWidget *parent = nullptr);
    ~QtRenderTool();

protected:
    void paintEvent(QPaintEvent*);

private:
    Ui::QtRenderToolClass ui;

    CTcpClient m_tcpClient;
};
