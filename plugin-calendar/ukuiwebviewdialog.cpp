#include "ukuiwebviewdialog.h"
#include "ui_ukuiwebviewdialog.h"
#include <QPalette>
#include <QBrush>
#include <QMessageBox>
#include <QColor>
#include <QTime>
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
        QColor color = this->palette().background().color();

        char color_hex[10]={0};
        char color_hex_red[4]={0};
        char color_hex_green[4]={0};
        char color_hex_blue[4]={0};

//        if((color.red()/257/16)==0){
//            sprintf(color_hex_red,"0%x",color.red()/257);
//        } else {
//            sprintf(color_hex_red,"%x",color.red()/257);
//        }
//        if((color.green()/257)/16==0){
//            sprintf(color_hex_green,"0%x",color.green()/257);
//        } else {
//            sprintf(color_hex_green,"%x",color.green/257);
//        }
//        if((color.blue()/257)/16==0){
//            sprintf(color_hex_blue,"0%x",color.blue()/257);
//        } else {
//            sprintf(color_hex_blue,"%x",color.blue/257);
//        }
//        sprintf(color_hex,"\#%s%s%s",color_hex_red,color_hex_green,color_hex_blue);
//        QString str("document.getElementById('header').style.background='red';");
#if 0
        if (!strcmp (color_hex, "#000000")){
            script=g_strdup_printf ("\
                          var zodiac_icon = document.getElementById('zodiac_icon');\
                          zodiac_icon.setAttribute('src', '/usr/share/ukui-indicators/indicator-calendar/html/images/zodiac/black/black-pig.png');\
                          zodiac_icon.setAttribute('style', 'padding-top: 33px');\
                          var checkbox = document.getElementById('checkbox');\
                          if (checkbox.checked){\
                              zodiac_icon.setAttribute('style', 'display:none');\
                          }\
                          document.getElementById('header').style.background='%s';\
                          document.getElementById('day').style.color='%s';\
                          document.getElementById('left_pane').style.background='%s';\
                          document.getElementById('right_pane').style.background='%s';\
                          var css1 = 'td {position: relative;left: 0;top: 0;border: 1px solid transparent;border-top: 1px solid #262e34;padding: 2px 12px;text-align: center;}';var style1 = document.createElement('style');\
                          if (style1.styleSheet) {\
                              style1.styleSheet.cssText = css1;\
                          } else {\
                                              style1.appendChild(document.createTextNode(css1));\
                                          }\
                          document.getElementsByTagName('td')[0].appendChild(style1);\
                          var css1 = 'td:active {background: #2b87a8;}';var style1 = document.createElement('style');\
                          if (style1.styleSheet) {\
                              style1.styleSheet.cssText = css1;\
                          } else {\
                                              style1.appendChild(document.createTextNode(css1));\
                                          }\
                          document.getElementsByTagName('td')[0].appendChild(style1);\
                          var css1 = 'td:hover {border: 1px solid #3593b5}';var style1 = document.createElement('style');\
                          if (style1.styleSheet) {\
                              style1.styleSheet.cssText = css1;\
                          } else {\
                                              style1.appendChild(document.createTextNode(css1));\
                                          }\
                          document.getElementsByTagName('td')[0].appendChild(style1);\
                          var day_highlight_len=document.getElementsByClassName('day_highlight').length;\
                          for (var i=0; i<day_today_len; i++){\
                              document.getElementsByClassName('day_highlight')[i].getElementsByClassName('solar_part')[0].style.color='#ffffff';\
                              document.getElementsByClassName('day_highlight')[i].getElementsByClassName('lunar_part ')[0].style.color='#ffffff';\
                              }\
                          var day_today_len=document.getElementsByClassName('day_today').length;\
                          for (var i=0; i<day_today_len; i++){\
                              document.getElementsByClassName('day_today')[i].getElementsByClassName('solar_part')[0].style.color='#ffffff';\
                              document.getElementsByClassName('day_today')[i].getElementsByClassName('lunar_part ')[0].style.color='#ffffff';\
                              }\
                          var day_this_month_len=document.getElementsByClassName('day_this_month').length;\
                          for (var i=0; i<day_this_month_len; i++){\
                              document.getElementsByClassName('day_this_month')[i].getElementsByClassName('solar_part')[0].style.color='#ffffff';\
                              document.getElementsByClassName('day_this_month')[i].getElementsByClassName('lunar_part ')[0].style.color='#aaaaaa';\
                              }\
                          var day_other_month_len=document.getElementsByClassName('day_other_month').length;\
                          for (var i=0; i<day_other_month_len; i++){\
                              document.getElementsByClassName('day_other_month')[i].getElementsByClassName('solar_part')[0].style.color='#777777';\
                              document.getElementsByClassName('day_other_month')[i].getElementsByClassName('lunar_part ')[0].style.color='#777777';\
                              }\
                          document.getElementsByClassName('effect_button')[0].style.backgroundColor='%s';\
                          document.getElementsByClassName('effect_button')[1].style.background='%s';\
                          document.getElementsByClassName('effect_button')[2].style.background='%s';\
                          document.getElementsByClassName('effect_button')[3].style.backgroundColor='%s';\
                          document.getElementsByClassName('effect_button')[4].style.background='%s';\
                          document.getElementsByClassName('effect_button')[5].style.background='%s';\
                          document.getElementById('general_datetime_list').style.padding='5px 6px 20px 5px';\
                          document.getElementById('general_datetime_list').style.borderBottom ='1px solid #343d45';\
                          var li_length=document.getElementById('general_datetime_list').getElementsByTagName('li').length;\
                          for (var i=0;i<li_length; i++){\
                              document.getElementById('general_datetime_list').getElementsByTagName('li')[i].style.color='#aaaaaa';\
                          }\
                          document.getElementById('general_datetime_list').getElementsByTagName('li')[1].style.color='#3593b5';\
                          var td_length=document.getElementById('hl_table').getElementsByTagName('td').length;\
                          for (var i=0;i<td_length; i++){\
                              document.getElementById('hl_table').getElementsByTagName('td')[i].style.color='#aaaaaa';\
                          }\
                          document.getElementsByClassName('worktime1')[1].style.height='15px';\
                          document.getElementsByClassName('worktime2')[1].style.width='15px';\
                          document.getElementsByClassName('worktime2')[1].style.height='15px';\
                          ",\
                          color_hex,color_hex,"#151a1e","#1f2428",color_hex,color_hex,color_hex,color_hex,color_hex,color_hex);
        }
        else{
            script=g_strdup_printf ("\
                          var zodiac_icon = document.getElementById('zodiac_icon');\
                          zodiac_icon.setAttribute('src', '/usr/share/ukui-indicators/indicator-calendar/html/images/zodiac/blue/blue-pig.png');\
                          zodiac_icon.setAttribute('style', 'padding-top: 33px');\
                          var checkbox = document.getElementById('checkbox');\
                          if (checkbox.checked){\
                              zodiac_icon.setAttribute('style', 'display:none');\
                          }\
                                          document.getElementById('header').style.background='%s';\
                                          document.getElementById('day').style.color='%s';\
                                          document.getElementsByClassName('effect_button')[0].style.backgroundColor='%s';\
                                          document.getElementsByClassName('effect_button')[1].style.background='%s';\
                                          document.getElementsByClassName('effect_button')[2].style.background='%s';\
                                          document.getElementsByClassName('effect_button')[3].style.backgroundColor='%s';\
                                          document.getElementsByClassName('effect_button')[4].style.background='%s';\
                                          document.getElementsByClassName('effect_button')[5].style.background='%s';\
                                          var css = 'table td:hover{border: 1px solid %s;}';var style = document.createElement('style');\
                                          if (style.styleSheet) {\
                                              style.styleSheet.cssText = css;\
                                          } else {\
                                              style.appendChild(document.createTextNode(css));\
                                          }\
                                          document.getElementsByTagName('head')[0].appendChild(style);\
                                          var css = '.day_today{border: 1px solid %s;}';var style = document.createElement('style');\
                                          if (style.styleSheet) {\
                                              style.styleSheet.cssText = css;\
                                          } else {\
                                              style.appendChild(document.createTextNode(css));\
                                          }\
                                          document.getElementsByTagName('head')[0].appendChild(style);\
                                          var css = '.day_today:hover{border: 1px solid %s;}';var style = document.createElement('style');\
                                          if (style.styleSheet) {\
                                              style.styleSheet.cssText = css;\
                                          } else {\
                                              style.appendChild(document.createTextNode(css));\
                                          }\
                                          document.getElementsByTagName('head')[0].appendChild(style);\
                                          ",\
                                          color_hex,color_hex,color_hex,color_hex,color_hex,color_hex,color_hex,color_hex,color_hex,color_hex,color_hex);
        }
