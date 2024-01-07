#pragma once

#include <frc/SPI.h>
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <AHRS.h>
#include "../subsystems/Drive.hpp"

namespace subsystems
{
    class Drive
    {
    private:
        ctre::phoenix::motorcontrol::can::WPI_TalonSRX L1{3};
        ctre::phoenix::motorcontrol::can::WPI_TalonSRX L2{4};
        ctre::phoenix::motorcontrol::can::WPI_TalonSRX R1{1};
        ctre::phoenix::motorcontrol::can::WPI_TalonSRX R2{2};

        AHRS* navx = new AHRS(frc::SPI::Port::kMXP);
    public:
        Drive();
        void move(double power, double steering);
        void routine_timed_gyro_drive(double max_speed, double heading, double seconds);
    };
    
} // namespace subsystems
