//
// Created by Accawi, Gina K. on 6/17/16.
//

#include "MotorShaftPower.h"
#include "MotorEfficiency.h"
#include "MotorPower.h"
#include "MotorCurrent.h"
#include "MotorPowerFactor.h"

double MotorShaftPower::calculate() {
    tempLoadFraction_ = 0.01;
    while (true) {
        MotorCurrent motorCurrent(motorRatedPower_, motorRPM_, efficiencyClass_,
                                  tempLoadFraction_, ratedVoltage_);
        current = motorCurrent.calculate();
        MotorEfficiency motorEfficiency(motorRPM_, efficiencyClass_, motorRatedPower_,
                                        motorMeasuredPower_, tempLoadFraction_);
        eff = motorEfficiency.calculate();
        MotorPowerFactor motorPowerFactor(motorRatedPower_, tempLoadFraction_, current, eff, ratedVoltage_);
        pf = motorPowerFactor.calculate();
        MotorPower motorPower(ratedVoltage_, current, pf);
        power = motorPower.calculate();
        if (power > motorMeasuredPower_ || tempLoadFraction_ > 1.5) {
            powerE2 = power;
            lf2 = tempLoadFraction_;
            eff2 = eff;
            pf2 = pf;
            break;
        } else {
            powerE1 = power;
            lf1 = tempLoadFraction_;
            eff1 = eff;
            pf1 = pf;
            tempLoadFraction_ += 0.01;
        }
    }
    double motorPowerdiff_ = powerE2 - powerE1;
    double measuredMotorPowerdiff_ = motorMeasuredPower_ - powerE1;
    double fractionalIndex_ = lf1 + ((measuredMotorPowerdiff_ / motorPowerdiff_) / 100);
    eff = eff1 + 100*(fractionalIndex_-lf1)*(eff2-eff1);
    double adjpf1 = pf1 / (((((fieldVoltage_ / ratedVoltage_) - 1) * (((-2) * lf1) + 1)) + 1) *
                           (fieldVoltage_ / ratedVoltage_));
    double adjpf2 = pf2 / (((((fieldVoltage_ / ratedVoltage_) - 1) * (((-2) * lf2) + 1)) + 1) *
                           (fieldVoltage_ / ratedVoltage_));
    pf = adjpf1 + 100 * (fractionalIndex_ - lf1) * (adjpf2 - adjpf1);
    //Current output
    current = motorMeasuredPower_ / (fieldVoltage_ * sqrt(3) * pf / 1000);
    // Output in kW
    motorShaftPower_ = motorMeasuredPower_ * eff;
    // Output in hP
    motorShaftPower_ = motorShaftPower_ / 0.746;
    return motorShaftPower_;
}

double MotorShaftPower::calculateCurrent() {
    return current;
}

double MotorShaftPower::calculateEfficiency() {
    return eff;
}

double MotorShaftPower::calculatePowerFactor() {
    return pf;
}

/* Internal Calculation of motor electric power.
double MotorShaftPower::calculateElectricPower() {
    return power;
}
 */

