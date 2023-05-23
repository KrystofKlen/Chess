#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include "../Game/GameControl/OnePlayerGame.h"
#include "../Game/GameControl/TwoPlayersGame.h"
#include "../Game/GameControl/Tutorial.h"
#include "../API/Api.h"

class Application{
public:
    /**
     * Launches the chess game.
     */
    void launch();

    Application(){
        api = std::make_shared<API>();
    }

private:
    /**
     * Displays the menu and prompts the user to select an option.
     */
    void select();

    /**
     * Checks if the terminal meets the minimum requirements for the game to run.
     *
     * @return true if the terminal meets the minimum requirements, false otherwise.
     */
    bool checkTerminalRequirements();

    /**
     * Loads the game state from a file.
     *
     * @param chessGame The game control object that will hold the game state.
     * @return true if the game state was successfully loaded, false otherwise.
     */
    bool loadFromFile(std::unique_ptr<GameControl> & chessGame);

    /**
     * Starts a new game.
     *
     * @param choiceFromMenu The user's choice from the main menu.
     * @param chessGame The game control object that will hold the game state.
     */
    void startNewGame(int choiceFromMenu, std::unique_ptr<GameControl> & chessGame);


    std::shared_ptr<API> api;
    static const int minTerminalRows = 43;
    static const int minTerminalColumns = 50;
    const std::string PATH_TO_LOAD="load.game";
};