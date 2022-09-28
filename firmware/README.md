# Firmware

## Design

From a 10000' view, the controller firmware approximately has the following stages

1. Collect measurements from sensors
2. Evaluate controller to produce desired control outputs
3. Actuate via hardware to apply desired controls
4. return to 1.

### Collection
Some nuance should be acknowledged in regards to the collection of measurements. Not all sensors produce measurements at the same frequency. In addition to that, some may be triggered by interrupts, and thus posses a degree of asynchronicity. There should be structures in place to accommodate the streaming incomplete nature of these measurements. This should be achievable using a Kalman filter 

### Evaluation
Because of the possible fragmented nature of the measurements, it's likely that we should want an intermediate step which filters our complete state and estimates the likely values of the state before running our evaluation. The output of this estimator should be the input of our controller. This should probably run a a fixed time step

### Actuation
Desired output controls are sent to the appropriate systems which control actuators which apply controls in the physical world.

### Block Diagram

These three stages can be broken into three logically distinct classes of components sensors for collection, an estimator for evaluating state, and an actuator for taking the state and determining the next action to be taken to achieve a predetermined goal state. One or more sensors should contribute to the state estimation. However, a single state should be produced, and forwarded to the actuator. In turn, the actuator should produce a single control vector used as feedback for the estimator.

```
                           ┌──────────────────────┐
                           │                      │
┌──────┐              ┌────▼────┐            ┌────┴───┐
│Sensor├─────n..1────►│Estimator├────1..1───►│Actuator│
└──────┘              └─────────┘            └────────┘
````

Each component should have access to the same context object. The context should house the estimated state, handles for any relevant busses, and any other values that may be useful across components.

Sensors can either be polled, or event (interrupt) driven. The execution sequence for each may look like the following, respectively.

#### Polling

1. Request data from sensor
2. Receive response
3. Ingest into estimator
4. Goto 1

#### Event Driven

1. Sensor triggers interrupt
2. Request data from sensor
3. Receive response
4. Ingest into estimator

For an estimator instance that is based on a Kalman filter, ingesting a measurement involves performing a measurement update which is the most expensive part of the filter. For that reason, maintaining a queue of measurements may be desireable, such that all the relevant measurements are aggergated before being processed by the filter.