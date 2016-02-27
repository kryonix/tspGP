#ifndef RANDOM_H
#define RANDOM_H

#include "MersenneTwister.h"

#include <QDateTime>

class Random
{
private:
   MTRand random;

public:
   Random()
      : random( QDateTime::currentMSecsSinceEpoch() + qrand() )
   {
      //random.seed( QDateTime::currentMSecsSinceEpoch() + random.randInt() );
   }

   int rnd(int lowerbounds, int upperbounds)
   {
      return lowerbounds + random.randInt(upperbounds-lowerbounds);
   }

   int rnd(int lowerbounds, int upperbounds, int best)
   {
      int zahl = lowerbounds + random.randInt(upperbounds-lowerbounds);

      if( random.rand() > static_cast<double>(best)/10 )
      {
         zahl = zahl%best;
      }

      return zahl;
   }

};

#endif // RANDOM_H
