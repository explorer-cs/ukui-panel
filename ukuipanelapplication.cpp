#include <QtDebug>
#include <QUuid>
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

    if (panels.isEmpty())
    {
        panels << "panel1";
    }

    for(const QString& i : qAsConst(panels))
    {
        addPanel(i);
    }
}

UkuiPanel* UkuiPanelApplication::addPanel(const QString& name)
{
    Q_D(UkuiPanelApplication);

    UkuiPanel *panel = new UkuiPanel(name, d->mSettings);
    mPanels << panel;
    qDebug() <<  "the number of panel is 0000000："<<mPanels.count();
    // reemit signals
    connect(panel, &UkuiPanel::deletedByUser, this, &UkuiPanelApplication::removePanel);
    connect(panel, &UkuiPanel::pluginAdded, this, &UkuiPanelApplication::pluginAdded);
    connect(panel, &UkuiPanel::pluginRemoved, this, &UkuiPanelApplication::pluginRemoved);

    return panel;
}


void UkuiPanelApplication::removePanel(UkuiPanel* panel)
{
    Q_D(UkuiPanelApplication);
    Q_ASSERT(mPanels.contains(panel));

    mPanels.removeAll(panel);

    QStringList panels = d->mSettings->value("panels").toStringList();
   // panels.removeAll(panel->name());
    d->mSettings->setValue("panels", panels);

    panel->deleteLater();
}

bool UkuiPanelApplication::isPluginSingletonAndRunnig(QString const & pluginId) const
{
    for (auto const & panel : mPanels)
        if (panel->isPluginSingletonAndRunnig(pluginId))
            return true;

    return false;
}

void UkuiPanelApplication::addNewPanel()
{

    Q_D(UkuiPanelApplication);

    QString name("panel_" + QUuid::createUuid().toString());

    UkuiPanel *p = addPanel(name);
    int screenNum = p->screenNum();
    //ILXQtPanel::Position newPanelPosition = d->computeNewPanelPosition(p, screenNum);
    //p->setPosition(screenNum, newPanelPosition, true);
    QStringList panels = d->mSettings->value("panels").toStringList();
    panels << name;
    d->mSettings->setValue("panels", panels);

    // Poupup the configuration dialog to allow user configuration right away
    p->showConfigDialog();
}

/*
ILXQtPanel::Position UkuiPanelApplicationPrivate::computeNewPanelPosition(const UkuiPanel *p, const int screenNum)
{
    Q_Q(UkuiPanelApplication);
    QVector<bool> screenPositions(4, false); // false means not occupied

    for (int i = 0; i < q->mPanels.size(); ++i) {
        if (p != q->mPanels.at(i)) {
            // We are not the newly added one
            if (screenNum == q->mPanels.at(i)->screenNum()) { // Panels on the same screen
                int p = static_cast<int> (q->mPanels.at(i)->position());
                screenPositions[p] = true; // occupied
            }
        }
    }

    int availablePosition = 0;

    for (int i = 0; i < 4; ++i) { // Bottom, Top, Left, Right
        if (!screenPositions[i]) {
            availablePosition = i;
            break;
        }
    }

    return static_cast<ILXQtPanel::Position> (availablePosition);
}*/


