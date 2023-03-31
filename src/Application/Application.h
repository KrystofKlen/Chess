#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include "../Game/GameControl/OnePlayerGame.h"
#include "../Game/GameControl/TwoPlayersGame.h"
#include "../API/Api.h"

class Application{
public:
    void launch();
private:
    const int ONE_PLAYER_GAME = 0;
    const int TWO_PLAYERS_GAME = 1;
    void select();
    static const int minTerminalRows = 43;
    static const int minTerminalColumns = 50;

    bool checkTerminalRequirements();
    const std::string PATH_TO_LOAD="load.game";

    API api;

};