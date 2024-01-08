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

        // Singleton pattern
        Drive();
        Drive(Drive const&);
        void operator=(Drive const&);
    public:
        void move(double power, double steering);
        void timed_gyro_drive(double max_speed, double heading, double seconds);
        void reset_gyro();

        // Singleton pattern
        // Drive(Drive const&) = delete;
        // void operator=(Drive const&) = delete;
        /** Singleton pattern. Call this instead of instantiating this class. **/
        static Drive& getInstance();
    };
    
} // namespace subsystems
