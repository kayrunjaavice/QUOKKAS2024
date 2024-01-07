#pragma once

#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <frc/Encoder.h>
#include <frc/DigitalInput.h>

namespace subsystems
{
    class Manipulator
    {
    private:        
        frc::Encoder arm_enc{1, 2};
        frc::DigitalInput lower_arm_limit{3};
        frc::DigitalInput upper_arm_limit{4};
    
        ctre::phoenix::motorcontrol::can::WPI_VictorSPX arm_l{5};
        ctre::phoenix::motorcontrol::can::WPI_VictorSPX arm_r{6};

        ctre::phoenix::motorcontrol::can::WPI_VictorSPX shooter_a{7};
        ctre::phoenix::motorcontrol::can::WPI_VictorSPX shooter_b{8};

        frc::DigitalInput note_sensor{0};
        ctre::phoenix::motorcontrol::can::WPI_VictorSPX intake_motor{9};
    public:
        Manipulator();
        void arm(double power);
        void intake(double power);
        void shoot(double power);
        bool get_note_sensor();
    };
    
} // namespace subsystems
