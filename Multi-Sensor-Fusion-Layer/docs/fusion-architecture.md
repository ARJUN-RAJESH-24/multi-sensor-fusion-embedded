# Fusion Layer Architecture

## Purpose

The fusion layer combines heterogeneous sensor decisions into a single, reliable system state. Individual sensors are limited when used alone; fusion improves robustness by correlating their outputs while remaining independent of hardware drivers.

## Sensor Inputs

The fusion layer operates on normalized, decision-level inputs:

* **IR (MLX90614):** object temperature, heat presence flag
* **Gas (MQ-135):** gas level, hazard presence flag
* **RGB (OV2640):** visual confirmation flag

## Data Normalization

Before fusion, sensor data is:

* Converted to consistent units where applicable
* Reduced to boolean presence indicators via thresholds
* Decoupled temporally to allow asynchronous updates
* Stripped of raw high-volume data (e.g., image buffers)

## Decision-Level Fusion Strategy

Fusion is rule-based and deterministic. It evaluates combinations of sensor conditions (e.g., heat + vision, heat + gas) to infer higher-level states. No machine learning or probabilistic methods are used.

## Fusion Output States

The fusion layer outputs one of the following states:

* **SAFE**
* **POSSIBLE_HUMAN**
* **CONFIRMED_HUMAN**
* **HAZARD**

## Constraints & Assumptions

* ESP32 acts as an intermediate processor
* Sensors are validated independently
* No real-time guarantees
* Platform-agnostic logic

