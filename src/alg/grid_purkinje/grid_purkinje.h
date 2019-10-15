//
// Created by bergolho on 10/09/19.
//

#ifndef MONOALG3D_GRID_PURKINJE_H
#define MONOALG3D_GRID_PURKINJE_H

#include "../cell/cell.h"
#include "../../graph/graph.h"
#include "../../common_types/common_types.h"

#include <stdlib.h>
#include <stdio.h>

struct grid_purkinje 
{

    struct point_3d cube_side_length;

    struct point_3d mesh_side_length;

    uint32_t number_of_purkinje_cells;      // Number of Purkinje cells of grid.

    uint32_t num_active_purkinje_cells;

    struct cell_node **purkinje_cells;
    struct cell_node *first_cell;           // First Purkinje cell of grid.

    struct graph *the_network;              // Purkinje network graph

};


struct grid_purkinje* new_grid_purkinje ();
/*
void initialize_grid(struct grid *the_grid, struct point_3d side_length);
void clean_and_free_grid(struct grid* the_grid);
void construct_grid(struct grid *the_grid);
void initialize_and_construct_grid(struct grid *the_grid, struct point_3d side_length);

void print_grid(struct grid* the_grid, FILE *output_file);
void print_grid_with_scar_info(struct grid *the_grid, FILE *output_file, bool binary);

void clean_grid(struct grid *the_grid);
void order_grid_cells (struct grid *the_grid);

void set_grid_flux(struct grid *the_grid);

void grid_to_csr(struct grid *the_grid, real **A, int **IA, int **JA);


bool refine_grid_with_bound(struct grid* the_grid, real_cpu refinement_bound,  real_cpu min_dx, real_cpu min_dy, real_cpu min_dz);
void refine_grid(struct grid* the_grid, int num_steps);
void refine_grid_cell(struct grid *the_grid, struct cell_node* grid_cell);
void refine_fibrotic_cells(struct grid *the_grid);
void refine_border_zone_cells(struct grid *the_grid);

bool derefine_grid_with_bound (struct grid *the_grid, real_cpu derefinement_bound, real_cpu max_dx, real_cpu max_dy, real_cpu max_dz);
void derefine_all_grid (struct grid* the_grid);
void derefine_grid_inactive_cells (struct grid* the_grid);
bool derefine_grid_cell (struct grid *the_grid, struct cell_node *grid_cell);


void print_grid_matrix(struct grid *the_grid, FILE* output_file);
void print_grid_vector(struct grid* the_grid, FILE *output_file, char name);
real_cpu * grid_vector_to_array(struct grid *the_grid, char name, uint32_t *num_lines);
void print_grid_matrix_as_octave_matrix(struct grid *the_grid, FILE *output_file);

int get_num_refinement_steps_to_discretization (float side_len, real_cpu h);
void save_grid_domain (struct grid * the_grid, const char *file_name);

void initialize_and_construct_grid_purkinje (struct grid *the_grid);
void initialize_grid_purkinje (struct grid *the_grid);
void construct_grid_purkinje (struct grid *the_grid);
void translate_mesh_to_origin(struct grid *grid);
void construct_grid_from_file(struct grid *grid, FILE *matrix_a, FILE *vector_b);

void link_purkinje_to_endocardium (struct grid *the_grid ,struct terminal **the_terminals);
*/

#endif //MONOALG3D_GRID_PURKINJE_H