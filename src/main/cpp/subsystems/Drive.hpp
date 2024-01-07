#pragma once

#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
#include <AHRS.h>

namespace subsystems
{
    class Drive
    {
    private:
        ctre::phoenix::motorcontrol::can::WPI_TalonSRX L1{3};
        ctre::phoenix::motorcontrol::can::WPI_TalonSRX L2{4};
        ctre::phoenix::motorcontrol::can::WPI_TalonSRX R1{1};
        ctre::phoenix::motorcontrol::can::WPI_TalonSRX R2{2};

        AHRS* navx = new AHRS(SPI.Port.kMPX);
    public:
        Drive();
        void move(double power, double steering);
        bool routine_timed_gyro_drive(double max_speed, double heading, double seconds);
    };
    
} // namespace subsystems
