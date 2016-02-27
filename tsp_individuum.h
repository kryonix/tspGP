#ifndef TSP_INDIVIDUUM_H
#define TSP_INDIVIDUUM_H

#include <QDebug>

#include <QVector>
#include <QtAlgorithms>
#include <algorithm>
#include <cmath>

#include "random.h"
#include "timer.h"

#include "tsp_locations.h"

namespace tsp {

   class Individuum
   {
   private:
      Locations*          pLocations;
      QVector<int>        mGene;
      int                 mAge;

      double              mFitness;
      double              mMutationsRate;

      double              calculateFitness();

      void                recombineGene(QVector<int>, QVector<int>);
      void                recombineGeneB(QVector<int>, QVector<int>);

      QVector<int> mA;
      QVector<int> mB;
      QVector<int> randPool;

      Random mRandom;

   public:
      Individuum() {}
      Individuum(Locations* pLocations, double MutationsRate, QVector<int> a, QVector<int> b, QVector<int> randPool);
      Individuum(Locations* pLocations, double MutationsRate);
      Individuum(QVector<int> gene);
      Individuum(Individuum& a, Individuum& b, Locations* pLocations, double MutationsRate);
      Individuum(QVector<int> a, QVector<int> b, Locations* pLocations, double MutationsRate);
      ~Individuum();

      QVector<int> getGene();
      int          getGene(int);
      void         setGene(QVector<int>&);

      double       getFitness()                                     { return this->mFitness; }
      void         setLocations(Locations *pLocations)              { this->pLocations = pLocations; }
      Locations*   getLocations()                                   { return this->pLocations; }

      static bool compareFitness(Individuum& a, Individuum& b)      { return a.getFitness() < b.getFitness(); }
      static bool compareFitnessLower(Individuum& a, Individuum& b) { return a.getFitness() > b.getFitness(); }

      bool operator< (Individuum& b)                                { return this->getFitness() < b.getFitness(); }
      bool operator== (Individuum& b)
      {
         /*for(int i = 0; i < this->mGene.size(); i++)
         {
            if( this->mGene[i] != b.getGene(i) )
            {
               return false;
            }
         }
         return true;*/
         return this->getFitness() == b.getFitness();
      }

      void recombineGene() { recombineGene(mA, mB); }

      void newRandomGene();

      void increaseAge() { this->mAge++; }
      int getAge()       { return this->mAge; }
   };

}
#endif //INDIVIDUUM_H
