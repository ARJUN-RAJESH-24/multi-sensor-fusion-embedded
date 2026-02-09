# multi-sensor-fusion-embedded

https://docs.google.com/document/d/1HS7LJLWHO-os45puliYl5kCMo8Mn_Q_I8ZpBiLweHjo/edit?usp=sharing


This repository contains independent ESP-IDF reference implementations
for sensors intended to be used in a multi-sensor fusion system.

Current sensors:
- MLX90614 (IR temperature)
- MQ-135 (Gas sensor)
- OV2640 (RGB camera)

Each sensor is implemented and validated in isolation.
Fusion logic is designed after sensor characterization.
