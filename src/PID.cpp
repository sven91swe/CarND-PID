#include <cmath>
#include <iostream>
#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd, long startCounter) {
  PID::Kp = Kp;
  PID::Ki = Ki;
  PID::Kd = Kd;

  p_error = 0;
  i_error = 0;
  d_error = 0;

  squareError = 0;

  previousInput = 0;
  counter = 0;
  PID::startCounter = startCounter;

}

double PID::UpdateSteering(double cte) {
  UpdateError(cte);

  return - Kp * p_error - Kd * d_error - Ki * i_error;
}

void PID::UpdateError(double cte) {
  p_error = cte;

  d_error = cte - previousInput;
  previousInput = cte;

  i_error += cte;

  counter++;

  if(counter >= startCounter){
    squareError += pow(cte, 2);
  }
}

double PID::TotalError() {
}

