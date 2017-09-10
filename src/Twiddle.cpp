//
// Created by sven on 2017-08-17.
//

#include <iostream>
#include "Twiddle.h"
#include "PID.h"

Twiddle::Twiddle() {}

Twiddle::~Twiddle() {}

void Twiddle::Init(std::vector<double> p, std::vector<double> dp,
                   double tol, long startCounter, long endCounter){

  Twiddle::p = p;
  Twiddle::dp = dp;
  Twiddle::startCounter = startCounter;
  Twiddle::endCounter = endCounter;
  Twiddle::tol = tol;

  pid.Init(Twiddle::p[0], Twiddle::p[1], Twiddle::p[2], Twiddle::startCounter);
}

bool Twiddle::resetSimulation() {
  if(!initialRestart){
    initialRestart = true;
    return true;
  }
  if(pid.counter > endCounter){
    updatePID();
    return true;
  }
  return false;
}

void Twiddle::updatePID(){
  cout << "P: " << p[0] << " - I: " << p[1] << " - D: " << p[2] << endl;
  cout << "Index: " << index << " - factor: " << factor << endl;
  cout << "dP: " << dp[0] << " - dI: " << dp[1] << " - dD: " << dp[2] << endl;
  cout << "TotalError: " << pid.squareError << " - bestError: " << smallestError << endl;
  cout << "Best so far - P: " << bestP[0] << " - I: " << bestP[1] << " - D: " << bestP[2] << endl;

  if(dp[0] + dp[1] + dp[2] < tol){
    //Twiddle complete, rerun simulation
    cout << "Tolerance reached, rerunning best values" << endl;
    p[0] = bestP[0];
    p[1] = bestP[1];
    p[2] = bestP[2];
  }else{
    if(pid.squareError < smallestError){
      dp[index] *= 1.1;
      smallestError = pid.squareError;
      bestP[0] = p[0];
      bestP[1] = p[1];
      bestP[2] = p[2];

      factor = 1;
      index++;
      index %= 3;
    }else{
      if(factor == 1){
        factor = -2;
      }else{
        //Resetting to 'middle'
        p[index] += dp[index];
        dp[index] *= 0.9;

        index++;
        index %= 3;
        factor = 1;
      }
    }

    p[index] += factor * dp[index];


  }
  pid.Init(Twiddle::p[0], Twiddle::p[1], Twiddle::p[2], Twiddle::startCounter);
}

double Twiddle::updateSteering(double cte) {
  return pid.UpdateSteering(cte);
}
