// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include "autonomous/autonomous.hpp"
#include "subsystems/subsystems.hpp"

#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>

double currentTimeStamp = 0, lastTimestamp = 0, dt = 0;
double matchTime = 0;


void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
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
    autonomous::Basic basic;
    basic.run();
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
  /* Drive */
  double power = xbox->GetRawAxis(1);     // 1 -- Left Y Axis
  double steering = xbox->GetRawAxis(4);  // 4 -- Rght X Axis
  
  this->drive->move(power, steering);

  /* Intake */
  if (xbox->GetRightBumper() && !this->manip->get_note_sensor()) {
    // If pressing intake button, and the NOTE is not in the intake
    this->manip->intake(1.0);
  } else if (xbox->GetLeftBumper()) {
    // Outtake
    this->manip->intake(-1.0);
    this->manip->shoot(-0.25);
  } else {
    // Do nothing
    this->manip->intake(0.0);
    this->manip->shoot(0.0);
  }

  /* Shooter */
  if (xbox->GetRightTriggerAxis() > 0.5) {
    this->manip->shoot(xbox->GetRightTriggerAxis());

    if (xbox->GetRightBumper()) {
      // Run intake despite NOTE being in intake
      this->manip->intake(1.0);
    }
  } else {
    // Do nothing
    this->manip->intake(0.0);
    this->manip->shoot(0.0);
  }

  /* Arm */
  if (xbox->GetPOV(0)) {
    this->manip->arm(0.1);  // Up
  } else if (xbox->GetPOV(180)) {
    this->manip->arm(-0.1);  // Down
  }
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