#include "vehicle.h"

Vehicle::Vehicle() : id(-1) {
    for (int i = 0; i < 2; i++) {
        this->x_state[i] = 0.0;
        this->y_state[i] = 0.0;
    }

    for (int i = 0; i < 3; i++) {
        this->s_state[i] = 0.0;
        this->d_state[i] = 0.0;
    }
}

Vehicle::Vehicle(int id, const double (&x)[2], const double (&y)[2], double s, double d) : id(id) {
    for (int i = 0; i < 2; i++) {
        this->x_state[i] = x[i];
        this->y_state[i] = y[i];
    }

    for (int i = 0; i < 3; i++) {
        this->s_state[i] = 0.0;
        this->d_state[i] = 0.0;
    }
    this->s_state[0] = s;
    this->d_state[0] = d;
}


Vehicle::Vehicle(int id, const double (&x)[2],
    const double (&y)[2], const double (&s)[3], const double (&d)[3]) : id(id) {
    for (int i = 0; i < 2; i++) {
        this->x_state[i] = x[i];
        this->y_state[i] = y[i];
    }

    for (int i = 0; i < 3; i++) {
        this->s_state[i] = s[i];
        this->d_state[i] = d[i];
    }
}

// Vehicle::~Vehicle() {}


// Estimate new s and d states from current states using following formula:
//   x_t = x_{t-1} + v_{t-1} * t + 1/2 * a_{t-1} * t^2
//   v_t = v_{t-1} + a_{t-1} * t
//   a_t = a_{t-1}
vector<double> Vehicle::PredictSDStateAt(double t) {
    return {
        this->s_state[0] + (this->s_state[1] * t) + this->s_state[2] * t * t / 2.0,
        this->s_state[1] + this->s_state[2] * t,
        this->s_state[2],
        this->d_state[0] + (this->d_state[1] * t) + this->d_state[2] * t * t / 2.0,
        this->d_state[1] + this->d_state[2] * t,
        this->d_state[2]
    };
}

// Update x, y, s, d states
void Vehicle::UpdateState(const double (&x)[2], const double (&y)[2], double s, double d) {
    // Just copy for x, vx, y, vy
    for (int i = 0; i < 2; i++) {
        this->x_state[i] = x[i];
        this->y_state[i] = y[i];
    }

    // Update s and d
    double old_vs = this->s_state[1];
    this->s_state[1] = s - this->s_state[0];
    this->s_state[2] = this->s_state[1] - old_vs;
    this->s_state[0] = s;

    double old_vd = this->d_state[1];
    this->d_state[1] = d - this->d_state[0];
    this->d_state[2] = this->d_state[1] - old_vd;
    this->d_state[0] = d;
}
