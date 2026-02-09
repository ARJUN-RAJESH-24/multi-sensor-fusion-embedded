#include "fusion_layer.h"

FusionState fuse_sensor_data(const SensorSnapshot *s)
{
    /* ---- Highest priority: human + hazardous environment ---- */
    if (s->ir.heat_present && s->gas.hazard_present) {
        return FUSION_HAZARD;
    }

    /* ---- Strong human confirmation ---- */
    if (s->ir.heat_present && s->rgb.visual_confirmation) {
        return FUSION_CONFIRMED_HUMAN;
    }

    /* ---- Weak human indication (thermal only) ---- */
    if (s->ir.heat_present) {
        return FUSION_POSSIBLE_HUMAN;
    }

    /* ---- Environmental hazard without human presence ---- */
    if (s->gas.hazard_present) {
        return FUSION_HAZARD;
    }


    return FUSION_SAFE;
}
