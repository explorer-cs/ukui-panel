#include <QtDebug>
#include <QApplication>
#include <LXQt/Settings>
#include "ilxqtpanel.h"

class UkuiPanel;
class ILXQtPanel;
class UkuiPanelApplicationPrivate;
class UkuiPanelApplication : public QApplication
{
    Q_OBJECT
public:	
	UkuiPanelApplication(int& argc, char** argv);
        int count() const { return mPanels.count(); }
	UkuiPanelApplicationPrivate *const d_ptr;	
	Q_DECLARE_PRIVATE(UkuiPanelApplication)
//	Q_DISABLE_COPY(UkuiPanelApplication)

        UkuiPanel*addPanel(const QString& name);

        bool isPluginSingletonAndRunnig(QString const & pluginId) const;

public slots:
    void addNewPanel();
    void removePanel(UkuiPanel* panel);

signals:
    /*!
     * \brief Signal that re-emits the signal pluginAdded() from LXQtPanel.
     */
    void pluginAdded();

    void pluginRemoved();
private:
    QList<UkuiPanel*> mPanels;
};

class UkuiPanelApplicationPrivate {
	Q_DECLARE_PUBLIC(UkuiPanelApplication)
public:

    	UkuiPanelApplicationPrivate(UkuiPanelApplication *q);
        ILXQtPanel::Position computeNewPanelPosition(const UkuiPanel *p, const int screenNum);
//    	~UkuiPanelApplicationPrivate() {};

    	LXQt::Settings *mSettings;

    	UkuiPanelApplication *const q_ptr;
};

