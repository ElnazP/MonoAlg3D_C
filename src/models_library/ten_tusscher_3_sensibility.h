#ifndef MONOALG3D_MODEL_TEN_TUSSCHER_3_COMMON_H
#define MONOALG3D_MODEL_TEN_TUSSCHER_3_COMMON_H

/*
 * This model is used for the sensiblity analysis of Pedro's paper.
*/ 

#include <stdio.h>
#include <stdint.h>

#include "model_common.h"

#define NEQ 12
#define INITIAL_V (-86.2f)

// This model is set to work with endocardium cells
#define ENDO

#ifdef __CUDACC__

extern "C" {
    #include "../utils/file_utils.h"
}

__constant__  size_t pitch;
size_t pitch_h;

__global__ void kernel_set_model_inital_conditions(real *sv, real *extra_data, int num_volumes);

__global__ void solve_gpu(real dt, real *sv, real* stim_currents,
                          uint32_t *cells_to_solve, uint32_t num_cells_to_solve,
                          int num_steps, real *fibrosis, real *extra_parameters);

inline __device__ void RHS_gpu(real *sv_, real *rDY_, real stim_current, int threadID_, real dt, real fibrosis, real *extra_parameters);
#else
#include "../utils/file_utils.h"
#endif


void RHS_cpu(const real *sv, real *rDY_, real stim_current, real dt, real fibrosis, real *extra_parameters);
void solve_model_ode_cpu(real dt, real *sv, real stim_current, real fibrosis, real *extra_parameters);

#endif //MONOALG3D_MODEL_TEN_TUSSCHER_3_COMMON_H
