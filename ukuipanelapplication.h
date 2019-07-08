#include <QtDebug>
#include <QApplication>
#include <LXQt/Settings>
class UkuiPanelApplicationPrivate;
class UkuiPanelApplication : public QApplication
{
public:	
	UkuiPanelApplication(int& argc, char** argv);
	UkuiPanelApplicationPrivate *const d_ptr;	
	Q_DECLARE_PRIVATE(UkuiPanelApplication)
//	Q_DISABLE_COPY(UkuiPanelApplication)		
};

class UkuiPanelApplicationPrivate {
	Q_DECLARE_PUBLIC(UkuiPanelApplication)
public:

    	UkuiPanelApplicationPrivate(UkuiPanelApplication *q);
//    	~UkuiPanelApplicationPrivate() {};

    	LXQt::Settings *mSettings;

    	UkuiPanelApplication *const q_ptr;
};

