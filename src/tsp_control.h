#ifndef TSP_CONTROLL_H
#define TSP_CONTROLL_H

#include <QVector>

#include "tsp_locations.h"
#include "tsp_population.h"

namespace tsp {

   class Control
   {
   public:
      Control();

      void setMaxLocations(int maxLocations)             { this->mLocations.setMaxLocations(maxLocations); }
      int  getMaxLocations()                             { return this->mLocations.getMaxLocations(); }

      int  getCntCoordinates()                           { return this->mLocations.getCntCoordinates(); }
      void deleteAllLocations()                          { this->mLocations.deleteAllLocations(); }

      void setMaxX(int MaxX)                             { this->mLocations.setMaxX(MaxX); }
      int  getMaxX()                                     { return this->mLocations.getMaxX(); }

      void setMaxY(int MaxY)                             { this->mLocations.setMaxY(MaxY); }
      int  getMaxY()                                     { return this->mLocations.getMaxY(); }

      void setGenerationMethod(int generationMethod)     { this->mLocations.setGenerationMethod(generationMethod); }
      int  getGenerationMethod()                         { return this->mLocations.getGenerationMethod(); }

      void newRandomLocations()                          { this->mLocations.newRandomLocations(); }
      void newLocation(int x, int y)                     { this->mLocations.newLocation(x, y); }



      void setMaxIndividuen(int maxIndividuen)           { this->mPopulation.setMaxIndividuen(maxIndividuen); }
      int  getMaxIndividuen()                            { return this->mPopulation.getMaxIndividuen(); }
      void clearIndividuen()                             { this->mPopulation.deleteAllIndividuen(); }

      void epoch()                                       { this->mPopulation.epoch(); }

      int  getPopulationSize()                           { return this->mPopulation.getPopulationSize(); }
      void createPopulation()                            { this->mPopulation.createPopulation(); }

      int  getCntGeneration()                            { return this->mPopulation.getCntGeneration(); }

      void setMaxMutationRate(double maxMutationRate)    { this->mPopulation.setMaxMutationRate(maxMutationRate); }

      double getBestFitness()                            { return this->mPopulation.getBestFitness(); }
      double getWorstFitness()                           { return this->mPopulation.getWorstFitness(); }

      void enableMultithreading()                        { this->mPopulation.enableMultiThreading(); }
      void disableMultithreading()                       { this->mPopulation.disableMultiThreading(); }

      void setOptimizeDirection(bool optimizeDirection)  { this->mPopulation.setOptimizeDirection(optimizeDirection); }

      QVector< QVector<int> > getCoordinates()           { return this->mLocations.getCoordinates(); }
      QVector< int > getBestGene()                       { return this->mPopulation.getBestGene(); }

   private:
      Locations   mLocations;
      Population  mPopulation;

   };

}
#endif // CONTROLL_H
