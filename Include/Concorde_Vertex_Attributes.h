/**
 * When sending vertex data to the GPU, it needs to be told how to interpret it.
 * The Wii has an internal table 8 entries long, which you can occupy.
 * 
 * This is called the vertex attribute table, and an entry needs to be used for each type of draw.
 * For example you could have one entry that tells the wii how to handle vertices 
 * that belong to a model, and another entry describing how to interpret vertices for the HUD
 * 
 * Now GX has a pretty flexible input assembler, but I think it'll be best to limit this flexability 
 * inside of concorde, the point of this is to have less variation, making it easier to emulate in 
 * GL. Also the average user doesn't need that much flexibility, realisticallly a triangle buffer
 * is enough.
 */ 

#ifndef __CONCORDE_ATTRIBUTES_H__
#define __CONCORDE_ATTRIBUTES_H__

#include <stdint.h>

/**
 * Describes all of the settings for one entry in the vertex atribute table 
 */
typedef struct concorde_vertex_attribute
{
    /*Vertex descriptions, how we plan to feed GX the different vertex attributes*/
    uint8_t position_desc;
    uint8_t normal_desc;
    uint8_t color0_desc;
    uint8_t tex0_desc;
    uint8_t tex1_desc;

    /*How many entries there are per vertex attribute*/
    /*The rest of the Vertex attribute format is fixed*/
    uint8_t position_width;
    uint8_t normal_width;
    uint8_t color0_width;
    uint8_t tex0_width;
    uint8_t tex1_width;
}concorde_vertex_attribute;


#endif