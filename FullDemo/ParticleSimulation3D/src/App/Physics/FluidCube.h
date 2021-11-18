#pragma once

#include <cmath>

#define IX(x, y, z) ((x) + (y) * N + (z) * N * N)

namespace Physics {
    typedef struct FluidCube {
        int size;
        float dt;
        float diff;
        float visc;

        float* s;
        float* density;

        float* Vx;
        float* Vy;
        float* Vz;

        float* Vx0;
        float* Vy0;
        float* Vz0;
    }FluidCube;

}

