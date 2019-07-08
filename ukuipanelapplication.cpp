#include <QtDebug>
#include "ukuipanelapplication.h"
#include "ukuipanel.h"

UkuiPanelApplicationPrivate::UkuiPanelApplicationPrivate(UkuiPanelApplication *q)
    : mSettings(0),
      q_ptr(q)
{
}
UkuiPanelApplication::UkuiPanelApplication(int& argc, char** argv)
	:QApplication(argc, argv),
	d_ptr(new UkuiPanelApplicationPrivate(this))
{
	Q_D(UkuiPanelApplication);
	qDebug()<< "UkuiPanelApplication::UkuiPanelApplication";
	QStringList panels;
	panels << QStringLiteral("panel1");
	d->mSettings = new LXQt::Settings(QLatin1String("panel"), this);
	for(const QString& i : qAsConst(panels)){
		new UkuiPanel(i,d->mSettings);
	}
}	
