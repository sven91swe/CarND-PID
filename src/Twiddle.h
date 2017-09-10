//
// Created by sven on 2017-08-17.
//

#ifndef PID_TWIDDLE_H
#define PID_TWIDDLE_H

#include <vector>
#include <cmath>
#include "PID.h"


using namespace std;

class Twiddle{
  std::vector<double> p;
  std::vector<double> dp;
  std::vector<double> bestP = {0, 0, 0};

  bool initialRestart = false;
  PID pid;
  long endCounter;
  long startCounter;
  double tol;
  double smallestError = pow(10, 9);

  int factor = -2;
  int index = 2;



  void updatePID();

public:
    Twiddle();

    ~Twiddle();

    void Init(std::vector<double> p, std::vector<double> dp, double tol, long startCounter, long endCounter);

    bool resetSimulation();

    double updateSteering(double cte);
};

#endif //PID_TWIDDLE_H
