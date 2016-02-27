#include "graphic.h"

graphic::graphic(QWidget *parent) :
      QWidget(parent)
{

   qRegisterMetaType<QImage>("QImage");
   connect(&thread, SIGNAL(renderedImage(QImage, int)),
           this, SLOT(updatePixmap(QImage, int)));

   pixmap = QPixmap(500, 500);
}

void graphic::newCities(int count)
{

}

void graphic::startThread()
{
}

void graphic::updatePixmap(const QImage &image)
{
   pixmap = QPixmap::fromImage(image);
   update();
}

void graphic::paintEvent(QPaintEvent *)
{
   QPainter painter(this);

   painter.save();
   painter.drawPixmap(0, 0, 500, 500, pixmap);
   painter.restore();
}
