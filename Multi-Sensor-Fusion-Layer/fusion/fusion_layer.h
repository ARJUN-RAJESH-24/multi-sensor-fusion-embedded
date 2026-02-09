#ifndef FUSION_LAYER_H
#define FUSION_LAYER_H

#include "fusion_types.h"

/**
 * @brief Fuse sensor data into a single system state
 *
 * @param snapshot Pointer to normalized sensor snapshot
 * @return FusionState Resulting fused state
 */
FusionState fuse_sensor_data(const SensorSnapshot *snapshot);

#endif 
