/*****************************************************************************
*  QtRenderTool
*  Copyright (C) 2023 ijianqiangwu@outlook.com
*
*  @file     ServerSocket.h
*  @brief    对文件的简述
*  Details.
*
*  @author   WuJianQiang
*  @email    ijianqiangwu@outlook.com
*  @version  1.0.0.1(版本号)
*  @date     2023.05.30
*  @license  GNU General Public License (GPL)
*
*----------------------------------------------------------------------------
*  Remark         : Description
*----------------------------------------------------------------------------
*  Change History :
*  <Date>     | <Version> | <Author>       | <Description>
*----------------------------------------------------------------------------
*  2023/05/30 | 1.0.0.1   | WuJianQiang          | Create file
*----------------------------------------------------------------------------
*
*****************************************************************************/

#pragma once

#include <QtWidgets/QMainWindow>
#include <QtGui/QPainter>
#include <QtWidgets/QMessageBox>
#include "ui_QtRenderTool.h"
#include "ServerSocket.h"
class QtRenderTool : public QMainWindow
{
    Q_OBJECT

public:
    QtRenderTool(QWidget *parent = nullptr);
    ~QtRenderTool();

    virtual void timerEvent(QTimerEvent * event);

private Q_SLOTS:
    void on_checkBoxSetSocketPort_clicked();
private:

    Ui::QtRenderTool ui;

    CTcpServer* m_pTcpServer;

    int m_nTimerID; // 定时器ID
};
