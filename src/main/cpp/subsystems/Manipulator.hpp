#pragma once

#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>
#include <frc/DutyCycleEncoder.h>
#include <frc/DigitalInput.h>

namespace subsystems
{
    class Manipulator
    {
    private:        
        frc::DutyCycleEncoder arm_enc{9};
    
        ctre::phoenix::motorcontrol::can::WPI_VictorSPX arm_l{5};
        ctre::phoenix::motorcontrol::can::WPI_VictorSPX arm_r{6};

        ctre::phoenix::motorcontrol::can::WPI_VictorSPX shooter_a{7};
        ctre::phoenix::motorcontrol::can::WPI_VictorSPX shooter_b{8};

        frc::DigitalInput note_sensor{0};
        ctre::phoenix::motorcontrol::can::WPI_VictorSPX intake_motor{9};

        // Singleton pattern
        Manipulator();
        Manipulator(Manipulator const&);
        void operator=(Manipulator const&);
    public:
        double kARM_FLOOR_POS = 0.0;
        double kARM_START_POS = 0.0;
        double kARM_AMP_POS   = 0.0;        
        
        void arm(double power);
        void arm_to_pos(double pos);
        void intake(double power);
        void shoot(double power);
        bool get_note_sensor();
        double get_arm_enc();

        // Singleton pattern
        // Manipulator(Manipulator const&) = delete;
        // void operator=(Manipulator const&) = delete;
        /** Singleton pattern. Call this instead of instantiating this class. **/
        static Manipulator& getInstance();
    };
    
} // namespace subsystems
