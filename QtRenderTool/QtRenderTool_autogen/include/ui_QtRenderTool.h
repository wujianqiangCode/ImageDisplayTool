/********************************************************************************
** Form generated from reading UI file 'QtRenderTool.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTRENDERTOOL_H
#define UI_QTRENDERTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtRenderTool
{
public:
    QWidget *verticalLayoutWidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QFormLayout *formLayout;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButtonConnect;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *lineSocketPortEdit;
    QLabel *checkBoxSetSocketPort;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineWidthEdit;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineHegihtEdit;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QLineEdit *linePtsEdit;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QPlainTextEdit *plainTextEdit;

    void setupUi(QWidget *QtRenderTool)
    {
        if (QtRenderTool->objectName().isEmpty())
            QtRenderTool->setObjectName(QString::fromUtf8("QtRenderTool"));
        QtRenderTool->resize(1538, 929);
        verticalLayoutWidget = new QWidget(QtRenderTool);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(560, 120, 484, 431));
        gridLayout = new QGridLayout(verticalLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        pushButtonConnect = new QPushButton(verticalLayoutWidget);
        pushButtonConnect->setObjectName(QString::fromUtf8("pushButtonConnect"));

        horizontalLayout_5->addWidget(pushButtonConnect);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_5);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        lineSocketPortEdit = new QLineEdit(verticalLayoutWidget);
        lineSocketPortEdit->setObjectName(QString::fromUtf8("lineSocketPortEdit"));

        horizontalLayout_4->addWidget(lineSocketPortEdit);

        checkBoxSetSocketPort = new QLabel(verticalLayoutWidget);
        checkBoxSetSocketPort->setObjectName(QString::fromUtf8("checkBoxSetSocketPort"));

        horizontalLayout_4->addWidget(checkBoxSetSocketPort);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        verticalLayout_5->addLayout(verticalLayout_3);


        formLayout->setLayout(0, QFormLayout::LabelRole, verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lineWidthEdit = new QLineEdit(verticalLayoutWidget);
        lineWidthEdit->setObjectName(QString::fromUtf8("lineWidthEdit"));

        horizontalLayout_3->addWidget(lineWidthEdit);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);


        verticalLayout_6->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineHegihtEdit = new QLineEdit(verticalLayoutWidget);
        lineHegihtEdit->setObjectName(QString::fromUtf8("lineHegihtEdit"));

        horizontalLayout_2->addWidget(lineHegihtEdit);

        label_3 = new QLabel(verticalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);


        verticalLayout_6->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        linePtsEdit = new QLineEdit(verticalLayoutWidget);
        linePtsEdit->setObjectName(QString::fromUtf8("linePtsEdit"));

        horizontalLayout->addWidget(linePtsEdit);

        label_4 = new QLabel(verticalLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);


        verticalLayout_6->addLayout(horizontalLayout);


        formLayout->setLayout(0, QFormLayout::FieldRole, verticalLayout_6);


        gridLayout_2->addLayout(formLayout, 0, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(label);

        plainTextEdit = new QPlainTextEdit(verticalLayoutWidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        verticalLayout_4->addWidget(plainTextEdit);


        gridLayout_2->addLayout(verticalLayout_4, 1, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);


        retranslateUi(QtRenderTool);

        QMetaObject::connectSlotsByName(QtRenderTool);
    } // setupUi

    void retranslateUi(QWidget *QtRenderTool)
    {
        QtRenderTool->setWindowTitle(QApplication::translate("QtRenderTool", "Main", nullptr));
        pushButtonConnect->setText(QApplication::translate("QtRenderTool", "connect", nullptr));
        lineSocketPortEdit->setText(QApplication::translate("QtRenderTool", "5050", nullptr));
        checkBoxSetSocketPort->setText(QApplication::translate("QtRenderTool", "Port", nullptr));
        label_2->setText(QApplication::translate("QtRenderTool", "width", nullptr));
        label_3->setText(QApplication::translate("QtRenderTool", "height", nullptr));
        label_4->setText(QApplication::translate("QtRenderTool", "PTS", nullptr));
        label->setText(QApplication::translate("QtRenderTool", "Photo Show", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtRenderTool: public Ui_QtRenderTool {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTRENDERTOOL_H
