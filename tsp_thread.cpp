#include "tsp_thread.h"

#define BENCH false

TSP_thread::TSP_thread(QObject *parent) : QThread(parent)
{
   abort = false;
   paused = false;
}

TSP_thread::~TSP_thread()
{
   mutex.lock();
   abort = true;
   condition.wakeOne();
   mutex.unlock();

   wait();
}

void TSP_thread::render(int locations, int individuen, double mutationRate, int generationMethod = 0 )
{
   QMutexLocker locker(&mutex);

   ga.deleteAllLocations(); //ggf. Vorhandene Punkte löschen
   ga.clearIndividuen(); // ggf. Vorhandene Individuen löschen

   ga.setMaxLocations(locations); // Anzahl der Punkte setzen
   ga.setGenerationMethod(generationMethod); // Art der Stadtgeneration einstellen
   ga.newRandomLocations(); // Neue Punkte Zufällig generieren

   ga.setMaxMutationRate(mutationRate); //Mutationsrate setzen

   ga.setMaxIndividuen(individuen); // Anzahl der Individuen setzen
   ga.createPopulation(); // Population generieren

   //paused = true;
   lastFitness = 0.0;
   emit renderedImage(paint()); // Bildausgabe

   // Thread starten oder Aufwecken

   mTimer_2.start();
   mTimer.Start();

   if (!isRunning()) {
      start(LowPriority);
   } else {
      paused = false;
      condition.wakeOne();
   }
}

void TSP_thread::newPopulation(int individuen, double MutationsRate)
{
   QMutexLocker locker(&mutex);
   //paused = true; // Thread Pausieren
   lastFitness = 0.0;
   ga.clearIndividuen(); // Individuen Löschen
   ga.setMaxIndividuen(individuen); // Anzahl der Individuen setzen
   ga.setMaxMutationRate(MutationsRate); // Mutationsrate setzen
   ga.createPopulation(); // Population erstellen

   emit renderedImage(paint()); // Bildausgabe

   mTimer_2.start();
   mTimer.Start();
   paused = false;
   condition.wakeOne();
}

void TSP_thread::togglePause()
{
   mutex.lock();
   if(paused)
   {
      paused = false;
      condition.wakeOne();
   }
   else
   {
      paused = true;
   }
   mutex.unlock();
}

void TSP_thread::setDirection(bool direction)
{
   mutex.lock();
   this->ga.setOptimizeDirection(direction);
   mutex.unlock();
}

void TSP_thread::setMultiThreading(bool multiThreading)
{
   mutex.lock();
   if( multiThreading == true )
   {
      this->ga.enableMultithreading();
   }
   else
   {
      this->ga.disableMultithreading();
   }
   mutex.unlock();
}

void TSP_thread::setMutationRate(double mutationRate)
{
   mutex.lock();
   ga.setMaxMutationRate(mutationRate);
   mutex.unlock();
}

void TSP_thread::setPopulationSize(int individuen)
{
   mutex.lock();
   ga.setMaxIndividuen(individuen);
   mutex.unlock();
}

void TSP_thread::run()
{
   forever
   {
      mutex.lock();
      if (abort)
      {
         return;
      }
      mutex.unlock();

      mutex.lock();
      if(paused)
      {
         condition.wait(&mutex);
      }
      mutex.unlock();

      mutex.lock();
      ga.epoch();

      if( (ga.getCntGeneration()%100 == 0) && (mTimer_2.elapsed() > 500) )
      {
         mTimer_2.start();
         #if !BENCH
         emit renderedImage(paint());
         #endif
      }
      mutex.unlock();

      #if BENCH
      mutex.lock();
      if( ga.getGeneration() == 1000)
      {
         std::fstream fout("timer.csv", std::fstream::app | std::fstream::out);
         QString str;
         str.setNum(mTimer.Elapsed());
         str.replace(QString("."), QString(","));
         fout << ga.getIndividuen() << ";" << ga.getLocations() << ";" << str.toStdString() << ";\n";
         fout.close();
         paused = true;
         emit renderedImage(paint());
      }
      mutex.unlock();
      #endif

   }

}

QImage TSP_thread::paint()
{
   QVector< QVector<int> > locations = this->ga.getCoordinates();

   QVector< QVector<int> >::iterator it;

   QImage image(500, 500, QImage::Format_ARGB32_Premultiplied);
   QPainter painter(&image);
   painter.fillRect(0, 0, 500, 500, Qt::white);

   painter.setRenderHints(QPainter::Antialiasing);
   painter.setPen(Qt::black);

   painter.drawRect(0, 0, 500, 500);

   if( locations.size() > 1 )
   {
#define FOREGROUND 0
#if FOREGROUND == 0
      painter.setPen(Qt::red);
      for(it = locations.begin() ; it < locations.end() ; it++ )
      {
         //painter.drawText(it->at(0)-3, it->at(1)-5, QString::number(i++));
         //painter.drawRect(it->at(0)-3, it->at(1)-3, 8, 8);
         painter.drawEllipse( it->at(0)-2, it->at(1)-2, 4, 4);
         //painter.drawEllipse(it->at(0)-20, it->at(1)-20, 40, 40);
      }
#endif
      if( this->ga.getPopulationSize() > 1 )
      {
         QVector<int> a = this->ga.getBestGene();

         painter.setPen(Qt::black);

         for(int i = 0; i < a.size()-1; i++)
         {
            painter.drawLine( locations.at(a[i]).at(0), locations.at(a[i]).at(1), locations.at(a[i+1]).at(0), locations.at(a[i+1]).at(1) );
         }

         painter.drawLine( locations.at(a[a.size()-1]).at(0), locations.at(a[a.size()-1]).at(1), locations.at(a[0]).at(0), locations.at(a[0]).at(1) );
         painter.fillRect(1, 1, 150, 20, Qt::white);

         painter.setPen(Qt::black);

         painter.drawText(5, 15,  "Beste Route: " + QString::number(this->ga.getBestFitness())
                                 + " Generation: " + QString::number(ga.getCntGeneration()) + " "
                                 + QString::number(mTimer.Elapsed()) + " s "
                                 + "Individuen: " + QString::number(this->ga.getPopulationSize())
                         );
         painter.drawText(5, 28, "Schlechteste Route: " + QString::number(this->ga.getWorstFitness())
                          + " Durchschnitt pro Generation: " + QString::number(mTimer.Elapsed() / (ga.getCntGeneration()+1) ));
      }
#if FOREGROUND == 1
      painter.setPen(Qt::red);
      for(it = locations.begin() ; it < locations.end() ; it++ )
      {
         //painter.drawText(it->at(0)-3, it->at(1)-5, QString::number(i++));
         //painter.drawRect(it->at(0)-3, it->at(1)-3, 8, 8);
         painter.drawEllipse( it->at(0)-2, it->at(1)-2, 2, 2);
         //painter.drawEllipse(it->at(0)-20, it->at(1)-20, 40, 40);
      }
#endif
   }
#if 0
   if( ga.getGeneration()%1000 == 0 )
   {
      image.save("./output/" + QString::number(ga.getGeneration()/1000) + ".jpg");
   }
#endif
   return image;
}
