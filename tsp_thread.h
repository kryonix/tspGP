#ifndef TSP_THREAD_H
#define TSP_THREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QPainter>
#include <QVector>
#include <QElapsedTimer>

#include <fstream>
#include "timer.h"

//#include "benchmark.h"

#include "tsp_control.h"

class TSP_thread : public QThread
{
   Q_OBJECT

private:
   QImage paint();

   QMutex mutex;
   QWaitCondition condition;

   Timer mTimer;
   QElapsedTimer mTimer_2;

   bool paused;
   bool abort;
   double lastFitness;

public:
   TSP_thread(QObject *parent = 0);
   ~TSP_thread();

   tsp::Control ga;

public slots:
   void render(int locations, int individuen, double mutationRate, int generationMethod);
   void newPopulation(int individuen, double MutationsRate);

   void togglePause();
   void setDirection(bool direction);

   void setMultiThreading(bool multiThreading);
   void setMutationRate(double mutationRate);

   void setPopulationSize(int individuen);
signals:
   void renderedImage(const QImage &image);

protected:
   void run();
};

#endif // TSP_THREAD_H
