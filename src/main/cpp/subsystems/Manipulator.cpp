#include "Manipulator.hpp"

namespace subsystems
{
    // Singleton
    Manipulator& Manipulator::getInstance()
    {
        static Manipulator instance;
        return instance;
    }
    
    Manipulator::Manipulator()
    {
        this->arm_l.SetNeutralMode(ctre::phoenix::motorcontrol::Brake);
        this->arm_r.SetNeutralMode(ctre::phoenix::motorcontrol::Brake);
    }

    double Manipulator::get_arm_enc()
    {
        return this->arm_enc.GetAbsolutePosition();
    }

    /* See Manipulator::kARM_FLOOR_POS etc. */
    void Manipulator::arm_to_pos(double pos)
    {
        double Kp = 0.0;
        double error = pos - this->arm_enc.GetAbsolutePosition();
        double power = Kp * error;
        this->arm(power);
    }

    void Manipulator::arm(double power)
    {
        const double max_power = 0.25;

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
