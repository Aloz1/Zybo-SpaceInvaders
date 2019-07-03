/*
 * Empty C++ Application
 */

#include "drivers/VGA.h"
#include "config.h"
#include "tasks/MainGameTask.h"

using namespace std;

int main()
{
    // Instantiate the player and its laser
	static MainGameTask gameTask;

    // Clear the screen (so we don't have stripes everywhere)
	clearScreen(BLACK);

    // Attach all invaders to the player laser
	//invaderBinTask.attachCollidablesToLaser(playerLaserTask);

    // Initialize the invader bin (reset invader positions, visibility, etc)
	//invaderBinTask.reset();

    // And go (Creates idle task and runs FreeRTOS task loop)
	vTaskStartScheduler();

    // Just incase vTaskScheduler exits
	for(;;) vTaskSuspend(NULL);
}
