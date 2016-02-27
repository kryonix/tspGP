#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <vector>

#include "tsp_thread.h"

namespace Ui {
   class Widget;
}

class Widget : public QWidget {
   Q_OBJECT
public:
   Widget(QWidget *parent = 0);
   ~Widget();

protected:
   void changeEvent(QEvent *e);
   void paintEvent(QPaintEvent *);
   void startThread();

private:
   Ui::Widget *ui;

   TSP_thread thread;
   QPixmap pixmap;

private slots:
   void on_pushButton_7_clicked();
   void on_spinBoxIndividuen_valueChanged(int );
   void on_doubleSpinBoxMutationrate_valueChanged(double );
   void on_pushButton_2_clicked();
   void on_checkBoxMultiThreading_clicked();
   void on_checkBoxReverse_clicked();
   void on_pushButton_6_clicked();
   void updatePixmap(const QImage &image);
   void on_pushButton_5_clicked();
   void on_pushButton_3_clicked();
   void on_pushButton_clicked();

signals:
   void thread_render(int locations, int individuen, double mutationRate, int generationMethod);
   void thread_newPopulation(int individuen, double MutationsRate);
   void thread_optimizeDirection(bool direction);
   void thread_setMutationRate(double mutationRate);
   void thread_setMultithreading(bool multiThreading);
   void thread_togglePause();
   void thread_setPopulationSize(int individuen);

};

#endif // WIDGET_H
