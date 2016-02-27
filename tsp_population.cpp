#include "tsp_population.h"

#define GENERATESECONDINDIVIDUUM 0
namespace tsp {

   Population::Population()
   {
      this->mOptimizeDirection = false;
      this->mMultiThreading = false;
   }

   Population::Population(int individuen, Locations* pLocations, bool multiThreading = false)
   {
      this->mOptimizeDirection = false;
      this->mMaxIndividuen = individuen;
      this->pLocations = pLocations;
      this->mMultiThreading = multiThreading;

      createPopulation();
   }

   Population::~Population(void)
   {
   }

   void Population::createPopulation()
   {
      this->deleteAllIndividuen();
      this->setGenerationToZero();

      for(int i = 0 ; i < this->getMaxIndividuen() ; i++)
      {
         bool twice = false;
         Individuum b( this->pLocations, this->mMaxMutationRate );

         do
         {
            twice = false;
            b.newRandomGene();

            if( this->mIndividuen.size() > 1 )
            {
               for(int j = 0; j < this->mIndividuen.size(); j++)
               {
                  if( mIndividuen[j].getFitness() == b.getFitness())
                  {
                     twice = true;
                     break;
                  }
               }
            }
         } while( twice == true );

         this->mIndividuen.push_back( b );
      }
   }

   void Population::epoch(void)
   {
   // [1] n-viele Zufällige Individuen Auswählen und Rekombinieren.
   // [2] Sortieren nach Fitness.
   // [3] Surviving of the best

      bool multiThreading = this->mMultiThreading;

      #if 1
      if( this->mCntGeneration%100 == 0 )
      {
         for(int i = 0; i < this->mMaxIndividuen; i++)
         {
            mIndividuen.push_back(Individuum(this->pLocations, this->mMaxMutationRate));
         }
      }
      #endif

      QList<Individuum> a = this->mIndividuen;

      int x;
      int y;

      int anzahl = this->mMaxIndividuen;
      int aSize = a.size()-1;

      for(int i = 0; i < anzahl; i++) //[1]
      {
         x = mRandom.rnd(0, aSize); //, this->mIndividuen/10);
         do
         {
            y = mRandom.rnd(0, aSize); //, this->mIndividuen/10);
         } while( x == y );

         if( multiThreading == false )
         {
            this->mIndividuen.push_back( Individuum( a[x], a[y], this->pLocations, this->mMaxMutationRate ) );

            #if GENERATESECONDINDIVIDUUM == 1
            this->mIndividuen.push_back( Individuum( a[y], a[x], this->pLocations, this->mMaxMutationRate ) );
            #endif
         }
         else
         {
            QVector<int> randPool;
            #if 0
            randPool.push_back(mRandom.rnd(0, 100));
            randPool.push_back(mRandom.rnd(0, 100));
            randPool.push_back(mRandom.rnd(0, 100));
            randPool.push_back(mRandom.rnd(0, 100));

            int loc1 = mRandom.rnd(0, this->pLocations->getLocations()-1);
            int loc2 = 0;
            do
            {
               loc2 = mRandom.rnd(0, this->pLocations->getLocations()-1);
            } while( loc1 == loc2 );

            randPool.push_back(loc1);
            randPool.push_back(loc2);
            #endif

            Individuum b(this->pLocations, this->mMaxMutationRate, a[x].getGene(), a[y].getGene(), randPool);

            this->mIndividuen.push_back( b );

            #if GENERATESECONDINDIVIDUUM == 1
            Individuum c(this->pLocations, this->mMaxMutationRate, a[y].getGene(), a[x].getGene(), randPool);
            this->mIndividuen.push_back( c );
            #endif
         }
      }

      if( multiThreading == true )
      {
         QVector<tsp_workerthread *> threads;

         for(int i = a.size(); i < mIndividuen.size(); i++)
         {
            threads.push_back(new tsp_workerthread(&this->mIndividuen[i]));
         }

         QThreadPool::globalInstance()->setMaxThreadCount(100);

         int i = 0;
         while( i < threads.size() )
         {
            if( QThreadPool::globalInstance()->tryStart(threads.at(i)) == true )
            {
               i++;
            }
         }

         QThreadPool::globalInstance()->waitForDone();
      }

      this->sortIndividuenByFitness(); //[2]

      #define HOLDINDIVIDUEN 0

      #if HOLDINDIVIDUEN == 1
      if( this->mCntGeneration%100 == 0 )
      {
      #endif
         while( this->mIndividuen.size() > this->mMaxIndividuen )
         {
            this->mIndividuen.pop_back();
         }
      #if HOLDINDIVIDUEN == 1
      }
      #endif
      this->increaseGeneration();
   }

   double Population::calculatePopulationFitness()
   {
      double fitness = 0;
      QList< Individuum >::iterator it;

      for(it = mIndividuen.begin() ; it < mIndividuen.end() ; it++)
      {
         it->setLocations(this->pLocations);
         fitness += it->getFitness();
      }

      return fitness;
   }

   void Population::insertIndividuum( Individuum a )
   {
      this->mIndividuen.push_back(a);
   }

   const char* Population::getGenes(void)
   {
      std::ostringstream str;
      QList< Individuum >::iterator it;

      for(it = mIndividuen.begin() ; it < mIndividuen.end() ; it++)
      {
         for(int i = 0 ; i <= this->pLocations->getMaxLocations() ; i++)
         {
            str << it->getGene(i) << " ";
         }
         str << "Fitness: " << it->getFitness() << "\n";
      }
      str << "Fitness Population: " << getPopulationFitness() << "\n";

      return str.str().c_str();
   }

   double Population::getBestFitness()
   {
      return mIndividuen.begin()->getFitness();
   }

   double Population::getWorstFitness()
   {
      return (mIndividuen.end()-1)->getFitness();
   }

   QVector<int> Population::getBestGene()
   {
      return mIndividuen.begin()->getGene();
   }

   void Population::sortIndividuenByFitness()
   {
      if(!mOptimizeDirection)
      {
         //std::sort(mIndividuen.begin(), mIndividuen.end(), Individuum::compareFitness);
         qSort(mIndividuen.begin(), mIndividuen.end(), Individuum::compareFitness);
      }
      else
      {
         //std::sort(mIndividuen.begin(), mIndividuen.end(), Individuum::compareFitnessLower);
         qSort(mIndividuen.begin(), mIndividuen.end(), Individuum::compareFitnessLower);
      }
   }

}
