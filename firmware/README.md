# Firmware

## Design

From a 10000' view, the controller firmware approximately has the following stages

1. Collect measurements from sensors
2. Evaluate controller to produce desired control outputs
3. Actuate via hardware to apply desired controls
4. return to 1.

### Collection
Some nuance should be acknowledged in regards to the collection of measurements. Not all sensors produce measurements at the same frequency. In addition to that, some may be triggered by interrupts, and thus posses a degree of asynchronicity. There should be structures in place to accommodate the streaming incomplete nature of these measurements.

### Evaluation
Because of the possible fragmented nature of the measurements, it's likely that we should want an intermediate step which filters our complete state and estimates the likely values of the state before running our evaluation. The output of this estimator should be the input of our controller. This should probably run a a fixed time step

### Actuation
Desired output controls are sent to the appropriate systems which control actuators which apply controls in the physical world.
