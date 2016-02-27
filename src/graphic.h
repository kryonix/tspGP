#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QWidget>
#include <QPainter>
#include <QVector>

#include <vector>

#include "tsp_thread.h"

#include "tsp_control.h"

class graphic : public QWidget
{
   Q_OBJECT

private:
   TSP_thread thread;
   QPixmap pixmap;

public:
   explicit graphic(QWidget *parent = 0);
   void newCities(int count);
   void startThread(void);

   tsp::Control ga;
protected:
   void paintEvent(QPaintEvent *);

private slots:
   void updatePixmap(const QImage &image);

};

#endif // GRAPHIC_H
