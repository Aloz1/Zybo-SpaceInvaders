/*
 * Sprites.cpp
 *
 *  Created on: 20May,2018
 *      Author: alastair
 */

/*
 * Header files (wrapped in namespaces to avoid name collisions)
 */

#include "Sprite.h"

// Include all Gimp image headers. All headers have identical identifiers, so
// they are included into their own namespace to prevent name collitions. It
// may be possible to simplify this using macro black magic.
namespace Player_H {
	#include "images/PLAYER.h"
}
namespace Player_Laser_H     {
	#include "images/LAS_PLAYER.h"
}
namespace Player_Explode_1_H {
	#include "images/EXP_1.h"
}
namespace Player_Explode_2_H {
	#include "images/EXP_2.h"
}
namespace Shield_H           {
	#include "images/SHIELD.h"
}
namespace Invader_L1_H       {
	#include "images/INV_LRG_1.h"
}
namespace Invader_L2_H       {
	#include "images/INV_LRG_2.h"
}
namespace Invader_M1_H       {
	#include "images/INV_MED_1.h"
}
namespace Invader_M2_H       {
	#include "images/INV_MED_2.h"
}
namespace Invader_S1_H       {
	#include "images/INV_SML_1.h"
}
namespace Invader_S2_H       {
	#include "images/INV_SML_2.h"
}
namespace Invader_Laser_S1_H {
	#include "images/INV_LAS_1.h"
}
namespace Invader_Laser_S2_H {
	#include "images/INV_LAS_2.h"
}
namespace Invader_Laser_L1_H {
	#include "images/INV_LAS_3.h"
}
namespace Invader_Laser_L2_H {
	#include "images/INV_LAS_4.h"
}
namespace Invader_UFO_H      {
	#include "images/UFO.h"
}
namespace Invader_Explode_H  {
	#include "images/INV_DEATH.h"
}

/*
 * Static instantiations of each sprite. These use the namespaces specified above.
 */
Sprite playerSprite(Player_H::width, Player_H::height, Player_H::header_data);
Sprite playerLaserSprite(Player_Laser_H::width, Player_Laser_H::height, Player_Laser_H::header_data);
Sprite playerExplode1Sprite(Player_Explode_1_H::width, Player_Explode_1_H::height, Player_Explode_1_H::header_data);
Sprite playerExplode2Sprite(Player_Explode_2_H::width, Player_Explode_2_H::height, Player_Explode_2_H::header_data);
Sprite shieldSprite(Shield_H::width, Shield_H::height, Shield_H::header_data);
Sprite invaderLarge1Sprite(Invader_L1_H::width, Invader_L1_H::height, Invader_L1_H::header_data);
Sprite invaderLarge2Sprite(Invader_L2_H::width, Invader_L2_H::height, Invader_L2_H::header_data);
Sprite invaderMed1Sprite(Invader_M1_H::width, Invader_M1_H::height, Invader_M1_H::header_data);
Sprite invaderMed2Sprite(Invader_M2_H::width, Invader_M2_H::height, Invader_M2_H::header_data);
Sprite invaderSmall1Sprite(Invader_S1_H::width, Invader_S1_H::height, Invader_S1_H::header_data);
Sprite invaderSmall2Sprite(Invader_S2_H::width, Invader_S2_H::height, Invader_S2_H::header_data);
Sprite invaderLaserLarge1Sprite(Invader_Laser_S1_H::width, Invader_Laser_S1_H::height, Invader_Laser_S1_H::header_data);
Sprite invaderLaserLarge2Sprite(Invader_Laser_S2_H::width, Invader_Laser_S2_H::height, Invader_Laser_S2_H::header_data);
Sprite invaderLaserSmall1Sprite(Invader_Laser_L1_H::width, Invader_Laser_L1_H::height, Invader_Laser_L1_H::header_data);
Sprite invaderLaserSmall2Sprite(Invader_Laser_L2_H::width, Invader_Laser_L2_H::height, Invader_Laser_L2_H::header_data);
Sprite invaderUfoSprite(Invader_UFO_H::width, Invader_UFO_H::height, Invader_UFO_H::header_data);
Sprite invaderExplodeSprite(Invader_Explode_H::width, Invader_Explode_H::height, Invader_Explode_H::header_data);
