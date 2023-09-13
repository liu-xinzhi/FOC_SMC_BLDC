#ifndef INLINE_CS_LIB_H
#define INLINE_CS_LIB_H

#include "Ctrl/Sensor/CurrentSense/CurrentSense.h"


class InlineCurrentSense : public CurrentSense
{
public:
    /**
      InlineCurrentSense class constructor
      @param shunt_resistor shunt resistor value
      @param gain current-sense op-amp gain
      @param phA A phase adc pin
      @param phB B phase adc pin
      @param phC C phase adc pin (optional)
    */
    InlineCurrentSense(float shunt_resistor, float gain, int pinA, int pinB, int pinC = NOT_SET);

    // CurrentSense interface implementing functions 
    void init() override;

    PhaseCurrent_s getPhaseCurrents() override;

    int driverSync(BLDCDriver *driver) override;

    int driverAlign(BLDCDriver *driver, float voltage) override;

    // ADC measuremnet gain for each phase
    // support for different gains for different phases of more commonly - inverted phase currents
    // this should be automated later
    float gain_a; //!< phase A gain
    float gain_b; //!< phase B gain
    float gain_c; //!< phase C gain

    float phA,phB,phC;

private:

    // hardware variables
    int pinA; //!< pin A analog pin for current measurement
    int pinB; //!< pin B analog pin for current measurement
    int pinC; //!< pin C analog pin for current measurement

    // gain variables
    double shunt_resistor; //!< Shunt resistor value 
    double amp_gain; //!< amp gain value 
    double volts_to_amps_ratio; //!< Volts to amps ratio

    /**
     *  Function finding zero offsets of the ADC
     */
    void calibrateOffsets();

    double offset_ia; //!< zero current A voltage value (center of the adc reading)
    double offset_ib; //!< zero current B voltage value (center of the adc reading)
    double offset_ic; //!< zero current C voltage value (center of the adc reading)



};

#endif