#include "tsp_individuum.h"

namespace tsp {

   Individuum::Individuum(Locations* pLocations, double MutationsRate, QVector<int> a, QVector<int> b, QVector<int> randpool)
      : pLocations(pLocations), mAge(0), mMutationsRate(MutationsRate), mA(a), mB(b), randPool(randpool)
   {}

   Individuum::Individuum(Locations* pLocations, double MutationsRate)
      : pLocations(pLocations), mAge(0), mMutationsRate(MutationsRate)
   {
      QVector<int> waypoints; // Kontrollvector um sicher zu gehen, dass alle Wegpunkte im Genom übernommen werden

      // Befüllen des Vectors mit den Wegpunkte nummern von 0 bis n.
      // Dies stellt sicher, dass alle Wegpunkte im Genom vorhanden sind.
      for(int i = 0 ; i < pLocations->getMaxLocations() ; i++)
      {
         waypoints.push_back(i);
      }

      this->mGene.fill(0, pLocations->getMaxLocations());

      // Es wird Zufällig eine Position ausgewählt, diese wird an der i-ten
      // stelle im Genom eingefügt und im nächsten Schritt gelöscht.
      for(int i = 0, position = 0 ; i < pLocations->getMaxLocations() ; i++)
      {
         position = mRandom.rnd(0, waypoints.size()-1);
         this->mGene[i] = waypoints[position];
         waypoints.erase(waypoints.begin()+position);
      }

      this->mFitness = this->calculateFitness();
   }

   void Individuum::newRandomGene()
   {
      int locations = pLocations->getMaxLocations();

      mGene.clear();

      for(int i = 0; i < locations; i++)
      {
         mGene.push_back(i);
      }

      std::random_shuffle(mGene.begin(), mGene.end());

      this->mFitness = this->calculateFitness();
   }

   Individuum::Individuum(QVector<int> gene)
   {
      this->mAge = 0;
      setGene(gene);
   }

   Individuum::Individuum(Individuum& a, Individuum& b, Locations* pLocations, double MutationsRate)
      : pLocations(pLocations), mAge(0), mMutationsRate(MutationsRate)
   {
      recombineGene(a.getGene(), b.getGene());
   }

   Individuum::Individuum(QVector<int> a, QVector<int> b, Locations* pLocations, double MutationsRate)
      : pLocations(pLocations), mAge(0), mMutationsRate(MutationsRate)
   {
      recombineGene(a, b);
   }

   Individuum::~Individuum(void)
   {}

   QVector<int> Individuum::getGene(void)
   {
      return this->mGene;
   }

   int Individuum::getGene(int i) {
      return this->mGene[i];
   }

   void Individuum::setGene(QVector<int>& gene)
   {
      this->mGene.clear();
      this->mGene += gene;
      this->mFitness = this->calculateFitness();
   }

   void Individuum::recombineGeneB(QVector<int> a, QVector<int> b)
   {
      if( a.size() == b.size() )
      {
         /*
          * Vector des Neuen Genoms wird erstellt, ausreichend Speicherplatz reserviert.
          * Im nächsten Schritt wird er befüllt mit n -1-en.
          */

         int locations = this->pLocations->getMaxLocations();

         QVector<int> gene;
         gene.reserve( locations );
         gene.fill(-1, a.size());

         /*
            * Cycle Crossover Rekombinations Methode.
            * Genom a: 9 8 2 1 7 4 5 10 6 3
            * Genom b: 1 2 3 4 5 6 7 8  9 10
            * [1] Von links nach rechts in Genom a Wert aussuchen. => 9
            * [2] Unter der 9 steht die 1, und die 1 steht an Stelle 4 in Genom a.
            * Unter der 1 steht die 6, unter der 6 die 9.
            * Würde die 9 übertragen in das Kindgenom, würde dies zu einem Kurzzyklus führen,
            * [3] daher werden die Restlichen positionen einfach von b übernommen.
            */

         for(int i = 0, position = 0, value = 0; i < locations; i++)
         {
            value = b[position];
            qSwap(a[position], b[position]);

            for(int j = 0; j < locations; j++)
            {
               if(b[j] == value)
               {
                  position = j;
                  break;
               }
            }
         }
         gene = a;

         /*
          * Spiegelung Mutation Methode.
          * [1] Auswahl eines Bereiches des Genoms
          * [2] In Hilfsvector schreiben
          * [3] Übrige Stellen löschen
          * [4] Genom zusammenfügen
          */

         if(this->randPool[0] <= this->mMutationsRate)
         {
            int start = this->randPool[4];
            int end = this->randPool[5];

            std::reverse(gene.begin()+start, gene.begin()+end);
         }

         /*
          * Rotation Mutation Methode.
          * [1] Auswahl eines Bereiches des Genoms
          * [2] In Hilfsvector schreiben
          * [3] Übrige Stellen löschen
          * [4] Genom zusammenfügen
          */

         if(this->randPool[1] <= this->mMutationsRate)
         {
            int start = this->randPool[4];
            int end = this->randPool[5];

            std::rotate(gene.begin()+start, gene.begin()+end, gene.begin()+end);
         }

         if(this->randPool[2] <= this->mMutationsRate )
         {
            int x = this->randPool[4];
            int y = this->randPool[5];

            qSwap(gene[x], gene[y]);
         }

         if(this->randPool.at(3) <= this->mMutationsRate )
         {
            int x = this->randPool[4];
            int y = this->randPool[5];

            if(x > y)
            {
               std::swap( x, y );
            }
            std::random_shuffle(gene.begin()+x, gene.begin()+y);
         }

         setGene(gene);
      }
   }

