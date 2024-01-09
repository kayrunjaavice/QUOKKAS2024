/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

// 45 13

package frc.robot;

//import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.TimedRobot;
import edu.wpi.first.wpilibj.XboxController;
import edu.wpi.first.wpilibj.drive.DifferentialDrive;
import edu.wpi.first.wpilibj.motorcontrol.MotorControllerGroup;

import com.revrobotics.CANSparkMax;
import com.revrobotics.CANSparkMaxLowLevel.MotorType;

public class Robot extends TimedRobot {

  private static final int leftDrive1 = 3;
  private static final int leftDrive2 = 4;
  private static final int rightDrive1 = 1;
  private static final int rightDrive2 = 2;

  
  private static final int liftMasterID = 5; 
  private static final int liftFollower1ID = 6; 
  private static final int liftFollower2ID = 7;
  private static final int liftFollower3ID = 8;
  private static final int buddyID1 = 9;
  private static final int buddyID2 = 10;



  private CANSparkMax m_leftDrive1;
  private CANSparkMax m_leftDrive2;
  private CANSparkMax m_rightDrive1;
  private CANSparkMax m_rightDrive2;

  private MotorControllerGroup m_leftDrive;
  private MotorControllerGroup m_rightDrive;

  private DifferentialDrive m_Drive;


  private CANSparkMax m_liftMasterMotor;
  private CANSparkMax m_liftFollowerMotor1;
  private CANSparkMax m_liftFollowerMotor2;
  private CANSparkMax m_liftFollowerMotor3;
  private CANSparkMax m_buddyMasterMotor;
  private CANSparkMax m_buddyFollowerMotor;


  private final XboxController driverController = new XboxController(0);

  @Override
  public void robotInit() {
  /**
   * SPARK MAX controllers are intialized over CAN by constructing a CANSparkMax object
   * 
   * The CAN ID, which can be configured using the SPARK MAX Client, is passed as the
   * first parameter
   * 
   * The motor type is passed as the second parameter. Motor type can either be:
   *  com.revrobotics.CANSparkMaxLowLevel.MotorType.kBrushless
   *  com.revrobotics.CANSparkMaxLowLevel.MotorType.kBrushed
   * 
   * The example below initializes four brushless motors with CAN IDs 1 and 2. Change
   * these parameters to match your setup
   */

    m_leftDrive1 = new CANSparkMax(leftDrive1, MotorType.kBrushless);
    m_leftDrive2 = new CANSparkMax(leftDrive2, MotorType.kBrushless);
    m_rightDrive1 = new CANSparkMax(rightDrive1, MotorType.kBrushless);
    m_rightDrive2 = new CANSparkMax(rightDrive2, MotorType.kBrushless);

    m_leftDrive = new MotorControllerGroup(m_leftDrive1, m_leftDrive2);
    m_rightDrive = new MotorControllerGroup(m_rightDrive1, m_rightDrive2);

    m_liftMasterMotor = new CANSparkMax(liftMasterID, MotorType.kBrushed);
    m_liftFollowerMotor1 = new CANSparkMax(liftFollower1ID, MotorType.kBrushed);
    m_liftFollowerMotor2 = new CANSparkMax(liftFollower2ID, MotorType.kBrushed);
    m_liftFollowerMotor3 = new CANSparkMax(liftFollower3ID, MotorType.kBrushed);
    m_buddyMasterMotor = new CANSparkMax(buddyID1, MotorType.kBrushed);
    m_buddyFollowerMotor = new CANSparkMax(buddyID2, MotorType.kBrushed);

    m_Drive = new DifferentialDrive(m_leftDrive, m_rightDrive);


    /**
     * The RestoreFactoryDefaults method can be used to reset the configuration parameters
     * in the SPARK MAX to their factory default state. If no argument is passed, these
     * parameters will not persist between power cycles
     */
    m_liftMasterMotor.restoreFactoryDefaults();
    m_liftFollowerMotor1.restoreFactoryDefaults();
    m_liftFollowerMotor2.restoreFactoryDefaults();
    m_liftFollowerMotor3.restoreFactoryDefaults();
    m_buddyMasterMotor.restoreFactoryDefaults();
    m_buddyFollowerMotor.restoreFactoryDefaults();

    m_leftDrive1.restoreFactoryDefaults();
    m_leftDrive2.restoreFactoryDefaults();
    m_rightDrive1.restoreFactoryDefaults();
    m_rightDrive2.restoreFactoryDefaults();

    m_liftFollowerMotor1.follow(m_liftMasterMotor);
    m_liftFollowerMotor2.follow(m_liftMasterMotor);
    m_liftFollowerMotor3.follow(m_liftMasterMotor);

    m_buddyFollowerMotor.follow(m_buddyMasterMotor);


  }

  @Override
  public void teleopPeriodic() {
    m_Drive.tankDrive(driverController.getLeftY(), driverController.getRightY());

    // BUTTON A: BUDDY GRABBER
    if (driverController.getAButtonPressed()) { 
      m_buddyMasterMotor.set(0.1);
    } else if (driverController.getAButtonReleased()) {
      m_buddyMasterMotor.set(0);

    // BUTTON B: CLIMBER ELEVATOR
    } else if (driverController.getBButtonPressed()) {
      m_liftMasterMotor.set(0.1);
    } else if (driverController.getBButtonReleased()) {
      m_liftMasterMotor.set(0);
    }
  }
}
