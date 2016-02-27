#ifndef TSP_POPULATION_H
#define TSP_POPULATION_H

#include <QDebug>
#include <QThreadPool>
#include <QVector>
#include <QtAlgorithms>

#include <vector>
#include <algorithm>

#include <sstream>
#include <fstream>

#include "tsp_individuum.h"
#include "tsp_locations.h"
#include "tsp_workerthread.h"

#include "random.h"

namespace tsp {

   class Population
   {
   private:
      bool                mOptimizeDirection;
      bool                mMultiThreading;

      int                 mMaxIndividuen;

      int                 mCntGeneration;

      double              mMaxMutationRate;


      QList<Individuum>   mIndividuen;
      Locations*          pLocations;

      double              calculatePopulationFitness(void);
      void                sortIndividuenByFitness();

      void                increaseGeneration(void)                 { this->mCntGeneration++; }

      Random mRandom;

   public:
      Population();
      Population(int, Locations*, bool);

      ~Population();

      void                epoch();
      void                insertIndividuum( Individuum );

      double              getPopulationFitness()                        { return calculatePopulationFitness(); }

      const char*         getGenes();

      double              getBestFitness();
      double              getWorstFitness();

      QVector<int>        getBestGene();

      int                 getPopulationSize()                           { return this->mIndividuen.size(); }
      void                createPopulation();

      void                setLocations(Locations* pLocations)           { this->pLocations = pLocations; }

      void                setMaxIndividuen(int maxIndividuen)           { this->mMaxIndividuen = maxIndividuen; }
      int                 getMaxIndividuen()                            { return this->mMaxIndividuen; }
      void                deleteAllIndividuen()                         { this->mIndividuen.clear(); }

      void                setGenerationToZero()                         { this->mCntGeneration = 0; }
      int                 getCntGeneration()                            { return this->mCntGeneration; }

      void                setMaxMutationRate(double maxMutationRate)    { this->mMaxMutationRate = maxMutationRate; }
      double              getMaxMutationRate()                          { return this->mMaxMutationRate; }

      void                setOptimizeDirection(bool optimizeDirection)  { this->mOptimizeDirection = optimizeDirection; }

      void                enableMultiThreading()                        { this->mMultiThreading = true; }
      void                disableMultiThreading()                       { this->mMultiThreading = false; }
   };

}

#endif // POPULATION_H
