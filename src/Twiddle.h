#ifndef TWIDDLE_H
#define TWIDDLE_H
#include <vector>
#include <numeric>
#include<iostream>

class Twiddle {
private:
    int step = 1;
    int current_param = 0;
    int current_state = 0;
    double error = 0;
    double best_error = 1e9;

public:
    Twiddle();

    virtual ~Twiddle();

    void Init();

    void Update(std::vector<double> &params, std::vector<double> &dp, const double cte);

    int CurrentStep();
};

#endif