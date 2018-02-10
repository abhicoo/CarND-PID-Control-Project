#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Kd, double Ki) {
    PID::Kp = Kp;
    PID::Ki = Ki;
    PID::Kd = Kd;
    p_error = d_error = i_error = 0.0;
    dp.push_back(0.1*Kp);
    dp.push_back(0.1*Kd);
    dp.push_back(0.1*Ki);
}

void PID::UpdateError(double cte) {
    if(twiddle.CurrentStep() == 1) p_error = cte;

    d_error = cte - p_error;
	p_error = cte;
	i_error += cte;

    std::vector<double> params;
    params.push_back(Kp);
    params.push_back(Kd);
    params.push_back(Ki);

    twiddle.Update(params, dp, cte);

    Kp = params[0];
    Kd = params[1];
    Ki = params[2];
}

double PID::TotalError() {
    return -(Kp * p_error) - (Kd * d_error) - (Ki * i_error);
}

