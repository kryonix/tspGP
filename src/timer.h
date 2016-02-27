#ifndef TIMER_H
#define TIMER_H

#include <QTime>

class Timer
{
private:
   QTime Time;

public:
   void Start()
   {
      Time.start();
   }

   double Elapsed()
   {
      return static_cast<double>(Time.elapsed()/1000.0);
   }

};

#endif // TIMER_H
