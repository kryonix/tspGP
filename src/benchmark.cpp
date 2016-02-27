#include "benchmark.h"

Benchmark::Benchmark()
{
   this->mTimerName = "";
   this->mTimer.Start();
}

Benchmark::Benchmark(QString timername)
{
   this->mTimerName = timername;
   mTimer.Start();
}

void Benchmark::write()
{
   QString TimeElapsed;

   TimeElapsed.number(mTimer.Elapsed());

   TimeElapsed.replace( ".", "," );

   QFile file( "benchmark-" + mTimerName + ".csv" );
   file.open( QFile::Append | QFile::WriteOnly );

   QTextStream TextStream(&file);

   TextStream << TimeElapsed << "\n";

   file.close();
}

void Benchmark::write(Timer* mTimer)
{
   QString TimeElapsed;

   TimeElapsed = QString::number(mTimer->Elapsed());

   TimeElapsed.replace( ".", "," );

   QFile file( "benchmark-" + mTimerName + ".csv" );
   file.open( QFile::Append | QFile::WriteOnly );

   QTextStream TextStream(&file);

   TextStream << TimeElapsed << "\n";

   file.close();
}

Benchmark::~Benchmark()
{
}
