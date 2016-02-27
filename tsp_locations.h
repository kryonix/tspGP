#ifndef TSP_LOCATIONS_H
#define TSP_LOCATIONS_H

#include <QVector>
#include <vector>

#include "random.h"

namespace tsp {

   class Locations
   {
   private:
      int mMaxLocations;
      int mMaxX;
      int mMaxY;
      int mGenerationMethod;

      QVector< QVector<int> > mCoordinates;

      Random mRandom;

      void Init(int maxLocations, int maxX, int maxY, int generationMethod);
   public:
      Locations();
      Locations(int maxLocations, int maxX, int maxY, int generationMethod);

      void newRandomLocations();
      void newLocation(int x, int y);

      QVector< QVector<int> > getCoordinates();

      int getCntCoordinates()                        { return this->mCoordinates.size(); }

      void setMaxLocations(int maxLocations)         { this->mMaxLocations = maxLocations; }
      int getMaxLocations()                          { return this->mMaxLocations; }

      void deleteAllLocations()                      { this->mCoordinates.clear(); }

      void setMaxX(int maxX)                         { this->mMaxX = maxX; }
      int getMaxX()                                  { return this->mMaxX; }

      void setMaxY(int maxY)                         { this->mMaxY = maxY; }
      int getMaxY()                                  { return this->mMaxY; }

      void setGenerationMethod(int generationMethod) { this->mGenerationMethod = generationMethod; }
      int getGenerationMethod()                      { return this->mGenerationMethod; }

   };

}
#endif // LOCATIONS_H
