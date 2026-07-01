#pragma once
/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggVorbis SOFTWARE CODEC SOURCE CODE.   *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis SOURCE CODE IS (C) COPYRIGHT 1994-2009             *
 * by the Xiph.Org Foundation http://www.xiph.org/                  *
 *                                                                  *
 ********************************************************************

 function: libvorbis backend and mapping structures; needed for
           static mode headers
 last mod: $Id: backends.h 16227 2009-07-08 06:58:46Z xiphmont $

 ********************************************************************/

/* this is exposed up here because we need it for static modes.
   Lookups for each backend aren't exposed because there's no reason
   to do so */

#ifndef _vorbis_backend_h_
#define _vorbis_backend_h_

#include "codec_internal.h"

/* this would all be simpler/shorter with templates, but.... */
/* Floor backend generic *****************************************/
typedef struct {
    void ( *pack )( vorbis_info_floor*, oggpack_buffer* );
    vorbis_info_floor* ( *unpack )( vorbis_info*, oggpack_buffer* );
    vorbis_look_floor* ( *look )( vorbis_dsp_state*, vorbis_info_floor* );
    void ( *free_info )( vorbis_info_floor* );
    void ( *free_look )( vorbis_look_floor* );
    void* ( *inverse1 )( struct vorbis_block*, vorbis_look_floor* );
    int ( *inverse2 )( struct vorbis_block*,
                       vorbis_look_floor*,
                       void* buffer,
                       float* );
} vorbis_func_floor;

typedef struct {
    int order;
    long rate;
    long barkmap;

    int ampbits;
    int ampdB;

    int numbooks; /* <= 16 */
    int books[ 16 ];

    float lessthan;    /* encode-only config setting hacks for libvorbis */
    float greaterthan; /* encode-only config setting hacks for libvorbis */

} vorbis_info_floor0;

#define VIF_POSIT 63
#define VIF_CLASS 16
#define VIF_PARTS 31

/* Residue backend generic *****************************************/
typedef struct {
    void ( *pack )( vorbis_info_residue*, oggpack_buffer* );
    vorbis_info_residue* ( *unpack )( vorbis_info*, oggpack_buffer* );
    vorbis_look_residue* ( *look )( vorbis_dsp_state*, vorbis_info_residue* );
    void ( *free_info )( vorbis_info_residue* );
    void ( *free_look )( vorbis_look_residue* );
    long** ( *class )( struct vorbis_block*,
                       vorbis_look_residue*,
                       float**,
                       int*,
                       int );
    int ( *forward )( oggpack_buffer*,
                      struct vorbis_block*,
                      vorbis_look_residue*,
                      float**,
                      float**,
                      int*,
                      int,
                      long** );
    int ( *inverse )( struct vorbis_block*,
                      vorbis_look_residue*,
                      float**,
                      int*,
                      int );
} vorbis_func_residue;

/* Mapping backend generic *****************************************/
typedef struct {
    void ( *pack )( vorbis_info*, vorbis_info_mapping*, oggpack_buffer* );
    vorbis_info_mapping* ( *unpack )( vorbis_info*, oggpack_buffer* );
    void ( *free_info )( vorbis_info_mapping* );
    int ( *forward )( struct vorbis_block* vb );
    int ( *inverse )( struct vorbis_block* vb, vorbis_info_mapping* );
} vorbis_func_mapping;

#endif
