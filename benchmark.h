#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <QString>
#include <QFile>
#include <QTextStream>

#include "timer.h"
#include <string>
#include <fstream>
#include <sstream>

class Benchmark
{
private:
   Timer mTimer;
   QString mTimerName;
   Benchmark();

public:
   Benchmark(QString timername);
   ~Benchmark();

   void write();
   void write(Timer* mTimer);

};

#endif // BENCHMARK_H
