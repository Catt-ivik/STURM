// +++ Main file for the program STURM +++
//
// Actually the GameManager could have been implemented
// here, but seeing other games I wanted to maintain
// a standard construction starting the GameManager here
// and keep the main of the program for other purposes.
// 

#include "Game/Gamemanager.h"

int main()
{
    // Initializing the casual number generator
    srand(time(NULL));

    GameManager gameManager;
    gameManager.Start();

    return 0;
}