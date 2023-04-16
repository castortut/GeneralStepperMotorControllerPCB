# Motor controller features

Motor controller features for designing a stepper motor driver board that supports A4988 and DRV8825 motor controllers**

### A4988

- Steps: Full step - 1/16
  
  - Maximum motor voltage: 35 V, 2 A
  
  - Logic voltage: 
  
  - Micro-step select: 50-100 kohm pull-down resistance, default value is full step

- Microstepping truth table:
  
  - MS1, MS2, MS3
  
  - LLL Full step
  
  - HLL Half step
  
  - LHL Quarter step
  
  - HHL Eighth step
  
  - HHH sixteenth step

- Pins:
  
  - 3.3 and 5 V compatible logic supply
  
  - RESET active when low. Pull up to operate.
  
  - ENABLE active when low. Pull down to operate.
  
  - A logic low on the SLEEP pin puts the A4988
    into Sleep mode.

- Conclusions:
  
  - 3,3 V or 5 V logic
  
  - Max motor voltage 35 V
  
  - Max motor current 2 A
  
  - Not necessary to connect MS1, MS2, MS3 anywhere, put jumpers to logic high. 50 - 100 kohm internal pulldowns.
  
  - Connect RESET high. No need to control.
  
  - Connect SLEEP high. No need to control.

### DRV8825

- Steps: Full - 1/32

- Electrical values:
  
  - 8.2 - 45 V operating supply voltage
  
  - Max drive current: 2A with 24 V
  
  - 3.3 and 5 V compatible

- ENABLE: active when low. Internal 100 kΩ pulldown. Pull down to operate.

- RESET:    active when low. Internal 100 kΩ pulldown. Pull up to operate.

- SLEEP:    active when low. Internal 1 MΩ    pulldown. Pull up to operate.

- nFault:   Outputs logic low when in fault condition.

- Microstepping:
  
  - MODE0, MODE1, MODE2
  
  - LLL Full step
  
  - HLL 1/2
  
  - LHL 1/4
  
  - HHL 1/8
  
  - LLH 1/16
  
  - HHH or LHH or HLH 1/32

### Combined conclusions:

- A4988 has lower maximum voltage, 35 V

- DRV8825 needs at least 8.2 V voltage supply. 
  
  - Motor supply voltage should therefore be 8.2 - 35 V.

- Micro-stepping pins
  
  - Connect to logic high through jumpers

- ENABLE: Connect to ground to enable motor drivers.
  
  - Connect GROUND

- RESET: Connect to HIGH to to enable motor drivers.
  
  - Connect HIGH

- SLEEP: HIGH enables device, LOW puts it to sleep.
  
  - Connect to 10 kohm pulldown
  
  - Connect to MCU

- DRV8825 FAULT / A4988 Logic voltage supply pin
  
  - Connect to HIGH through jumper

- STEP / DIR
  
  - Connect to MCU
