#ifndef BUTTON_H
#define BUTTON_H
#include <QtGui>
#include <QPushButton>
#include <QToolButton>

class TOOTBtn : public QToolButton
{
    Q_OBJECT
public:
    TOOTBtn(const QString &imgPath, QWidget *parent = 0 )
        : QToolButton(parent)
    {
        _movie = new QMovie(imgPath, QByteArray(), this);
        connect(_movie, SIGNAL(frameChanged(int)), this, SLOT(iconChged(int)));
        _movie->start();

    }


private slots:
    void iconChged(int){
        QPixmap currFrame = _movie->currentPixmap();
        QPixmap pixmap(100,100);
        pixmap.fill( Qt::transparent );
        QPainter painter( &pixmap );
        painter.drawPixmap(( pixmap.width()-currFrame.width()) / 20  ,
                           ( pixmap.height()-currFrame.height()) / 20, currFrame );
        setIcon(QIcon( pixmap));
        setIconSize(pixmap.rect().size());
    }


private:
    QMovie *_movie;


};

#endif // BUTTON_H
