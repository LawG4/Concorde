/**
 * @brief Defines all of the enums used by Concorde
 * @file Concorde_Enums.h
 * @license MIT License
 * @authors Lawrence Green,
 *
 * Further description:
 * Defines all of the concorde enums. they are split amongst return error codes and other utility enums, like
 * the vertex inputs
 */
#ifndef __CONCORDE_ENUMS_H__
#define __CONCORDE_ENUMS_H__

#include "Concorde.h"

/**
 * @brief Defines the error codes that may be reported through some concorde functions
 */
typedef enum {
    cec_success = 0,                   /*We were successful*/
    cec_unclassified_failure,          /*We had an error, but we've not yet added an enum for it*/
    cec_invalid_vertex_attribute_mask, /*The vertex attribute mask doesn't make sense*/
    cec_already_rendering,
    cec_not_finished_rendering,
    cec_invalid_vertex_mask,
    cec_vertex_alloc_failed,
    cec_shader_not_found,
    cec_shader_comp_fail
} concorde_error_code;

/**
 * @brief When formatting the vertex inputs for the graphics processer, we need to tell the GP which
 * components of the vertex we're talking about
 */
typedef enum {
    position = 1,     /*Position vertex attribute*/
    normal = 1 << 1,  /*Normal attribute*/
    color_0 = 1 << 2, /* Color for Tev stage 0 vertex attribute*/
    color_1 = 1 << 3, /* Color for Tev stage 1 vertex attribute*/
    tex_0 = 1 << 4,   /* Tex coord for Tev stage 0 vertex attribute*/
    tex_1 = 1 << 5    /* Tex coord for Tev stage 1 vertex attribute*/
} Concorde_Vertex_Attributes;
#endif  // !__CONCORDE_ENUMS_H__
