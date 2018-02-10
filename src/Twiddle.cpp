#include "Twiddle.h"
#include <cmath>
#define MIN_NUMBER_STEPS 100

using namespace std;

Twiddle::Twiddle() {}

Twiddle::~Twiddle() {}

void Twiddle::Init() {}

void Twiddle::Update(std::vector<double> &params, std::vector<double> &dp, const double cte) {

    //Accumulate error    
    if(step > MIN_NUMBER_STEPS && step <  2 * MIN_NUMBER_STEPS) {
        error += pow(cte, 2);
        step++;
        if(step == 2 * MIN_NUMBER_STEPS) {
            error /= MIN_NUMBER_STEPS;
        }
        return;
    }else if(step <= MIN_NUMBER_STEPS) {
        step++;
        return;
    }
    
    // Set best error if not set
    if(best_error > 1e8) {
        best_error = error;
        step = 0;
        error = 0;
        return;
    }

    // Update params on basis of error
    switch(current_state) {
        case 0:
            params[current_param] += dp[current_param];
            current_state = 1;
            break;
        case 1:
            if(fabs(error) < fabs(best_error)) {
                best_error = error;
                dp[current_param] *= 1.1;
                current_state = 3;
            } else {
                params[current_param] -= 2 * dp[current_param];
                step = 0;
                error = 0;
                current_state = 2;
            }
            break;
        case 2:
            if (fabs(error) < fabs(best_error)) {
                best_error = error;
                dp[current_param] *= 1.1;
            } else {
                params[current_param] += dp[current_param];
                dp[current_param] *= 0.9;
            }
            current_state = 3;
            break;
        case 3:
            cout << "Value after optimization " << "\n";
            cout << "Kp " << params[0] << "\n";
            cout << "Kd " << params[1] << "\n";
            cout << "Ki " << params[2] << "\n";
            cout << "\n";
            cout << "\n";
            current_param = (current_param + 1) % dp.size();
            step = 0;
            error = 0;
            current_state = 0;
            break;
    }
}

int Twiddle::CurrentStep() {
    return step;
}