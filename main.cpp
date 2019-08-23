#include "ukuipanelapplication.h"
int main (int argc, char *argv[])
{
	UkuiPanelApplication app(argc, argv);
    app.setAttribute(Qt::AA_UseHighDpiPixmaps, true);
	return app.exec();		
}
