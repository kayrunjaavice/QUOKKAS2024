// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

double currentTimeStamp = 0, lastTimestamp = 0, dt = 0;
double matchTime = 0;

std::string m_autoSelected;


void Robot::RobotInit() {  
  this->curr_arm_target = manip->getInstance().kARM_START_POS;
  
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption("Basic", "Basic");  
  m_chooser.AddOption("Multi Note", "MultiNote");
  m_chooser.AddOption("Send It", "SendIt");
  
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  xbox = new frc::XboxController(0);
}

/**
 * This function is called every 20 ms, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  matchTime = (double)frc::Timer::GetMatchTime();
  currentTimeStamp = (double)frc::Timer::GetFPGATimestamp();
  dt = currentTimeStamp - lastTimestamp;

  lastTimestamp = currentTimeStamp;
}

bool testinit;

void Robot::AutonomousInit() {
  testinit = true;
  
  m_autoSelected = m_chooser.GetSelected();
  fmt::print("Auto selected: {}\n", m_autoSelected);

  this->basic = new autonomous::Basic();
  this->multinote = new autonomous::MultiNote();
  this->sendit = new autonomous::SendIt();
}

void Robot::AutonomousPeriodic() {
  if (testinit) {
    // drive->zero_gyro();
    testinit = false;
  }
  
  if (m_autoSelected == "Basic") {
    this->basic->run();
  } else if (m_autoSelected == "MultiNote") {
    this->multinote->run();
  } else if (m_autoSelected == "SendIt") {
    this->sendit->run();
  }
  
  else {
    this->basic->run();
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {  
  /* Drive */
  double power = -xbox->GetRawAxis(1);     // 1 -- Left Y Axis
  double steering = xbox->GetRawAxis(4);  // 4 -- Rght X Axis
  
  drive->getInstance().move(power, steering);
  
  /* Intake */
  if (xbox->GetRightBumper() && manip->getInstance().get_note_sensor()) {
    // If pressing intake button, and the NOTE is not in the intake
    manip->getInstance().intake(0.375);
    if (xbox->GetRightTriggerAxis() < 0.5) {
      this->curr_arm_target = manip->getInstance().kARM_FLOOR_POS;
    }
  } else if (xbox->GetLeftBumper()) {
    // Outtake
    manip->getInstance().intake(-1.0);
    manip->getInstance().shoot(-0.25);
  } else {
    // Do nothing
    manip->getInstance().intake(0.0);
    manip->getInstance().shoot(0.0);
  }

  if (xbox->GetRightBumper() && !manip->getInstance().get_note_sensor()) {
    // If pressing intake and NOTE is in the intake
    xbox->SetRumble(frc::GenericHID::kBothRumble, 1.0);
  } else {
    xbox->SetRumble(frc::GenericHID::kBothRumble, 0.0);
  }

  if (xbox->GetRightBumperReleased()) {
    // No longer intaking; raise intake to avoid damage
    this->curr_arm_target = manip->getInstance().kARM_FENDER_POS;
  }

  /* Shooter */
  if (xbox->GetRightTriggerAxis() > 0.1) {
    if (manip->getInstance().get_arm_enc() < manip->getInstance().kARM_START_POS) {
      // If arm turned back farther than starting config
      manip->getInstance().shoot(0.25);
    } else {
      // High goal shooting
      // Set shot angle
      // std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
      // double ty = table->GetNumber("ty", 0.0);
      // double shot_angle = -0.00008 * pow(ty,2) + .00252*ty + .4992;
      // this->curr_arm_target = shot_angle;
    }

    // vision aiming
    std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    double tx = table->GetNumber("tx", 0.0);
    double Kp = 0.05;
    drive->getInstance().move(power, Kp * tx);
    frc::SmartDashboard::PutNumber("tx", tx);
  }

  if (xbox->GetRightTriggerAxis() > 0.5) {
    if (manip->getInstance().get_arm_enc() < manip->getInstance().kARM_START_POS) {
      // If arm turned back farther than starting config, score AMP
      manip->getInstance().intake(1.0);
      manip->getInstance().shoot(0.5);
    } else {
      // High goal shooting
      // Adjustable by driver. 50% press => 0% power, 100% press => 100% power
      manip->getInstance().shoot((xbox->GetRightTriggerAxis() - 0.5) * 2);
    }

    if (xbox->GetRightBumper()) {
      // Run intake despite NOTE being in intake
      manip->getInstance().intake(1.0);
    }
  } else {
    // Do nothing
    // manip->getInstance().intake(0.0);
    manip->getInstance().shoot(0.0);
  }

  /* Arm manual control */
  if (xbox->GetYButtonPressed()) {
    // Amp scoring config
    this->curr_arm_target = this->manip->getInstance().kARM_AMP_POS;
  }

  if (xbox->GetPOV(0) == 0) {
    manip->getInstance().move_arm(0.5);  // Up
    this->curr_arm_target = this->manip->getInstance().get_arm_enc();
  } else if (xbox->GetPOV(0) == 180) {
    manip->getInstance().move_arm(-0.5);  // Down
    this->curr_arm_target = this->manip->getInstance().get_arm_enc();
  } else {
    // Move arm to preset target, or current position if last command was manual control.
    manip->getInstance().arm_to_pos(curr_arm_target);
  }

  frc::SmartDashboard::PutNumber("Arm", manip->getInstance().get_arm_enc());
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif