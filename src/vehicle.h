#ifndef SRC_VEHICLE_H_
#define SRC_VEHICLE_H_

#include <vector>
#include <cmath>

using std::vector;

class Vehicle {
 private:
    static const int LANE_WIDTH = 4;  // TODO(zuqqhi2): this will be input by caller

 public:
    int id;  // Vehicle unique ID
    double x_state[2];  // x, vx
    double y_state[2];  // y, vy
    double s_state[3];  // s, vs, as
    double d_state[3];  // d, vd, ad
    int lane_id;
    double speed;

    Vehicle();
    Vehicle(int id, const double (&x)[2],
        const double (&y)[2], double s, double d);
    Vehicle(int id, const double (&x)[2],
        const double (&y)[2], const double (&s)[3], const double (&d)[3]);
    virtual ~Vehicle() {}

    // Estimate future(at given t) s_state and d_state from current states
    vector<double> PredictSDStateAt(const double t);
    // Estimate future(at given t) s-axis position
    double PredictSPosAt(const double t);

    // Update x, y, s, d states
    // The censor cannot get vs, vd, as, ad
    void UpdateState(const double (&x)[2], const double (&y)[2], double s, double d);
};

#endif  // SRC_VEHICLE_H_
