#ifndef UKUIPANEL_H
#define UKUIPANEL_H
#include <QFrame>
#include <QtDebug>
#include "panelpluginsmodel.h"
#include <LXQt/Settings>
#include "ilxqtpanel.h"
#include<QMenu>
#include <QPointer>
#include <QTimer>
#include <QPropertyAnimation>

#define CFG_KEY_PLUGINS            	"plugins"
#define PLUGIN_DESKTOPS_DIR		"/usr/share/lxqt/lxqt-panel/"   //临时位置，后面要获取安装目录 set(PLUGIN_DESKTOPS_DIR \"${CMAKE_INSTALL_FULL_DATAROOTDIR}/lxqt/${PROJECT}\")
#define PLUGIN_DESKTOPS_LOCAL_DIR		"/usr/local/share/lxqt/lxqt-panel/"

class Plugin;
class ILXQtPanel;
class PanelPluginsModel;
class WindowNotifier;
class ConfigPanelDialog;
class UkuiPanel : public QFrame
{
    Q_OBJECT

    friend class PanelPluginsModel;
public:
    enum Alignment {
        AlignmentLeft   = -1, //!< Align the panel to the left or top
        AlignmentCenter =  0, //!< Center the panel
        AlignmentRight  =  1 //!< Align the panel to the right or bottom
    };
public:
        UkuiPanel(const QString &configGroup,LXQt::Settings *settings);
        ~UkuiPanel();
        /*show menu*/
        void showUkuiMenu(Plugin *plugin = 0);
        /*calc pos*/
        QRect calculatePopupWindowPos(QPoint const & absolutePos, QSize const & windowSize) const;
        //ILXQtPanel::Position position() const override { return mPosition; }
        void willShowWindow(QWidget * w);
        void saveSettings(bool _bVar = false);

        /*ui parameter set*/
        // Settings
        int iconSize() const  { return mIconSize; } //!< Implement ILXQtPanel::iconSize().
        int lineCount() const  { return mLineCount; } //!< Implement ILXQtPanel::lineCount().
        int panelSize() const { return mPanelSize; }
        int length() const { return mLength; }
        bool lengthInPercents() const { return mLengthInPercents; }
        //LXQtPanel::Alignment alignment() const { return mAlignment; }
        int screenNum() const { return mScreenNum; }
        QColor fontColor() const { return mFontColor; }
        QColor backgroundColor() const { return mBackgroundColor; }
        QString backgroundImage() const { return mBackgroundImage; }
        int opacity() const { return mOpacity; }
        int reserveSpace() const { return mReserveSpace; }
        bool hidable() const { return mHidable; }
        bool visibleMargin() const { return mVisibleMargin; }
        int animationTime() const { return mAnimationTime; }
        int showDelay() const { return mShowDelayTimer.interval(); }

        void setReserveSpace(bool reserveSpace, bool save);

        bool isPluginSingletonAndRunnig(QString const & pluginId) const;

        QScopedPointer<PanelPluginsModel> mPlugins;
signals:
    /**
     * @brief This signal gets emitted whenever this panel receives a
     * QEvent::LayoutRequest, i.e. "Widget layout needs to be redone.".
     * The PanelPluginsModel will connect this signal to the individual
     * plugins so they can realign, too.
     */
    void realigned();

 public slots:
        void showConfigDialog();
        void showAddPluginDialog();
public:
        void deletedByUser(UkuiPanel *self);
        void pluginAdded();
        LXQt::Settings *settings() const { return mSettings; }

protected:
	bool event(QEvent *event);
	void showEvent(QShowEvent *event) ;
private :
	QString mConfigGroup;

	void loadPlugins();

	QStringList pluginDesktopDirs();

	LXQt::Settings *mSettings;

    int mPanelSize;

    int mIconSize;

    int mLineCount;

    int mLength;

    bool mLengthInPercents;

    Alignment mAlignment;

   // ILXQtPanel::Position mPosition;

    int mScreenNum;

    int mActualScreenNum;

    QTimer mDelaySave;

    bool mHidable;

    bool mVisibleMargin;

    bool mHidden;

    QTimer mHideTimer;

    int mAnimationTime;

    QTimer mShowDelayTimer;

    QColor mFontColor; //!< Font color that is used in the style sheet.
    QColor mBackgroundColor; //!< Background color that is used in the style sheet.
    QString mBackgroundImage; //!< Background image that is used in the style sheet.

    int mOpacity;

    bool mReserveSpace;

    QPointer<ConfigPanelDialog> mConfigDialog;


    QPropertyAnimation *mAnimation;

    bool mLockPanel;

    QScopedPointer<WindowNotifier> mStandaloneWindows;
public slots:
//	void show();
private slots:
	void setPanelGeometry();
	void updateWmStrut();
    //ILXQtPanel::Position mPosition;
};
#endif // UKUIPANEL_H