   void Individuum::recombineGene(QVector<int> a, QVector<int> b)
   {
      if( a.size() == b.size() )
      {
         // Vector des Neuen Genoms wird erstellt, ausreichend Speicherplatz reserviert.
         // Im nächsten Schritt wird er befüllt mit n -1-en.
         QVector<int> gene;

         int locations = this->pLocations->getMaxLocations();

         if( !a.operator ==(b) )
         {
            gene.reserve( locations );
            gene.fill(-1, a.size());

         // Cycle Crossover Rekombinations Methode.
         // Genom a: 9 8 2 1 7 4 5 10 6 3
         // Genom b: 1 2 3 4 5 6 7 8  9 10
         // [1] Von links nach rechts in Genom a Wert aussuchen. => 9
         // [2] Unter der 9 steht die 1, und die 1 steht an Stelle 4 in Genom a.
         // Unter der 1 steht die 6, unter der 6 die 9.
         // Würde die 9 übertragen in das Kindgenom, würde dies zu einem Kurzzyklus führen,
         // [3] daher werden die Restlichen positionen einfach von b übernommen.

            for(int i = 0, position = 0, value = 0; i < locations; i++)
            {
               value = b[position];

               gene[position] = value;

               for(int j = 0; j < locations; j++)
               {
                  if(b[j] == value)
                  {
                     position = j;
                     break;
                  }
               }
            }
         }
         else
         {
            gene = a;
         }

         for(int i = 0; i < locations; i++)
         {
            if( gene[i] == -1 )
            {
               gene[i] = b[i];
            }
         }

         if( mRandom.rnd(1, 100) <= this->mMutationsRate )
         {
            int method = mRandom.rnd(0, 1);

            if(method == 0)
            {
               int start = mRandom.rnd(0, locations-1);
               int end = 0;
               do
               {
                  end = mRandom.rnd(0, locations-1);
               } while( start == end );

               std::reverse(gene.begin()+start, gene.begin()+end);
            } else
/*
            if(method == 1)
            {
               int start = mRandom.rnd(0, locations-1);
               int end = 0;
               do {
                  end = mRandom.rnd(0, locations-1);
               } while( start == end );

               std::rotate(gene.begin()+start, gene.begin()+end, gene.begin()+end);
            }
*/
            if(method == 1)
            {
               int x = mRandom.rnd(0, gene.size()-1);
               int y = 0;
               do {
                  y = mRandom.rnd(0, gene.size()-1);
               } while ( (x == y) );

               std::swap(gene[x], gene[y]);
            }
            else if(method == 3)
            {
               int x = mRandom.rnd(0, gene.size()-1);
               int y = 0;
               do
               {
                  y = mRandom.rnd(0, gene.size()-1);
               } while( x == y );

               if( x > y )
               {
                  std::swap( x, y );
               }
               std::random_shuffle( gene.begin()+x, gene.begin()+y);
            }
            else if(method == 4)
            {
               int anzahl = mRandom.rnd(1, gene.size()-1);

               for(int i = 0; i < anzahl; i++)
               {
                  int x = mRandom.rnd(0, gene.size()-1);
                  int y = 0;
                  do
                  {
                     y = mRandom.rnd(0, gene.size()-1);
                  } while( x == y );

                  std::swap( gene[x], gene[y] );
               }
            }
            else if(method == 5) // EXPERIMENTELL!!!
            {
               //int position = mRandom.rnd(0, gene.size()-1);

               for(int i = 0; i < 5; i++)
               {
                  int position = mRandom.rnd(0, gene.size()-1);

                  for(int j = 0; j < gene.size()-1; j++)
                  {
                     setGene(gene);
                     double fitness = calculateFitness();

                     if(position != j)
                     {
                        std::swap( mGene[position], mGene[j] );
                        double newFitness = calculateFitness();

                        if( fitness > newFitness )
                        {
                           std::swap( gene[position], gene[j] );
                        }
                     }
                  }
               }
            }
         }

         setGene(gene);
      }
   }

   double Individuum::calculateFitness()
   {
   // Hier wird die Länge der Route und damit die Fitness des Individuums berechnet
   // und abgespeichert.
      QVector< QVector<int> > positions = this->pLocations->getCoordinates();

      double fitness = 0.0;

      if( mGene.size() > 0 )
      {
         int geneSize = this->mGene.size()-1;
         for(int i = 0 ; i < geneSize ; i++)
         {
            fitness += ( pow(positions.at(this->mGene.at(i) ).at(0) - positions.at( this->mGene.at(i+1)).at(0), 2.0) +
                         pow(positions.at(this->mGene.at(i) ).at(1) - positions.at( this->mGene.at(i+1)).at(1), 2.0) );
         } // Vektorbetrag berechnen und zu fitness Addieren

         fitness += ( pow(positions.at(this->mGene.at(geneSize) ).at(0) - positions.at( this->mGene.at(0)).at(0), 2.0) +
                      pow(positions.at(this->mGene.at(geneSize) ).at(1) - positions.at( this->mGene.at(0)).at(1), 2.0) );
      }

      return fitness;
   }

}
