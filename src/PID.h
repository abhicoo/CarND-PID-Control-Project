#ifndef PID_H
#define PID_H
#include "Twiddle.h"
#include<cmath>
#include <vector>
#include<iostream>

class PID {
public:
  /*
  * Errors
  */
  double p_error = 0;
  double i_error = 0;
  double d_error = 0;
  double total_error = 0;

  /*
  * Coefficients
  */ 
  double Kp;
  double Kd;
  double Ki;
 
  std::vector<double> dp;
  Twiddle twiddle;
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Kd, double Ki);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
};

#endif /* PID_H */
