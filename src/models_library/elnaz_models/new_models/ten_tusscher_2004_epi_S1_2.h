
#ifndef MONOALG3D_MODEL_TEN_TUSSCHER_change_H
#define MONOALG3D_MODEL_TEN_TUSSCHER_change_H


// Scenario 1_2 - (AP + max:dvdt)

#include <stdint.h>
#include "model_common.h"

#define NEQ 17
#define INITIAL_V (-86.2f)
#define EPI

#ifdef __CUDACC__

extern "C" {
    #include "../utils/file_utils.h"
}

__constant__  size_t pitch;
size_t pitch_h;

__global__ void kernel_set_model_inital_conditions(real *sv, int num_volumes);

__global__ void solve_gpu(real dt, real *sv, real* stim_currents,
                          uint32_t *cells_to_solve, uint32_t num_cells_to_solve,
                          int num_steps);

inline __device__ void RHS_gpu(real *sv_, real *rDY_, real stim_current, int threadID_, real dt);

#else
#include "../utils/file_utils.h"
#endif

void RHS_cpu(const real *sv, real *rDY_, real stim_current, real dt);
void solve_model_ode_cpu(real dt, real *sv, real stim_current);

#endif //MONOALG3D_MODEL_TEN_TUSSCHER_2004_H
