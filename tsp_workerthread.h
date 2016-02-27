#ifndef TSP_WORKERTHREAD_H
#define TSP_WORKERTHREAD_H

#include <QRunnable>
#include <QThreadPool>
#include <QMutex>

#include <vector>
#include "tsp_individuum.h"

namespace tsp {

   class tsp_workerthread : public QRunnable
   {
   public:
      tsp_workerthread(Individuum *);

      void run(void);

   private:
      QMutex mutex;

      Individuum *A;
   };

}

#endif // TSP_WORKERTHREAD_H
