#pragma once

#include "codebook.h"
#include "envelope.h"

#define PACKETBLOBS 15

#define P_BANDS 17    /* 62Hz to 16kHz */
#define P_LEVELS 8    /* 30dB to 100dB */
#define P_LEVEL_0 30. /* 30 dB */
#define P_NOISECURVES 3

#define NOISE_COMPAND_LEVELS 40

#define VIF_POSIT 63
#define VIF_CLASS 16
#define VIF_PARTS 31

// other
typedef struct {
    int partitions;                  /* 0 to 31 */
    int partitionclass[ VIF_PARTS ]; /* 0 to 15 */

    int class_dim[ VIF_CLASS ];          /* 1 to 8 */
    int class_subs[ VIF_CLASS ];         /* 0,1,2,3 (bits: 1<<n poss) */
    int class_book[ VIF_CLASS ];         /* subs ^ dim entries */
    int class_subbook[ VIF_CLASS ][ 8 ]; /* [VIF_CLASS][subs] */

    int mult;                      /* 1 2 3 or 4 */
    int postlist[ VIF_POSIT + 2 ]; /* first two implicit */

    /* encode side analysis parameters */
    float maxover;
    float maxunder;
    float maxerr;

    float twofitweight;
    float twofitatten;

    int n;

} vorbis_info_floor1;

typedef struct vorbis_info_residue0 {
    /* block-partitioned VQ coded straight residue */
    long begin;
    long end;

    /* first stage (lossless partitioning) */
    int grouping;           /* group n vectors per partition */
    int partitions;         /* possible codebooks for a partition */
    int groupbook;          /* huffbook for partitioning */
    int secondstages[ 64 ]; /* expanded out to pointers in lookup */
    int booklist[ 256 ];    /* list of second stage books */

    const float classmetric1[ 64 ];
    const float classmetric2[ 64 ];
} vorbis_info_residue0;

typedef struct vorbis_info_mapping0 {
    int submaps;          /* <= 16 */
    int chmuxlist[ 256 ]; /* up to 256 channels in a Vorbis stream */

    int floorsubmap[ 16 ];   /* [mux] submap to floors */
    int residuesubmap[ 16 ]; /* [mux] submap to residue */

    int coupling_steps;
    int coupling_mag[ 256 ];
    int coupling_ang[ 256 ];

} vorbis_info_mapping0;

typedef struct {
    int eighth_octave_lines;

    /* for block long/short tuning; encode only */
    float preecho_thresh[ VE_BANDS ];
    float postecho_thresh[ VE_BANDS ];
    float stretch_penalty;
    float preecho_minenergy;

    float ampmax_att_per_sec;

    /* channel coupling config */
    int coupling_pkHz[ PACKETBLOBS ];
    int coupling_pointlimit[ 2 ][ PACKETBLOBS ];
    int coupling_prepointamp[ PACKETBLOBS ];
    int coupling_postpointamp[ PACKETBLOBS ];
    int sliding_lowpass[ 2 ][ PACKETBLOBS ];

} vorbis_info_psy_global;

// psych 11

typedef struct vp_adjblock {
    int block[ P_BANDS ];
} vp_adjblock;

typedef struct {
    int data[ P_NOISECURVES ][ 17 ];
} noise3;

typedef struct {
    int att[ P_NOISECURVES ];
    float boost;
    float decay;
} att3;

// psych 16

typedef struct {
    int pre[ PACKETBLOBS ];
    int post[ PACKETBLOBS ];
    float kHz[ PACKETBLOBS ];
    float lowpasskHz[ PACKETBLOBS ];
} adj_stereo;

typedef struct {
    int lo;
    int hi;
    int fixed;
} noiseguard;

// psych 44

typedef struct {
    int data[ NOISE_COMPAND_LEVELS ];
} compandblock;

// residue 16

/* careful with this; it's using static array sizing to make managing
   all the modes a little less annoying.  If we use a residue backend
   with > 12 partition types, or a different division of iteration,
   this needs to be updated. */
typedef struct {
    const static_codebook* books[ 12 ][ 3 ];
} static_bookblock;

typedef struct {
    int res_type;
    int limit_type; /* 0 lowpass limited, 1 point stereo limited */
    const vorbis_info_residue0* res;
    const static_codebook* book_aux;
    const static_codebook* book_aux_managed;
    const static_bookblock* books_base;
    const static_bookblock* books_base_managed;
} vorbis_residue_template;

typedef struct {
    const vorbis_info_mapping0* map;
    const vorbis_residue_template* res;
} vorbis_mapping_template;

extern const vorbis_info_mapping0 _map_nominal[ 2 ];
extern const vorbis_info_mapping0 _map_nominal_u[ 2 ];

// setup 11
typedef struct {
    int mappings;
    const double* rate_mapping;
    const double* quality_mapping;
    int coupling_restriction;
    long samplerate_min_restriction;
    long samplerate_max_restriction;

    const int* blocksize_short;
    const int* blocksize_long;

    const att3* psy_tone_masteratt;
    const int* psy_tone_0dB;
    const int* psy_tone_dBsuppress;

    const vp_adjblock* psy_tone_adj_impulse;
    const vp_adjblock* psy_tone_adj_long;
    const vp_adjblock* psy_tone_adj_other;

    const noiseguard* psy_noiseguards;
    const noise3* psy_noise_bias_impulse;
    const noise3* psy_noise_bias_padding;
    const noise3* psy_noise_bias_trans;
    const noise3* psy_noise_bias_long;
    const int* psy_noise_dBsuppress;

    const compandblock* psy_noise_compand;
    const double* psy_noise_compand_short_mapping;
    const double* psy_noise_compand_long_mapping;

    const int* psy_noise_normal_start[ 2 ];
    const int* psy_noise_normal_partition[ 2 ];
    const double* psy_noise_normal_thresh;

    const int* psy_ath_float;
    const int* psy_ath_abs;

    const double* psy_lowpass;

    const vorbis_info_psy_global* global_params;
    const double* global_mapping;
    const adj_stereo* stereo_modes;

    const static_codebook* const* const* const floor_books;
    const vorbis_info_floor1* floor_params;
    const int* floor_short_mapping;
    const int* floor_long_mapping;

    const vorbis_mapping_template* maps;
} ve_setup_data_template;
