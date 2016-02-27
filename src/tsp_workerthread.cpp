#include "tsp_workerthread.h"
#include <QDebug>

namespace tsp {

   tsp_workerthread::tsp_workerthread(Individuum *a)
      : A(a)
   {}

   void tsp_workerthread::run()
   {
      //qDebug() << "Hello world from thread" << QThread::currentThread();
      A->recombineGene();
   }

}
