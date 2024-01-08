// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>

double currentTimeStamp = 0, lastTimestamp = 0, dt = 0;
double matchTime = 0;

std::string m_autoSelected;


void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption("Basic", "Basic");  
  m_chooser.AddOption("One Note", "OneNote");
  m_chooser.AddOption("Multi Note", "MultiNote");
  
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

  double timeAtTheStart = 0;

bool testinit;

void Robot::AutonomousInit() {
  testinit = true;
  
  m_autoSelected = m_chooser.GetSelected();
  fmt::print("Auto selected: {}\n", m_autoSelected);

  this->basic = new autonomous::Basic();
  this->onenote = new autonomous::OneNote();
  this->multinote = new autonomous::MultiNote();

  timeAtTheStart = currentTimeStamp;
}

void Robot::AutonomousPeriodic() {
  if (testinit) {
    drive->zero_gyro();
    testinit = false;
  }
  
  if (m_autoSelected == "Basic") {
    this->basic->run();
  } else if (m_autoSelected == "OneNote") {
    this->onenote->run();
  } else if (m_autoSelected == "MultiNote") {
    this->multinote->run();
  } else {
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
    manip->getInstance().intake(0.5);
  } else if (xbox->GetLeftBumper()) {
    // Outtake
    manip->getInstance().intake(-1.0);
    manip->getInstance().shoot(-0.25);
  } else {
    // Do nothing
    manip->getInstance().intake(0.0);
    manip->getInstance().shoot(0.0);
  }

  /* Shooter */
  if (xbox->GetRightTriggerAxis() > 0.5) {
    manip->getInstance().shoot(xbox->GetRightTriggerAxis());

    if (xbox->GetRightBumper()) {
      // Run intake despite NOTE being in intake
      manip->getInstance().intake(1.0);
    }
  } else {
    // Do nothing
    // manip->getInstance().intake(0.0);
    manip->getInstance().shoot(0.0);
  }

  /* Arm */
  // Avoid going past 25% power. ABSOLUTE MAXIMUM 50%.
  if (xbox->GetPOV(0) == 0) {
    manip->getInstance().arm(0.25);  // Up
  } else if (xbox->GetPOV(0) == 180) {
    manip->getInstance().arm(-0.25);  // Down
  } else {
    manip->getInstance().arm(0.0);
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