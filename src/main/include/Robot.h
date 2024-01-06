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
//TalonSRX motor controllers for the arm and gripper
WPI_TalonSRX *R1, *R2;
WPI_TalonSRX *L1, *L2;
WPI_VictorSPX *M1, *M2;
//drivebase motors
//xbox controllers
frc::XboxController *driver;
//frc::XboxController *codriver;
//timer we're going to use for autonomous
frc::Timer autoTimer;
//variables used within the program
};