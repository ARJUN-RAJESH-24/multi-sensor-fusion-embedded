#ifndef FUSION_TYPES_H
#define FUSION_TYPES_H

#include <stdbool.h>
#include <stdint.h>

/* ================= IR SENSOR ================= */

typedef struct {
    float object_temperature;   // °C
    bool  heat_present;         // threshold-derived
} IR_Data;

/* ================= GAS SENSOR ================= */

typedef struct {
    uint16_t gas_level;          // ADC or normalized value
    bool     hazard_present;     // threshold-derived
} Gas_Data;

/* ================= RGB CAMERA ================= */

typedef struct {
    bool visual_confirmation;    // decision-level output
} RGB_Data;

/* ============ SENSOR SNAPSHOT ================= */

typedef struct {
    IR_Data  ir;
    Gas_Data gas;
    RGB_Data rgb;
} SensorSnapshot;

/* ============ FUSION OUTPUT =================== */

typedef enum {
    FUSION_SAFE = 0,
    FUSION_POSSIBLE_HUMAN,
    FUSION_CONFIRMED_HUMAN,
    FUSION_HAZARD
} FusionState;

#endif 
