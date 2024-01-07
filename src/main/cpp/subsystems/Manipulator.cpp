#include "Manipulator.hpp"

namespace subsystems
{
    Manipulator::Manipulator()
    {
        this->arm_enc.Reset();

        this->arm_l.SetNeutralMode(ctre::phoenix::motorcontrol::Brake);
        this->arm_r.SetNeutralMode(ctre::phoenix::motorcontrol::Brake);
    }

    void Manipulator::arm(double power)
    {
        const double max_power = 0.25;
        
        // Stop from going too low
        // if (this->lower_arm_limit.Get() && power < 0.0) {
        //     power = 0.0;
        // }

        // // Stop from going too high
        // if (this->upper_arm_limit.Get() && power > 0.0) {
        //     power = 0.0;
        // }

        // Stop from making too much torque
        if (power > max_power) {
            power = max_power;
        } else if (power < -max_power) {
            power = -max_power;
        }

        this->arm_l.Set(-power);
        this->arm_r.Set(-power);  // -ve, as motors are pointing in opposite directions
    }

    void Manipulator::intake(double power)
    {
        this->intake_motor.Set(power);
    }

    void Manipulator::shoot(double power)
    {
        this->shooter_a.Set(power);
        // this->shooter_b.Set(power);  // TODO: check polarities
    }

    bool Manipulator::get_note_sensor()
    {
        return this->note_sensor.Get();
    }
    
} // namespace subsystems
