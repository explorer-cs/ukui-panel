#include "ukuiwebviewdialog.h"
#include "ui_ukuiwebviewdialog.h"
#include <QPalette>
#include <QBrush>
#include <QMessageBox>
#include <QColor>
#include <QTime>
#include <QDir>
UkuiWebviewDialog::UkuiWebviewDialog(QWidget *parent) :
    QDialog(parent, Qt::Popup),
    mWebView(NULL),
    ui(new Ui::UkuiWebviewDialog)
{
    ui->setupUi(this);
}

UkuiWebviewDialog::~UkuiWebviewDialog()
{
    delete ui;
}

void UkuiWebviewDialog::creatwebview()
{
    if(!mWebView)
    {
         mWebView = new QWebView(this);
    }
    else
    {
        //deletePopup();
    }
    if(mWebView != NULL)
    {
        QString  htmlFilePath = QLatin1String(PACKAGE_DATA_DIR);
        htmlFilePath = QLatin1String("file://") + htmlFilePath + QLatin1String("/plugin-calendar/html/ukui.html");

        /*set window no margins*/
        mWebView->setWindowFlags(Qt::FramelessWindowHint);
        /*set window size*/
        mWebView->resize(480,400);
        mWebView->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
        mWebView->settings()->setAttribute(QWebSettings::WebAttribute::LocalStorageEnabled, true);
        mWebView->setContextMenuPolicy(Qt::NoContextMenu);
        mWebView->load(QUrl(htmlFilePath));
    }
}


bool UkuiWebviewDialog::event(QEvent *event)
{
    if (event->type() == QEvent::Close)
    {
        emit deactivated();
    }

    return QDialog::event(event);
}
