#pragma once

#include <QtWidgets/QMainWindow>
#include <QtGui/QPainter>
#include "ui_QtRenderTool.h"
#include "Socket.h"
class QtRenderTool : public QMainWindow
{
    Q_OBJECT

public:
    QtRenderTool(QWidget *parent = nullptr);
    ~QtRenderTool();
private Q_SLOTS:
    void on_checkBoxSetSocketPort_clicked(bool);
private:
    CTcpClient* m_pTcpClient;
};
