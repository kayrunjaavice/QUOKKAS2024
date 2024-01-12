#include "SendIt.hpp"
#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include "../util/util.hpp"

namespace autonomous
{    
    SendIt::SendIt() {
        st = frc::GetTime().value();
        frc::SmartDashboard::PutNumber("start time", st);
    }
    
    void SendIt::run() {
        using namespace subsystems;

        frc::SmartDashboard::PutNumber("time", frc::GetTime().value());
        if (util::wait(st, 2)) {
            // Lower arm
            Manipulator::getInstance().shoot(0.5);
            Manipulator::getInstance().arm_to_pos(0.545);
        } else if (util::wait(st, 4)) {
            // Shoot
            Manipulator::getInstance().intake(1.0);
            Manipulator::getInstance().shoot(0.5);
            Manipulator::getInstance().arm_to_pos(Manipulator::getInstance().kARM_FENDER_POS);
        } else if (util::wait(st, 5.5)) {
            // Drive, intake
            if (Manipulator::getInstance().get_note_sensor()) {
                Manipulator::getInstance().intake(0.375);
            } else {
                Manipulator::getInstance().intake(0.0);
            }
            Manipulator::getInstance().shoot(0.0);
            Manipulator::getInstance().arm_to_pos(Manipulator::getInstance().kARM_FLOOR_POS);
            Drive::getInstance().gyro_drive(0.375, 0.0);
        } else if (util::wait(st, 7.0)) {
            // Shoot
            Manipulator::getInstance().intake(0.0);
            Manipulator::getInstance().shoot(1.0);
            
            // Set shot angle
            std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
            double ty = table->GetNumber("ty", 0.0);
            double shot_angle = -0.00008 * pow(ty,2) + .00252*ty + .4992;
            Manipulator::getInstance().arm_to_pos(shot_angle);
            
            // vision aiming
            double tx = table->GetNumber("tx", 0.0);
            double Kp = 0.05;
            Drive::getInstance().move(0.0, Kp * tx);
        
        } else if (util::wait(st, 9.0)) {
            // Shoot
            Manipulator::getInstance().intake(1.0);
            Manipulator::getInstance().shoot(1.0);
            
            // Set shot angle
            std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
            double ty = table->GetNumber("ty", 0.0);
            double shot_angle = -0.00008 * pow(ty,2) + .00252*ty + .4992;
            Manipulator::getInstance().arm_to_pos(shot_angle);
            
            // vision aiming
            double tx = table->GetNumber("tx", 0.0);
            double Kp = 0.05;
            Drive::getInstance().move(0.0, Kp * tx);
            
        } else if (util::wait(st, 11.0)) {
            // Drive, intake
            if (Manipulator::getInstance().get_note_sensor()) {
                Manipulator::getInstance().intake(0.45);
            } else {
                Manipulator::getInstance().intake(0.0);
            }
            Manipulator::getInstance().shoot(0.0);
            Manipulator::getInstance().arm_to_pos(Manipulator::getInstance().kARM_FLOOR_POS);
            Drive::getInstance().gyro_drive(0.375, -90.0);
            
        } else if (util::wait(st, 12.0)) {
            // Rough turn to angle
            Manipulator::getInstance().intake(0.0);
            Manipulator::getInstance().shoot(0.3);
            Manipulator::getInstance().arm_to_pos(Manipulator::getInstance().kARM_FENDER_POS);
            Drive::getInstance().gyro_drive(0.0, -46.0);
            
        } else if (util::wait(st, 13.5)) {
            // Shoot
            Manipulator::getInstance().intake(0.0);
            Manipulator::getInstance().shoot(1.0);
            
            // Set shot angle
            std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
            double ty = table->GetNumber("ty", 0.0);
            double shot_angle = -0.00008 * pow(ty,2) + .00252*ty + .4992;
            Manipulator::getInstance().arm_to_pos(shot_angle);
            
            // vision aiming
            double tx = table->GetNumber("tx", 0.0);
            double Kp = 0.05;
            Drive::getInstance().move(0.0, Kp * tx);
        
        } else if (util::wait(st, 15)) {
            // Shoot
            Manipulator::getInstance().intake(1.0);
            Manipulator::getInstance().shoot(1.0);
            
            // Set shot angle
            std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
            // double ty = table->GetNumber("ty", 0.0);
            // double shot_angle = -0.00008 * pow(ty,2) + .00252*ty + .4992;
            Manipulator::getInstance().arm_to_pos(0.490);
            
            // vision aiming
            double tx = table->GetNumber("tx", 0.0);
            double Kp = 0.05;
            Drive::getInstance().move(0.0, Kp * tx);
            
        }
        
         else {
            // Finally,
            subsystems::Drive::getInstance().move(0.0, 0.0);  // Stop
            Manipulator::getInstance().intake(0.0);
            Manipulator::getInstance().shoot(0.0);
            Manipulator::getInstance().arm_to_pos(Manipulator::getInstance().kARM_FENDER_POS);
        }
    }
    
} // namespace autonomous
