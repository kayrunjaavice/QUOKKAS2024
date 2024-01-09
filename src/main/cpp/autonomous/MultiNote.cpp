#include "MultiNote.hpp"
#include <frc/smartdashboard/SmartDashboard.h>
#include "../util/util.hpp"

namespace autonomous
{
    double st;  // start time
    
    MultiNote::MultiNote() {
        st = frc::GetTime().value();
        frc::SmartDashboard::PutNumber("start time", st);
    }
    
    void MultiNote::run() {
        using namespace subsystems;

        frc::SmartDashboard::PutNumber("time", frc::GetTime().value());
        if (util::wait(st, 2)) {
            // Lower arm
            Manipulator::getInstance().shoot(0.5);
            Manipulator::getInstance().arm_to_pos(Manipulator::getInstance().kARM_FENDER_POS);
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
            // Drive back
            Manipulator::getInstance().intake(0.0);
            Manipulator::getInstance().shoot(0.5);
            Manipulator::getInstance().arm_to_pos(Manipulator::getInstance().kARM_FENDER_POS);
            Drive::getInstance().gyro_drive(-0.5, 0.0);
        } else if (util::wait(st, 9.0)) {
            // Drive back
            Manipulator::getInstance().intake(1.0);
            Manipulator::getInstance().shoot(0.5);
            Manipulator::getInstance().arm_to_pos(Manipulator::getInstance().kARM_FENDER_POS);
            Drive::getInstance().gyro_drive(0.0, 0.0);
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
