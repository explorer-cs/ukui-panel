/********************************************************************************
** Form generated from reading UI file 'configpluginswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGPLUGINSWIDGET_H
#define UI_CONFIGPLUGINSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigPluginsWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QListView *listView_plugins;
    QLabel *label;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_3;
    QToolButton *pushButton_moveUp;
    QToolButton *pushButton_moveDown;
    QFrame *line;
    QToolButton *pushButton_addPlugin;
    QToolButton *pushButton_removePlugin;
    QFrame *line_2;
    QToolButton *pushButton_pluginConfig;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *ConfigPluginsWidget)
    {
        if (ConfigPluginsWidget->objectName().isEmpty())
            ConfigPluginsWidget->setObjectName(QStringLiteral("ConfigPluginsWidget"));
        ConfigPluginsWidget->resize(339, 220);
        horizontalLayout = new QHBoxLayout(ConfigPluginsWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(ConfigPluginsWidget);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        listView_plugins = new QListView(widget);
        listView_plugins->setObjectName(QStringLiteral("listView_plugins"));
        listView_plugins->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        listView_plugins->setAlternatingRowColors(true);
        listView_plugins->setSelectionMode(QAbstractItemView::SingleSelection);
        listView_plugins->setSelectionBehavior(QAbstractItemView::SelectRows);
        listView_plugins->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        listView_plugins->setFlow(QListView::TopToBottom);
        listView_plugins->setResizeMode(QListView::Adjust);
        listView_plugins->setSpacing(0);
        listView_plugins->setUniformItemSizes(false);
        listView_plugins->setSelectionRectVisible(true);

        verticalLayout->addWidget(listView_plugins);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setWordWrap(true);

        verticalLayout->addWidget(label);


        horizontalLayout->addWidget(widget);

        widget_5 = new QWidget(ConfigPluginsWidget);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        verticalLayout_3 = new QVBoxLayout(widget_5);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton_moveUp = new QToolButton(widget_5);
        pushButton_moveUp->setObjectName(QStringLiteral("pushButton_moveUp"));
        QIcon icon;
        QString iconThemeName = QStringLiteral("go-up");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral("../../../../../.designer/backup"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_moveUp->setIcon(icon);

        verticalLayout_3->addWidget(pushButton_moveUp);

        pushButton_moveDown = new QToolButton(widget_5);
        pushButton_moveDown->setObjectName(QStringLiteral("pushButton_moveDown"));
        QIcon icon1;
        iconThemeName = QStringLiteral("go-down");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QStringLiteral("../../../../../.designer/backup"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_moveDown->setIcon(icon1);

        verticalLayout_3->addWidget(pushButton_moveDown);

        line = new QFrame(widget_5);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);

        pushButton_addPlugin = new QToolButton(widget_5);
        pushButton_addPlugin->setObjectName(QStringLiteral("pushButton_addPlugin"));
        QIcon icon2;
        iconThemeName = QStringLiteral("list-add");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QStringLiteral("../../../../../.designer/backup"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_addPlugin->setIcon(icon2);

        verticalLayout_3->addWidget(pushButton_addPlugin);

        pushButton_removePlugin = new QToolButton(widget_5);
        pushButton_removePlugin->setObjectName(QStringLiteral("pushButton_removePlugin"));
        QIcon icon3;
        iconThemeName = QStringLiteral("list-remove");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QStringLiteral("../../../../../.designer/backup"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_removePlugin->setIcon(icon3);

        verticalLayout_3->addWidget(pushButton_removePlugin);

        line_2 = new QFrame(widget_5);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_2);

        pushButton_pluginConfig = new QToolButton(widget_5);
        pushButton_pluginConfig->setObjectName(QStringLiteral("pushButton_pluginConfig"));
        QIcon icon4;
        iconThemeName = QStringLiteral("preferences-other");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QStringLiteral("../../../../../.designer/backup"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_pluginConfig->setIcon(icon4);

        verticalLayout_3->addWidget(pushButton_pluginConfig);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout->addWidget(widget_5);


        retranslateUi(ConfigPluginsWidget);

        QMetaObject::connectSlotsByName(ConfigPluginsWidget);
    } // setupUi

    void retranslateUi(QWidget *ConfigPluginsWidget)
    {
        ConfigPluginsWidget->setWindowTitle(QApplication::translate("ConfigPluginsWidget", "Configure Plugins", Q_NULLPTR));
        label->setText(QApplication::translate("ConfigPluginsWidget", "Note: changes made in this page cannot be reset.", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_moveUp->setToolTip(QApplication::translate("ConfigPluginsWidget", "Move up", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_moveUp->setText(QApplication::translate("ConfigPluginsWidget", "...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_moveDown->setToolTip(QApplication::translate("ConfigPluginsWidget", "Move down", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_moveDown->setText(QApplication::translate("ConfigPluginsWidget", "...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_addPlugin->setToolTip(QApplication::translate("ConfigPluginsWidget", "Add", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_addPlugin->setText(QApplication::translate("ConfigPluginsWidget", "...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_removePlugin->setToolTip(QApplication::translate("ConfigPluginsWidget", "Remove", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_removePlugin->setText(QApplication::translate("ConfigPluginsWidget", "...", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pushButton_pluginConfig->setToolTip(QApplication::translate("ConfigPluginsWidget", "Configure", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pushButton_pluginConfig->setText(QApplication::translate("ConfigPluginsWidget", "...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ConfigPluginsWidget: public Ui_ConfigPluginsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGPLUGINSWIDGET_H
