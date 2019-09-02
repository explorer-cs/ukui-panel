#ifndef MAINVIEWWIDGET_H
#define MAINVIEWWIDGET_H

#include <QWidget>
#include <QSpacerItem>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolButton>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QScrollBar>
#include "../CommonUseWidget/commonusewidget.h"
#include "../LetterWidget/letterwidget.h"
#include "../FunctionWidget/functionwidget.h"
#include "../CommonUseWidget/fullcommonusewidget.h"
#include "../FunctionWidget/fullfunctionwidget.h"
#include "../LetterWidget/fullletterwidget.h"
#include "../SearchResultWidget/fullsearchresultwidget.h"
#include "../SearchResultWidget/searchresultwidget.h"

namespace Ui {
class MainViewWidget;
}

class MainViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainViewWidget(QWidget *parent = 0);
    ~MainViewWidget();

    /**
     * @设置主界面从全屏回到默认状态时应加载的分类窗口
     * @param arg分类窗口编号，1常用分类窗口，2字母分类窗口，3功能分类窗口
     */
    void load_classification_widget(int arg);

    /**
     * @主界面全屏时应加载的分类窗口
     * @param arg分类窗口编号，1常用分类窗口，2字母分类窗口，3功能分类窗口
     */
    void load_full_classification_widget(int arg);

private:
    Ui::MainViewWidget *ui;

    QVBoxLayout* mainLayout=NULL;
    QWidget* topWidget=NULL;
    QVBoxLayout* topLayout=NULL;

    QSpacerItem* verticalSpacer=NULL;
    QWidget* minmaxWidget=NULL;
    QHBoxLayout* minmaxLayout=NULL;
    QToolButton* minmaxbtn=NULL;
    QSpacerItem* horizontalSpacer=NULL;

    QWidget* queryWidget=NULL;
    QLineEdit* querylineEdit=NULL;
    QToolButton* querybtn=NULL;
    QHBoxLayout* queryLayout=NULL;

    FullSearchResultWidget* fullsearchresultwid=NULL;
    SearchResultWidget* searchresultwid=NULL;
    QHBoxLayout* searchResultWidLayout=NULL;
    QWidget* searchResultWid=NULL;
    QTableWidget* searchResultTableWid=NULL;

    CommonUseWidget* commonusewid=NULL;
    LetterWidget* letterwid=NULL;
    FunctionWidget* functionwid=NULL;

    int widgetState=-1;//分类窗口编号

    bool is_fullWid=false;

    int letterwid_state=0;
    int functionwid_state=0;
    QString letterbtnname;
    QString functionbtnname;

    FullCommonUseWidget* fullcommonusewid=NULL;
    FullLetterWidget* fullletterwid=NULL;
    FullFunctionWidget* fullfunctionwid=NULL;

protected:
    void init_widget();//初始化界面
    void init_top_widget();
    void add_top_control();//添加顶部窗口控件
    void add_query_lineedit();//添加查询框
    void set_min_btn();//设置还原按钮
    void set_max_btn();//设置全屏按钮

    void add_search_result_widget();//添加搜索列表界面
    void fill_search_result_tablewid();//填充默认态程序搜索列表
    void fill_full_search_result_tablewid();//填充全屏态程序搜索列表

//    void keyPressEvent(QKeyEvent* e);//查询框响应键盘事件

public:
    void load_min_mainview();//加载默认主视图
    void load_max_mainview();//加载全屏主视图

private slots:
    bool eventFilter(QObject *watched, QEvent *event);

    void fullscreen_btn_slot();//全屏按钮槽函数
    void load_commonuse_widget();//加载常用分类界面
    void load_letter_widget();//加载字母分类界面
    void load_function_widget();//加载功能分类界面

    void default_btn_slot();//默认态按钮槽函数
    void load_fullcommonuse_widget();//加载全屏常用分类界面
    void load_fullletter_widget();//加载全屏字母分类界面
    void load_fullfunction_widget();//加载全屏功能分类界面

    /**
     * 接收默认或全屏字母排序界面状态信号
     * @param arg为0时字母排序界面加载的是应用列表，为1时加载的是纯字母按钮界面
     * @param btnname存放纯字母按钮界面被点击的按钮名称
     */
    void recv_letterwid_state(int arg,QString btnname);

    /**
     * 接收默认与全屏功能分类界面状态信号
     * @param arg为0时功能分类界面加载的是应用列表，为1时加载的是纯功能分类按钮界面
     * @param btnname存放纯功能分类按钮界面被点击的按钮名称
     */
    void recv_functionwid_state(int arg,QString btnname);


    /**
     * 搜索程序和文件槽函数
     */
    void search_app_slot(QString arg);

signals:
    /**
     * @发送全屏按钮点击信号
     * @param arg当前所加载的分类窗口编号
     */
    void send_fullscreenbtn_signal(int arg);

    /**
     * @发送默认(还原)按钮点击信号
     * @param arg当前所加载的分类窗口编号
     */
    void send_defaultbtn_signal(int arg);

    /**
     * 发送搜索框的搜索关键字
     */
    void send_search_keyword(QString arg);

};

#endif // MAINVIEWWIDGET_H
