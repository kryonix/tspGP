#include "tsp_locations.h"
#include "random.h"
#include <cmath>

namespace tsp {

   Locations::Locations()
   {
      Init(0, 500, 500, 0);
   }

   Locations::Locations(int maxLocations, int maxX = 500, int maxY = 500, int generationMethod = 0)
   {
      Init(maxLocations, maxX, maxY, generationMethod);
      this->newRandomLocations();
   }

   void Locations::Init(int maxLocations, int maxX, int maxY, int generationMethod = 0)
   {
      this->mMaxLocations = maxLocations;
      this->mMaxX = maxX;
      this->mMaxY = maxY;
      this->mGenerationMethod = 0;
   }

   void Locations::newRandomLocations()
   {
      // Zufällige Positionen Berechnen und neuen Punkt eintragen

      if( this->mGenerationMethod == 0 )
      {
         for(int i = 0 ; i < this->mMaxLocations ; i++)
         {
            int x = mRandom.rnd(50, this->mMaxX-50);
            int y = mRandom.rnd(50, this->mMaxY-50);

            if( this->mCoordinates.size() > 2 )
            {
               bool ok = true;
               int trys = 50;
               do
               {
                  x = mRandom.rnd(50, this->mMaxX-50);
                  y = mRandom.rnd(50, this->mMaxY-50);
                  ok = true;
                  for(int j = 0; j < this->mCoordinates.size(); j++)
                  {
                     if( (this->mCoordinates.at(j).at(0) >= x-5 && this->mCoordinates.at(j).at(0) <= x+5)
                        && (this->mCoordinates.at(j).at(1) >= y-5 && this->mCoordinates.at(j).at(1) <= y+5) )
                     {
                        ok = false;
                        trys--;
                        break;
                     }
                  }
               } while( ok == false && trys > 0);
            }

            this->newLocation( x, y );
         }
      }

      if( this->mGenerationMethod == 1)
      {
         int x = 0;
         int y = 0;

         for(int i = 0 ; i < this->mMaxLocations ; i++)
         {
            x = 250+(200) * sin(i/10.0);
            y = 250+(200) * cos(i/10.0);

            this->newLocation(x, y);
         }
      }

      if( this->mGenerationMethod == 2 )
      {
         int x = 10;
         int y = 50;
         for(int i = 0 ; i < this->mMaxLocations ; i++)
         {
            this->newLocation( x, y );
            y += 10;

            if( y > mMaxY-10 )
            {
               x += 10;
               y = 50;
            }
         }
      }

   }

   void Locations::newLocation(int x, int y)
   {
      QVector<int> location;
      location.push_back(x);
      location.push_back(y);
      this->mCoordinates.push_back(location);
   }

   QVector< QVector<int> > Locations::getCoordinates()
   {
      return this->mCoordinates;
   }

}
