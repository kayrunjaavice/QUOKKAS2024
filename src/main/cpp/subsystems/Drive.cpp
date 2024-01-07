#include "Drive.hpp"

namespace subsystems
{
    Drive::Drive()
    {
    }
    
    void Drive::move(double power, double steering)
    {
        double lpower = power + steering;
        double rpower = power - steering;
        
        this->L1.Set(lpower);
        this->L2.Set(lpower);

        this->R1.Set(rpower);
        this->R2.Set(rpower);
    }

    void Drive::routine_timed_gyro_drive(double max_speed, double heading, double seconds)
    {
        double start_time = frc::GetTime().value();
        double end_time = start_time + seconds;

        while (frc::GetTime().value() < end_time)
        {
            double Kp = 0.01;
            double error = this->navx->GetYaw() - heading;
            double steering = Kp * error;
            this->move(max_speed, steering);
        }
        
        this->move(0, 0);  // stop the robot after the movement
    }
    
} // namespace subsystems
