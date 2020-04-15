#ifndef PATH_PLANNER_H
#define PATH_PLANNER_H

#include <vector>
#include "Eigen-3.3/Eigen/Core"
#include "Eigen-3.3/Eigen/QR"

using std::vector;
using Eigen::MatrixXd;
using Eigen::VectorXd;

struct Vehicle {
    int id;
    double x;
    double y;
    double vx;
    double vy;
    double s;
    double d;
    double vs;
    double vd;
    double as;
    double ad;
};

class PathPlanner {
    public:
        // Constructor
        PathPlanner();
        // Destructor
        virtual ~PathPlanner();

        /**
         * Return new s and d list
         */
        //vector<double> GenerateTrajectory(vector<double> &start_s, vector<double> &end_s, vector<double> &start_d, vector<double> &end_d, double yaw, double speed, double T, double goal_time);

        /**
         * s(t) = s_i + dot s_i * t + dot dot s_i / 2 * t^2 + alpha_3 * t^3 + alpha_4 * t^4 + alpha_5 * t^5  
         */ 
        double CalculateTrajectoryEquation(vector<double> &coef, double t);

        /**
         * Calculate the Jerk Minimizing Trajectory that connects the initial state
         * to the final state in time T.
         */
        vector<double> CalculateJerkMinimizingCoef(vector<double> &start, vector<double> &end, double T);

        /**
         * Calculate trajectory's cost
         */
        double CalculateCost(vector<double> &s, int num_div, double goal_t);

        // private?
        const double MAX_JERK = 10.0;  // m/s/s/s
        const double EXPECTED_JERK_IN_ONE_SEC = 2.0;  // m/s/s

        // Calculate differentiate
        vector<double> Differentiate(vector<double> &x);

        // Calculate Polynomial Equation Result
        double CalculateEqRes(vector<double> &x, double t);
};

#endif /* PATH_PLANNER_H */