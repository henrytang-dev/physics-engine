#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "system_state.h"
#include "rigid_body.h"
#include "matrix.h"
#include "utilities.h"

#include <cfloat>

namespace physics_engine {
    class Constraint {
        public:
            static constexpr int MaxConstraintCount = 3;
            static constexpr int MaxBodyCount = 2;

            struct Output {
                double C[MaxConstraintCount];
                double J[MaxConstraintCount][3 * MaxBodyCount];
                double J_dot[MaxConstraintCount][3 * MaxBodyCount];
                double v_bias[MaxConstraintCount];
                double limits[MaxConstraintCount][2];
                double ks[MaxConstraintCount];
                double kd[MaxConstraintCount];
            };

            Constraint(int constraintCount, int bodyCount);
            virtual ~Constraint();

            virtual void calculate(Output *output, SystemState *state);
            inline int getConstraintCount() const { return m_constraintCount; }

            int m_index;
            int m_bodyCount;
            RigidBody *m_bodies[MaxBodyCount];

            double F_x[MaxConstraintCount][MaxBodyCount];
            double F_y[MaxConstraintCount][MaxBodyCount];
            double F_t[MaxConstraintCount][MaxBodyCount];

        protected:
            inline void noLimits(Output *output) {
                for (int i = 0; i < MaxConstraintCount; ++i) {
                    output->limits[i][0] = -DBL_MAX;
                    output->limits[i][1] = DBL_MAX;
                }
            }

        protected:
            int m_constraintCount;  

    };
}

#endif