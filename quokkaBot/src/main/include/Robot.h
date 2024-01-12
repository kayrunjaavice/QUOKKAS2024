// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <string>
#include <iostream>
#include <fmt/core.h>

#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/XboxController.h>
#include <ctre/phoenix.h>
#include <frc/Timer.h>

#include "../cpp/autonomous/autonomous.hpp"
#include "../cpp/subsystems/subsystems.hpp"

class Robot : public frc::TimedRobot {
public:
void RobotInit() override;
void RobotPeriodic() override;
void AutonomousInit() override;
void AutonomousPeriodic() override;
void TeleopInit() override;
void TeleopPeriodic() override;
void DisabledInit() override;
void DisabledPeriodic() override;
void TestInit() override;
void TestPeriodic() override;

private:
frc::SendableChooser<std::string> m_chooser;
const std::string kAutoNameDefault = "Default";
const std::string kAutoNameCustom = "My Auto";
std::string m_autoSelected;
//drivebase motors
//xbox controllers
frc::XboxController *xbox;
//frc::XboxController *codriver;
//timer we're going to use for autonomous
frc::Timer autoTimer;
//variables used within the program

/* Mechanisms */
subsystems::Drive *drive;
subsystems::Manipulator *manip;

double curr_arm_target;

/* Autonomous Modes */
autonomous::Basic *basic;
autonomous::MultiNote *multinote;
autonomous::SendIt *sendit;

const int DRIVE_L1_ID = 3;
const int DRIVE_L2_ID = 4;
const int DRIVE_R1_ID = 1;
const int DRIVE_R2_ID = 2;

const int INTAKE_ID = 5;
const int SHOOTER_ID = 6;

const int ARM_L_ID = 7;
const int ARM_R_ID = 8;
};