#define CATCH_CONFIG_MAIN

#include <cmath>
#include <vector>

#include "catch.hpp"
#include "catch_reporter_sonarqube.hpp"

#include "../src/vehicle.h"

static const double epsilon = 0.01;

SCENARIO("Vehicle can estimate a position in a future", "[vehicle]") {
    GIVEN("A Vehicle") {
        Vehicle v;

        WHEN("Simple move action's pos, velocity, accel and future time are given") {
            v.s_state[0] = 3.0;
            v.s_state[1] = 2.0;
            v.s_state[2] = 1.0;

            v.d_state[0] = 4.0;
            v.d_state[1] = 3.0;
            v.d_state[2] = 2.0;

            double t = 1.0;

            vector<double> actual = v.PredictSDStateAt(t);
            THEN("New s, d axis states at t=1 are estimated") {
                vector<double> expected = {5.5, 3.0, 1.0, 8.0, 5.0, 2.0};
                REQUIRE(actual.size() == expected.size());

                for (int i = 0; i < actual.size(); i++) {
                    double diff = abs(actual[i] - expected[i]);
                    REQUIRE(diff < epsilon);
                }
            }
        }

        WHEN("Stopped vehicle's new state is given and future time position is required") {
            double x[2] = {1.0, 1.0};
            double y[2] = {2.0, 2.0};
            double t = 1.0;

            v.UpdateState(x, y, 4.0, 6.0);
            vector<double> actual = v.PredictSDStateAt(t);
            THEN("New s, d axis states with updated state at t = 1 are estimated") {
                vector<double> expected = {10.0, 8.0, 4.0, 15.0, 12.0, 6.0};
                REQUIRE(actual.size() == expected.size());

                for (int i = 0; i < actual.size(); i++) {
                    double diff = abs(actual[i] - expected[i]);
                    REQUIRE(diff < epsilon);
                }
            }
        }

        WHEN("vx and vy are given and future s-axis position is required") {
            double x[2] = {1.0, 3.0};
            double y[2] = {2.0, 4.0};
            double t = 1.0;

            v.UpdateState(x, y, 0.0, 0.0);  // speed will be sqrt(9 + 16) = 5.0
            double actual = v.PredictSPosAt(t);
            THEN("Future(t=1) s position is predicted") {
                double expected = 5.0;  // s + speed * t = 0.0 + 5.0 * 1.0 = 5.0
                REQUIRE(abs(actual - expected) < epsilon);
            }
        }
    }
}
