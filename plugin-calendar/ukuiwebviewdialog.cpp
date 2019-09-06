#include "ukuiwebviewdialog.h"
#include "ui_ukuiwebviewdialog.h"

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
         mWebView->setStyleSheet("background-color:#0e1316;");
         mWebView->setWindowOpacity(0.95);
        /* if (ischinese)   gtk_widget_set_size_request(d->main_window, 480, 400);
           else gtk_widget_set_size_request(d->main_window, 500, 280);*/
        /*set webview's position*/
        mWebView->settings()->setAttribute(QWebSettings::WebAttribute::LocalStorageEnabled, true);
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