#endif


        //htmlFilePath = QLatin1String("file://") + htmlFilePath + QLatin1String("/plugin-calendar/html/ukui.html");
        htmlFilePath = QLatin1String("file://") + htmlFilePath + QLatin1String("/plugin-calendar/html/ukui.html");

        /*set window no margins*/
        mWebView->setWindowFlags(Qt::FramelessWindowHint);
        /*set window size*/
         mWebView->resize(480,400);
         //mWebView->setAttribute(Qt::WA_TranslucentBackground);
        /* if (ischinese)   gtk_widget_set_size_request(d->main_window, 480, 400);
           else gtk_widget_set_size_request(d->main_window, 500, 280);*/
        /*set webview's position*/
//         mWebView->setAttribute(Qt::WA_TranslucentBackground);
//         mWebView->setStyleSheet("background:transparent");
        mWebView->settings()->setAttribute(QWebSettings::JavascriptEnabled,true);
        mWebView->setAutoFillBackground(true);
        mWebView->settings()->setAttribute(QWebSettings::WebAttribute::LocalStorageEnabled, true);
        mWebView->load(QUrl(htmlFilePath));
//        QTime qTimer = QTime::currentTime().addSecs(10);
//        while(QTime::currentTime() < qTimer){}
        //mWebView->page()->mainFrame()->addToJavaScriptWindowObject(str,mWebView);
        //QString cmd = QString("alert('okoko')");
        //mWebView->show();
        //QString cmd = QString("document.getElementById('header').style.background='#FF0000';");
//        QString cmd = QString("alert(document.getElementById('header'))");
//        mWebView->page()->mainFrame()->evaluateJavaScript(cmd);
//

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
