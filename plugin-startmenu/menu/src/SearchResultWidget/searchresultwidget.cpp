#include "searchresultwidget.h"
#include "ui_searchresultwidget.h"
#include "src/color.h"
#include <QDebug>
#include <QHeaderView>

SearchResultWidget::SearchResultWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchResultWidget)
{
    ui->setupUi(this);
    init_widget();
}

SearchResultWidget::~SearchResultWidget()
{
    delete ui;
}

void SearchResultWidget::init_widget()
{
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground,true);
    char widgetcolor[100];
    sprintf(widgetcolor, "border:0px;background-color:%s;",MAINVIEWWIDGETCOLOR);
    this->setStyleSheet(QString::fromLocal8Bit(widgetcolor));
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    this->setFixedSize(330,462);

    mainLayout=new QHBoxLayout(this);
    mainLayout->setContentsMargins(2,0,2,0);
    searchResultTableWid=new QTableWidget(this);
    mainLayout->addWidget(searchResultTableWid);
    this->setLayout(mainLayout);

    init_search_result_table();
}

void SearchResultWidget::init_search_result_table()
{
    QStringList header;
    header.append("");
    searchResultTableWid->setHorizontalHeaderLabels(header);
    searchResultTableWid->setFixedSize(330-4,462);
    searchResultTableWid->setColumnCount(1);
    searchResultTableWid->verticalHeader()->setDefaultSectionSize(42);
    searchResultTableWid->verticalHeader()->setHidden(true);
    searchResultTableWid->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    searchResultTableWid->setFocusPolicy(Qt::NoFocus);
    searchResultTableWid->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    searchResultTableWid->horizontalHeader()->setFixedHeight(0);
    searchResultTableWid->setEditTriggers(QAbstractItemView::NoEditTriggers);
    searchResultTableWid->setShowGrid(false);
    searchResultTableWid->setStyleSheet("QTableWidget{border:0px;background:transparent;}");
    searchResultTableWid->verticalScrollBar()->setStyleSheet(
                                            "QScrollBar{width:12px;padding-top:15px;padding-bottom:15px;background-color:#283138;}"
                                            "QScrollBar::handle{background-color:#414e59; width:12px;}"
                                            "QScrollBar::handle:hover{background-color:#697883; }"
                                            "QScrollBar::handle:pressed{background-color:#8897a3;}"
                                            "QScrollBar::sub-line{background-color:#283138;height:15px;width:12px;border-image:url(:/data/img/mainviewwidget/滑动条-向上箭头.svg);subcontrol-position:top;}"
                                            "QScrollBar::sub-line:hover{background-color:#697883;}"
                                            "QScrollBar::sub-line:pressed{background-color:#8897a3;border-image:url(:/data/img/mainviewwidget/滑动条-向上箭头-点击.svg);}"
                                            "QScrollBar::add-line{background-color:#283138;height:15px;width:12px;border-image:url(:/data/img/mainviewwidget/滑动条-向下箭头.svg);subcontrol-position:bottom;}"
                                            "QScrollBar::add-line:hover{background-color:#697883;}"
                                            "QScrollBar::add-line:pressed{background-color:#8897a3;border-image:url(:/data/img/mainviewwidget/滑动条-向下箭头-点击.svg);}"
                                            );
}

void SearchResultWidget::fill_search_result_table()
{
    if(!searchResultList.isEmpty())
    {
        searchResultTableWid->setRowCount(searchResultList.count());
        for(int i=0;i<searchResultList.count();i++)
        {
            char btncolor[300];
            sprintf(btncolor,"QToolButton{background:transparent;border:0px;}\
                    QToolButton:hover{background-color:%s;}\
                    QToolButton:pressed{background-color:%s;}", MAINVIEWBTNHOVER,MAINVIEWBTNPRESSED);
            QToolButton* btn=new QToolButton;
            btn->setFixedSize(330-4,42);
            btn->setStyleSheet(QString::fromLocal8Bit(btncolor));
            QHBoxLayout* layout=new QHBoxLayout(btn);
            layout->setContentsMargins(15,0,0,0);
            layout->setSpacing(15);
            QLabel* labelicon=new QLabel(btn);
            labelicon->setFixedSize(32,32);
            labelicon->setStyleSheet("QLabel{background:transparent;}");
            QLabel* labeltext=new QLabel(btn);
            labeltext->adjustSize();
            labeltext->setText(searchResultList.at(i));
            labeltext->setStyleSheet("QLabel{background:transparent;color:#ffffff;font-size:16px;}");
            layout->addWidget(labelicon);
            layout->addWidget(labeltext);
            btn->setLayout(layout);
            btn->setFocusPolicy(Qt::NoFocus);
            searchResultTableWid->setCellWidget(i,0,btn);
        }
    }
    else{
        searchResultTableWid->clear();
        searchResultTableWid->setRowCount(0);
    }
}

void SearchResultWidget::recv_search_keyword(QString arg)
{
    searchResultList.clear();
    //搜索符合arg关键字的程序名
    if(!arg.isEmpty())
    {
        for(int i=0;i<10;i++)
            searchResultList.append(arg);
    }
    else{
        searchResultList.clear();
    }

    fill_search_result_table();
}
