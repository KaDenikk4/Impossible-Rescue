#**Impossible Rescue**
![](https://toyangreen.com/images/ImpossibleRescue/Preview.jpg)

##**Overview**
**Impossible Rescue** is a 2D single-screen platformer game, inspired by Manic Miner, Impossible Mission, and Shadow Complex Remastered. The game follows a freelance mercenary, ‘Danielle’, and her remote AI assistant <abbr title="Specialist Hard-linked Android for Duty in Offshore Wars">'S.H.A.D.O.W.'</abbr>, on a mission to rescue the President of Earth's daughter from a hidden security installation on Mars. The player must take control of Danielle in order to navigate a series of single-screen, theme-based environments, interacting with various platforms, avoiding/destroying enemies and 'hacking' computers in order to progress from one area to the next. The game was developed by a team of 10 people, consisting of 3 programmers, 3 artists, 2 designers, a producer and a music composer.  The game was built using C++ and the Gamer Camp [GCFramework](https://bitbucket.org/darbotron/gcframework/src/master/ "GCFramework"); a wrapper around Cocos2d-x. CodeWeb [TexturePacker](https://www.codeandweb.com/texturepacker "TexturePacker") and [PhysicsEditor](https://www.codeandweb.com/physicseditor "PhysicsEditor") were used to create spritesheets and physics data. [Ogmo Editor](https://ogmo-editor-3.github.io/ "Ogmo Editor") V2 was used to create the levels. The game runs on a PC, with the use of a Dualshock 4 controller. A video demo can be viewed [here](https://drive.google.com/open?id=1fUhpNCXA-GPNHENtkok3PveHw8dyuWJH "here").

##**Table of Contents**
[TOC]

##**Game Mechanics**

####Player / Companion Mechanics
#####Movement
- Move left, right and jump
- Jump – Single jump with fixed height but the distance can be controlled by holding the left or right button to travel further
- Crouch – For going through small spaces and dodging enemy fire

#####Hacking
- Simple hacking with a progress bar
- The player must hold the ‘hack’ button to fill up the progress bar
- The hacking is completed when the progress bar is filled

#####Weapons/Ammo types
- Primary weapon – disruptor which shoots electric bolts and disables enemies for a short time
- The player has unlimited ammo

#####Health
- The player has 3 lives (health refreshes at the start of every act)
- The player is knocked back and temporarily invincible so they can recover
- Respawn at the start of the level
- No fall damage

#####S.H.A.D.O.W.
- Shadow appears as a series of in-game hints to help guide the player

####Enemy Mechanics
#####Turret
- Dormant – Stationary
- Active low-end – Stationary but shoots (three-round bursts)
- All versions damage the player if touched

####UI
- Blue/White is interactive and Blue/Dark means non-interactive/locked off
- Hacking shows progress bar above the terminal
- Front end and pause menu
- SHADOW hints

####Environment
- Stationary platforms
- Moving platforms
- Lethal environmental hazards

##**Explanation of Role**
This is a series of quick summaries for some of my contributions to the project.

####Level Editor Extension
I added functionality to the framework we used to build the game, to allow the objects placed using the level editor to be more configurable. This helped the designers with game balancing and freed up programmer time.

####Asset Manager
I created an asset manager that is used to preload sound effects to eliminate loading, and then access them from other areas of the codebase.

####Audio System
I also created a simplified audio system interface to be used to play music and sound effects in the game. I then in fact created two audio systems that were usable in the game. There was an issue with the first system as the underlying audio engine, 'SimpleAudioEngine' that it wrapped had a delay issue when playing sounds. The second system used a different audio engine, 'ExperimentalAudioEngine', that did not have any delay issues and was used in the final build.

####Event System
I implemented an event system for the game based on the ‘Mediator’ design pattern. The event system is used to broadcast messages to different parts of the codebase when required. Only objects listening for specific events will use them to execute code. We used events within the code to play audio, to notify when the player had died, to enable/disable things in the game when terminals are hacked, and a variety of other use cases.

####Moving Platform
I added moving platforms to the game. I programmed the platforms to be fully configurable so that the designers could tune and balance them as they see fit. These platforms can move along a path set by the designers in the level editor using a node system. The platforms travel in straight lines between coordinates. The movement speed, and time delay before moving to a new coordinate could also be configured in the level editor. 

####Player Movement
I implemented the player movement in the game. This included basic left and right movement, jumping, crouching, and crouching mid-jump. I also implemented animation and physics changes that occur when the player moves in different ways. For example, when the player transitions from standing to crouching, the player’s collision physics shape is replaced with a smaller physics shape, and the animation graphics are changed.

####Player Shooting
I implemented the player shooting. The player shoots in the direction they are facing, and the height of the bullets from the ground depends if the player is crouching or standing.

####Enemy Turrets
I implemented a stationary burst fire turret. These were also designed to be fully configurable. The firing velocity, number of shots in a burst, the time between bursts, and time between shots in a burst can all be configured for each individual turret within the level editor. Turret projectiles will kill the player on contact. The turret will also rotate itself to face the direction in which it is meant to be firing. I also added the functionality that disabled the turrets if the hacking station they are paired with is successfully hacked.

####Hacking Station
I built upon the code written by [Tomek](#Programming "Tomek's") to enable the hacking stations to broadcast a message when they are successfully hacked. I also added the functionality for an object to respond to said broadcast. Doors can be unlocked, hazards and enemy turrets can be disabled, and disabled moving platforms can be enabled. I also added the hacking progress bar.

####Player Health
I also a health system for the player. The system was built with the original project requirements in mind. It supported the idea of health points, as well as lives. The original idea from the designers was to have a 2-hit health point system, which when depleted, would cause the level to restart and the player would also lose a life. When all lives had been depleted, the player would restart the act. As the scope for the project was cut from three acts to one, the lives system was removed from the game. The health point system was also scrapped and instead, when the player is hit once, the current level will restart. The code for the health system still contains the scrapped extra features.

####Data Persistence
I also implemented data persistence. We did not have a save game option, but we did have the need to persist data between scenes in the game. For example, when we move from one area of a level to another, we need to keep track of how where the player was, how fast the player was moving, and what terminals the player had hacked. This allowed us to do things like jumping between areas and making sure obstacles were still hacked if the player decided to backtrack.

####Environmental Hazards
I created the environmental hazards in the game. There are 2 varieties of environmental hazards in the game. The exposed wiring hazard, the most common in the game, will kill the player on contact. The laser hazard will also kill the player on contact, and it also blocks the player from progressing through the game. The terminal paired with the laser hazard must be hacked in order to disable the hazard.

##**Credits**

####Programming
- Toyan Green :fa-envelope-o: [Email](mailto:toyangreen@gmail.com?subject=Just had a look at Impossible Rescue "Email") :fa-desktop: [Portfolio](https://toyanngreen.com "Portfolio") :fa-linkedin: [LinkedIn](https://uk.linkedIn.com/in/toyangreen "LinkedIn")
- Tomek Snopek :fa-envelope-o: [Email](mailto:tsnopek22@gmail.com?subject=Just had a look at Impossible Rescue "Email")
- Deniss Kaminskis :fa-envelope-o: [Email](mailto:denikk4@inbox.lv?subject=Just had a look at Impossible Rescue "Email")

####Art
- Kenan Wallace :fa-envelope-o: [Email](mailto:kenan.wallace@outlook.com?subject=Just had a look at Impossible Rescue "Email")
- Jamie Warner :fa-envelope-o: [Email](mailto:jamiwarner@sky.com?subject=Just had a look at Impossible Rescue "Email")
- Rylan Taylor :fa-envelope-o: [Email](mailto:rylantaylor@hotmail.co.uk?subject=Just had a look at Impossible Rescue "Email")

####Design
- Dylan Samra :fa-envelope-o: [Email](mailto:dylansamra21@gmail.com?subject=Just had a look at Impossible Rescue "Email")
- Artur Sienkiewicz :fa-envelope-o: [Email](mailto:Artursien99@gmail.com?subject=Just had a look at Impossible Rescue "Email")

####Production
- Luke Hodgetts :fa-envelope-o: [Email](mailto:l.hodgetts24@gmail.com?subject=Just had a look at Impossible Rescue "Email")

####Music Composition
- Benjamin Coulson :fa-envelope-o: [Email](mailto:bengoldencoulsonwork@gmail.com?subject=Just had a look at Impossible Rescue "Email")