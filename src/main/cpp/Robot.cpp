// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include "autonomous/autonomous.hpp"
#include "subsystems/Drive.hpp"

#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>

double currentTimeStamp = 0, lastTimestamp = 0, dt = 0;
double matchTime = 0;


void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  driver = new frc::XboxController(0);


}

/**
 * This function is called every 20 ms, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {matchTime = (double)frc::Timer::GetMatchTime();
  currentTimeStamp = (double)frc::Timer::GetFPGATimestamp();
  dt = currentTimeStamp - lastTimestamp;

  lastTimestamp = currentTimeStamp;}

  double timeAtTheStart = 0;

void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  fmt::print("Auto selected: {}\n", m_autoSelected);

  timeAtTheStart = currentTimeStamp;

  if (m_autoSelected == kAutoNameCustom) {
    autonomous::Basic::run();
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {

  L2->Set(-driver->GetLeftY());
  R2->Set(driver->GetRightY());
  L1->Set(-driver->GetLeftY());
  R1->Set(driver->GetRightY());

  M1->Set(driver->GetLeftTriggerAxis());
  M1->Set((driver->GetLeftBumper() == 1) ? -0.2 : 0);

  M2->Set(driver->GetRightTriggerAxis());
  M2->Set((driver->GetRightBumper() == 1) ? -0.2 : 0);
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