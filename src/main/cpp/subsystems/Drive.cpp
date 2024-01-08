#include "Drive.hpp"

namespace subsystems
{    
    // Singleton
    Drive::Drive() {
    }
    
    Drive& Drive::getInstance()
    {
        static Drive instance;
        return instance;
    }
    
    void Drive::reset_gyro()
    {
        this->navx->Reset();
    }
    
    void Drive::move(double power, double steering)
    {
        double lpower = power - steering;
        double rpower = power + steering;
        
        this->L1.Set(-lpower);
        this->L2.Set(-lpower);

        this->R1.Set(rpower);
        this->R2.Set(rpower);
    }

    void Drive::gyro_drive(double max_speed, double heading)
    {
        double Kp = 0.01;
        double error = heading - this->navx->GetAngle();
        double steering = Kp * error;
        this->move(max_speed, steering);
    }
    
} // namespace subsystems
