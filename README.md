# **Impossible Rescue**
![](https://github.com/KaDenikk4/Impossible-Rescue/raw/master/Images/Preview.jpg)

## **Overview**
**Impossible Rescue** is a 2D single-screen platformer game, inspired by Manic Miner, Impossible Mission, and Shadow Complex Remastered. The game follows a freelance mercenary, ‘Danielle’, and her remote AI assistant <abbr title="Specialist Hard-linked Android for Duty in Offshore Wars">'S.H.A.D.O.W.'</abbr>, on a mission to rescue the President of Earth's daughter from a hidden security installation on Mars. The player must take control of Danielle in order to navigate a series of single-screen, theme-based environments, interacting with various platforms, avoiding/destroying enemies and 'hacking' computers in order to progress from one area to the next. The game was developed by a team of 10 people, consisting of 3 programmers, 3 artists, 2 designers, a producer and a music composer.  The game was built using C++ and the Gamer Camp [GCFramework](https://bitbucket.org/darbotron/gcframework/src/master/ "GCFramework"); a wrapper around Cocos2d-x. CodeWeb [TexturePacker](https://www.codeandweb.com/texturepacker "TexturePacker") and [PhysicsEditor](https://www.codeandweb.com/physicseditor "PhysicsEditor") were used to create spritesheets and physics data. [Ogmo Editor](https://ogmo-editor-3.github.io/ "Ogmo Editor") V2 was used to create the levels. The game runs on a PC, with the use of a Dualshock 4 controller. A video demo can be viewed [here](https://drive.google.com/open?id=1fUhpNCXA-GPNHENtkok3PveHw8dyuWJH "here").

## **Table of Contents**
- [**Impossible Rescue**](#impossible-rescue)
  * [**Overview**](#overview)
  * [**Table of Contents**](#table-of-contents)
  * [**Game Mechanics**](#game-mechanics)
      - [Player Mechanics](#player-mechanics)
        * [Movement](#movement)
        * [Hacking](#hacking)
        * [Weapons](#weapons)
        * [Health](#health)
        * [S.H.A.D.O.W.](#shadow)
      - [Enemy Mechanics](#enemy-mechanics)
        * [Turret](#turret)
      - [UI](#ui)
      - [Environment](#environment)
  * [**Explanation of Role**](#explanation-of-role)
  * [**Credits**](#credits)
      - [Programming](#programming)
      - [Art](#art)
      - [Design](#design)
      - [Production](#production)
      - [Music Composition](#music-composition)
   * [**Code Attribution Table**](#code-attribution-table)
      
## **Game Mechanics**

#### Player Mechanics
##### Movement
- Move left, right and jump
- Jump – Single jump with fixed height but the distance can be controlled by holding the left or right button to travel further
- Crouch – For going through small spaces and dodging enemy fire

##### Hacking
- Simple hacking with a progress bar
- The player must hold the ‘hack’ button to fill up the progress bar
- The hacking is completed when the progress bar is filled

##### Weapons
- Primary weapon – disruptor gun which shoots electric bolts and disables enemies for a short time
- The player has unlimited ammo

##### Health
- The player has 3 lives (health refreshes at the start of every act)
- The player is knocked back and temporarily invincible so they can recover
- Respawn at the start of the level
- No fall damage

##### S.H.A.D.O.W.
- Shadow appears as a series of in-game hints to help guide the player

#### Enemy Mechanics
##### Turret
- Dormant – Stationary
- Active low-end – Stationary but shoots (three-round bursts)
- All versions damage the player if touched

#### UI
- Blue/White is interactive and Blue/Dark means non-interactive/locked off
- Hacking shows progress bar above the terminal
- Front end and pause menu
- SHADOW hints

#### Environment
- Stationary platforms
- Moving platforms
- Lethal environmental hazards

## **Explanation of Role**
Within the team, I took the role of a programmer. I wrote code to implement features that the designers created and refined. This is a series of quick summaries for some of my contributions to the project. Full breakdown of code contributions can been found in the [code attribution table](#code-attribution-table)

My main task during this module was related to the UI of the player. I was working on the main menu and pause menu, also tutorial and player health. I also was working with sound effects, player and levels.

## **Credits**

#### Programming
- Toyan Green :computer: [Email](mailto:toyangreen@gmail.com?subject=Just+had+a+look+at+Impossible+Rescue "Email") [Portfolio](https://toyanngreen.com "Portfolio") [LinkedIn](https://uk.linkedIn.com/in/toyangreen "LinkedIn")
- Tomek Snopek :computer: [Email](mailto:tsnopek22@gmail.com?subject=Just+had+a+look+at+Impossible+Rescue "Email")
- Deniss Kaminskis :computer: [Email](mailto:denikk4@inbox.lv?subject=Just+had+a+look+at+Impossible+Rescue "Email") [Portfolio](https://ksdeniss.com/projects/ "Portfolio") [LinkedIn](https://www.linkedin.com/in/deniss-kaminskis-a3a64518b/ "LinkedIn")

#### Art
- Kenan Wallace :art: [Email](mailto:kenan.wallace@outlook.com?subject=Just+had+a+look+at+Impossible+Rescue "Email")
- Jamie Warner :art: [Email](mailto:jamiwarner@sky.com?subject=Just+had+a+look+at+Impossible+Rescue "Email")
- Rylan Taylor :art: [Email](mailto:rylantaylor@hotmail.co.uk?subject=Just+had+a+look+at+Impossible+Rescue "Email")

#### Design
- Dylan Samra :bulb: [Email](mailto:dylansamra21@gmail.com?subject=Just+had+a+look+at+Impossible+Rescue "Email")
- Artur Sienkiewicz :bulb: [Email](mailto:Artursien99@gmail.com?subject=Just+had+a+look+at+Impossible+Rescue "Email")

#### Production
- Luke Hodgetts :bar_chart: [Email](mailto:l.hodgetts24@gmail.com?subject=Just+had+a+look+at+Impossible+Rescue "Email")

#### Music Composition
- Benjamin Coulson :musical_score: [Email](mailto:bengoldencoulsonwork@gmail.com?subject=Just+had+a+look+at+Impossible+Rescue "Email")

## **Code Attribution Table**

| Key     |                                      |
|---------|--------------------------------------|
| (Blank) | No Modification                      |
| N/A     | Not Applicable (for redundant files) |
| L       | Lightly Modified                     |
| M       | Medium Modification                  |
| H       | Heavily Modified                     |
| S       | Sole Author                          |

| Source Files ( .h and .cpp )               | Deniss Kaminskis | Tomek Snopek | Toyan Green |
|--------------------------------------------|------------------|--------------|-------------|
| CAssetManager.cpp                          | (Blank)          | (Blank)      | S           |
| CAssetManager.h                            | (Blank)          | (Blank)      | S           |
| IAssetManager.h                            | M                | M            | H           |
| CAudioSystem.cpp                           | (Blank)          | (Blank)      | S           |
| CAudioSystem.h                             | (Blank)          | (Blank)      | S           |
| CExperimentalAudioSystem.cpp               | (Blank)          | L            | H           |
| CExperimentalAudioSystem.h                 | (Blank)          | (Blank)      | S           |
| CSoundEffect.cpp                           | (Blank)          | (Blank)      | S           |
| CSoundEffect.h                             | (Blank)          | (Blank)      | S           |
| ESoundFX.h                                 | L                | M            | H           |
| IAudioSystem.h                             | (Blank)          | (Blank)      | S           |
| ISoundEffect.h                             | (Blank)          | (Blank)      | S           |
| CCinematicScene.cpp                        | L                | H            | L           |
| CCinematicScene.h                          | (Blank)          | S            | (Blank)     |
| CTitleScreen.cpp                           | (Blank)          | S            | (Blank)     |
| CTitleScreen.h                             | (Blank)          | S            | (Blank)     |
| CTurret.cpp                                | (Blank)          | H            | H           |
| CTurret.h                                  | (Blank)          | H            | H           |
| CTurretProjectile.cpp                      | (Blank)          | L            | H           |
| CTurretProjectile.h                        | (Blank)          | (Blank)      | S           |
| CTurretProjectileGroup.cpp                 | (Blank)          | (Blank)      | S           |
| CTurretProjectileGroup.h                   | (Blank)          | (Blank)      | S           |
| CDoor.cpp                                  | (Blank)          | H            | H           |
| CDoor.h                                    | (Blank)          | H            | M           |
| CHazardCables2m.cpp                        | (Blank)          | (Blank)      | S           |
| CHazardCables2m.h                          | (Blank)          | (Blank)      | S           |
| CHazardCables3m.cpp                        | (Blank)          | (Blank)      | S           |
| CHazardCables3m.h                          | (Blank)          | (Blank)      | S           |
| CVerticalHazard.cpp                        | (Blank)          | (Blank)      | S           |
| CVerticalHazard.h                          | (Blank)          | (Blank)      | S           |
| CHorizontalLevelTransitionBorder.cpp       | (Blank)          | (Blank)      | S           |
| CHorizontalLevelTransitionBorder.h         | (Blank)          | (Blank)      | S           |
| CVerticalLevelTransitionBorder.cpp         | (Blank)          | (Blank)      | S           |
| CVerticalLevelTransitionBorder.h           | (Blank)          | (Blank)      | S           |
| CMovingPlatform.cpp                        | (Blank)          | (Blank)      | S           |
| CMovingPlatform.h                          | (Blank)          | L            | H           |
| CMovingPlatform3m.cpp                      | (Blank)          | H            | H           |
| CMovingPlatform3m.h                        | (Blank)          | H            | H           |
| CStandardPlatform5m.cpp                    | (Blank)          | L            | H           |
| CStandardPlatform5m.h                      | (Blank)          | (Blank)      | S           |
| CWallPlatform3m.cpp                        | (Blank)          | L            | H           |
| CWallPlatform3m.h                          | (Blank)          | L            | H           |
| CWallPlatform3mLeft.cpp                    | (Blank)          | S            | (Blank)     |
| CWallPlatform3mLeft.h                      | (Blank)          | S            | (Blank)     |
| CWallPlatform3mRight.cpp                   | (Blank)          | S            | (Blank)     |
| CWallPlatform3mRight.h                     | (Blank)          | S            | (Blank)     |
| CWallPlatform4m.cpp                        | (Blank)          | L            | H           |
| CWallPlatform4m.h                          | (Blank)          | L            | H           |
| CWallPlatform4mLeft.cpp                    | (Blank)          | S            | (Blank)     |
| CWallPlatform4mLeft.h                      | (Blank)          | S            | (Blank)     |
| CWallPlatform4mRight.cpp                   | (Blank)          | S            | (Blank)     |
| CWallPlatform4mRight.h                     | (Blank)          | S            | (Blank)     |
| CWallPlatform5m.cpp                        | (Blank)          | L            | H           |
| CWallPlatform5m.h                          | (Blank)          | (Blank)      | S           |
| CWallPlatform5mLeft.cpp                    | (Blank)          | S            | (Blank)     |
| CWallPlatform5mLeft.h                      | (Blank)          | S            | (Blank)     |
| CWallPlatform5mMid.cpp                     | (Blank)          | S            | (Blank)     |
| CWallPlatform5mMid.h                       | (Blank)          | S            | (Blank)     |
| CWallPlatform5mRight.cpp                   | (Blank)          | S            | (Blank)     |
| CWallPlatform5mRight.h                     | (Blank)          | S            | (Blank)     |
| CCeiling.cpp                               | (Blank)          | H            | M           |
| CCeiling.h                                 | (Blank)          | H            | M           |
| CFloor.cpp                                 | (Blank)          | H            | M           |
| CFloor.h                                   | (Blank)          | H            | M           |
| CLeftWall.cpp                              | (Blank)          | H            | M           |
| CLeftWall.h                                | (Blank)          | H            | M           |
| CRightWall.cpp                             | (Blank)          | H            | M           |
| CRightWall.h                               | (Blank)          | H            | M           |
| CWall5M.cpp                                | (Blank)          | L            | H           |
| CWall5M.h                                  | (Blank)          | L            | H           |
| CContainersAsset.cpp                       | (Blank)          | H            | M           |
| CContainersAsset.h                         | (Blank)          | H            | M           |
| CGamePausedEvent.h                         | (Blank)          | (Blank)      | S           |
| CGameResumedEvent.h                        | (Blank)          | (Blank)      | S           |
| CLevelTransitionEvent.h                    | (Blank)          | (Blank)      | S           |
| CPlayBackgroundMusicEvent.h                | (Blank)          | (Blank)      | S           |
| CPlayerHasDiedEvent.h                      | (Blank)          | (Blank)      | S           |
| CStationHackedEvent.h                      | (Blank)          | (Blank)      | S           |
| CActionOnRelease.cpp                       | (Blank)          | (Blank)      | S           |
| CActionOnRelease.h                         | (Blank)          | (Blank)      | S           |
| CEventMediator.cpp                         | (Blank)          | (Blank)      | S           |
| CEventMediator.h                           | (Blank)          | (Blank)      | S           |
| IEventMediator.h                           | (Blank)          | (Blank)      | S           |
| IEventPublisher.h                          | (Blank)          | (Blank)      | S           |
| IEventSource.h                             | (Blank)          | (Blank)      | S           |
| ITReceiveEvents.h                          | (Blank)          | (Blank)      | S           |
| TNotificationChannel.h                     | (Blank)          | (Blank)      | S           |
| CHackingStation.cpp                        | (Blank)          | H            | H           |
| CHackingStation.h                          | (Blank)          | H            | H           |
| CLevelTimer.cpp                            | M                | H            | L           |
| CLevelTimer.h                              | L                | H            | L           |
| IHackable.h                                | (Blank)          | (Blank)      | S           |
| CLevel1Area1.cpp                           | H                | L            | H           |
| CLevel1Area1.h                             | H                | L            | H           |
| CLevel1Area2.cpp                           | H                | L            | H           |
| CLevel1Area2.h                             | H                | L            | H           |
| CLevel2Area1.cpp                           | H                | H            | H           |
| CLevel2Area1.h                             | H                | H            | H           |
| CLevel2Area2.cpp                           | (Blank)          | H            | L           |
| CLevel2Area2.h                             | (Blank)          | H            | L           |
| CLevel3Area1.cpp                           | H                | H            | L           |
| CLevel3Area1.h                             | H                | H            | L           |
| CLevel3Area2.cpp                           | (Blank)          | H            | L           |
| CLevel3Area2.h                             | (Blank)          | H            | L           |
| CLevel4Area1.cpp                           | L                | M            | H           |
| CLevel4Area1.h                             | L                | L            | H           |
| CLevel4Area2.cpp                           | L                | M            | H           |
| CLevel4Area2.h                             | L                | L            | H           |
| CBaseLevel.cpp                             | H                | H            | H           |
| CBaseLevel.h                               | H                | H            | H           |
| CEndScreen.cpp                             | (Blank)          | S            | (Blank)     |
| CEndScreen.h                               | (Blank)          | S            | (Blank)     |
| CMenuScene.cpp                             | H                | L            | M           |
| CMenuScene.h                               | H                | L            | L           |
| CTemplateLevel.cpp                         | S                | (Blank)      | (Blank)     |
| CTemplateLevel.h                           | S                | (Blank)      | (Blank)     |
| ELevelTransitionType.h                     | (Blank)          | (Blank)      | S           |
| SPhysicsObjectUserData.cpp                 | (Blank)          | (Blank)      | S           |
| SPhysicsObjectUserData.h                   | (Blank)          | (Blank)      | S           |
| CPlayerPrimaryProjectile.cpp               | (Blank)          | M            | H           |
| CPlayerPrimaryProjectile.h                 | (Blank)          | L            | H           |
| CPlayerPrimaryProjectileGroup.cpp          | (Blank)          | (Blank)      | S           |
| CPlayerPrimaryProjectileGroup.h            | (Blank)          | (Blank)      | S           |
| CPrimaryShootingPlayerEquipmentState.cpp   | (Blank)          | L            | H           |
| CPrimaryShootingPlayerEquipmentState.h     | (Blank)          | L            | H           |
| CPlayerSecondaryProjectile.cpp             | (Blank)          | M            | H           |
| CPlayerSecondaryProjectile.h               | (Blank)          | M            | H           |
| CPlayerSecondaryProjectileGroup.cpp        | (Blank)          | (Blank)      | S           |
| CPlayerSecondaryProjectileGroup.h          | (Blank)          | (Blank)      | S           |
| CSecondaryShootingPlayerEquipmentState.cpp | (Blank)          | M            | H           |
| CSecondaryShootingPlayerEquipmentState.h   | (Blank)          | L            | H           |
| CPlayerEquipmentState.h                    | (Blank)          | L            | H           |
| CPlayerEquipmentStates.cpp                 | (Blank)          | (Blank)      | S           |
| CPlayerEquipmentStates.h                   | (Blank)          | (Blank)      | S           |
| CPlayerHealth.cpp                          | (Blank)          | L            | H           |
| CPlayerHealth.h                            | (Blank)          | L            | H           |
| CCrouchingPlayerMovementState.cpp          | L                | L            | H           |
| CCrouchingPlayerMovementState.h            | L                | (Blank)      | H           |
| CDoubleJumpingPlayerMovementState.cpp      | (Blank)          | (Blank)      | S           |
| CDoubleJumpingPlayerMovementState.h        | (Blank)          | (Blank)      | S           |
| CIdleCrouchingPlayerMovementState.cpp      | (Blank)          | (Blank)      | S           |
| CIdleCrouchingPlayerMovementState.h        | (Blank)          | (Blank)      | S           |
| CIdleStandingPlayerMovementState.cpp       | (Blank)          | L            | H           |
| CIdleStandingPlayerMovementState.h         | (Blank)          | (Blank)      | S           |
| CJumpingPlayerMovementState.cpp            | L                | L            | H           |
| CJumpingPlayerMovementState.h              | L                | (Blank)      | H           |
| CJumpingCrouchPlayerMovementState.cpp      | L                | L            | H           |
| CJumpingCrouchPlayerMovementState.h        | L                | (Blank)      | H           |
| CJumpingWalkPlayerMovementState.cpp        | (Blank)          | L            | H           |
| CJumpingWalkPlayerMovementState.h          | (Blank)          | (Blank)      | S           |
| CWalkingPlayerMovementState.cpp            | L                | L            | H           |
| CWalkingPlayerMovementState.h              | L                | (Blank)      | H           |
| CPlayerMovementState.cpp                   | (Blank)          | L            | H           |
| CPlayerMovementState.h                     | L                | L            | H           |
| CPlayerMovementStates.h                    | (Blank)          | (Blank)      | S           |
| CPlayerLevelTransitionData.cpp             | (Blank)          | M            | H           |
| CPlayerLevelTransitionData.h               | (Blank)          | M            | H           |
| CPlayerData.cpp                            | (Blank)          | L            | H           |
| CPlayerData.h                              | (Blank)          | L            | H           |
| CPlayerDataManager.cpp                     | (Blank)          | L            | H           |
| CPlayerDataManager.h                       | (Blank)          | (Blank)      | S           |
| CPlayer.cpp                                | L                | M            | H           |
| CPlayer.h                                  | L                | L            | H           |
| EPlayerActions.h                           | (Blank)          | (Blank)      | S           |
| EPlayerCutsceneActions.h                   | (Blank)          | S            | (Blank)     |
| CShadow.cpp                                | (Blank)          | H            | L           |
| CShadow.h                                  | (Blank)          | S            | (Blank)     |
| CButton.cpp                                | S                | (Blank)      | (Blank)     |
| CButton.h                                  | S                | (Blank)      | (Blank)     |
| CHealth_UI.cpp                             | S                | (Blank)      | (Blank)     |
| CHealth_UI.h                               | S                | (Blank)      | (Blank)     |
| EPlayerMenuActions.h                       | S                | (Blank)      | (Blank)     |
| TickerText.cpp                             | H                | L            | L           |
| TickerText.h                               | S                | (Blank)      | (Blank)     |
| CHelperFunctions.h                         | (Blank)          | (Blank)      | S           |
| CLabelHelper.cpp                           | (Blank)          | S            | (Blank)     |
| CLabelHelper.h                             | (Blank)          | S            | (Blank)     |
| CTimerHelper.cpp                           | (Blank)          | S            | (Blank)     |
| CTimerHelper.h                             | (Blank)          | S            | (Blank)     |
| GCLevelLoader_Ogmo.cpp                     | (Blank)          | L            | L           |
| GCObjSprite.cpp                            | (Blank)          | (Blank)      | L           |
| GCObjSprite.h                              | (Blank)          | L            | (Blank)     |
| GCObjSpritePhysics.cpp                     | (Blank)          | L            | L           |
| GCObjSpritePhysics.h                       | (Blank)          | (Blank)      | L           |
| IGCGameLayer.cpp                           | (Blank)          | (Blank)      | L           |
| SGCFactoryCreationParams.h                 | (Blank)          | M            | M           |
| AppDelegate.cpp                            | (Blank)          | L            | H           |
| AppDelegate.h                              | (Blank)          | (Blank)      | H           |
| AppMacros.h                                | (Blank)          | (Blank)      | L           |
| CHackingState.h                            | (Blank)          | S            | (Blank)     |
| CHackingState.cpp                          | (Blank)          | S            | (Blank)     |
