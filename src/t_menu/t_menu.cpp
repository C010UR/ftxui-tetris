#include "t_menu/t_menu.hpp"

namespace Tetris::Menu {

void Menu::setMenu(MenuType menu)
{
    this->currentMenu      = menu;
    this->currentMenuIndex = (int)menu;
}

void Menu::startGame()
{
    this->exitType = Tetris::Engine::ExitType::CONTINUE;
    this->screen.Exit();
}

void Menu::exitGame()
{
    this->exitType = Tetris::Engine::ExitType::EXIT;
    this->screen.Exit();
}

void Menu::restartMenu()
{
    this->exitType = Tetris::Engine::ExitType::RETRY;
    this->screen.Exit();
}

Menu::Menu(
    ftxui::ScreenInteractive     &screen,
    Tetris::Config::Config       &config,
    Tetris::Config::Controls     &controls,
    const bool                    isGameOver,
    const Tetris::Game::GameData &gameData):
    config(config),
    controls(controls), screen(screen)
{
    auto startButtonHandler = [this] {
        this->startGame();
    };
    auto optionsButtonHandler = [this] {
        this->setMenu(MenuType::OPTIONS);
    };
    auto controlsButtonHandler = [this] {
        this->setMenu(MenuType::CONTROLS);
    };
    auto mainMenuButtonHandler = [this] {
        this->setMenu(MenuType::MAIN_MENU);
    };
    auto exitButtonHandler = [this] {
        this->exitGame();
    };
    auto restartHandler = [this] {
        this->restartMenu();
    };
    auto changeKeyHandler = [this](Tetris::Engine::Trigger trigger) {
        this->changeKeyMenu.isModalOpen = true;
        this->changeKeyMenu.trigger     = trigger;
        this->setMenu(MenuType::CHANGE_KEY);
    };

    this->mainMenu = MainMenu();
    this->mainMenu.init(startButtonHandler, optionsButtonHandler, controlsButtonHandler, exitButtonHandler);

    this->gameOverMenu = GameOver();
    this->gameOverMenu.init(mainMenuButtonHandler, startButtonHandler, exitButtonHandler, gameData);

    this->optionsMenu = Options();
    this->optionsMenu.init(this->config, mainMenuButtonHandler, restartHandler);

    this->changeKeyMenu = ChangeKey();
    this->changeKeyMenu.init(this->controls);

    this->controlsMenu = Controls();
    this->controlsMenu.init(this->controls, changeKeyHandler, mainMenuButtonHandler);

    this->setMenu(isGameOver ? MenuType::GAME_OVER : MenuType::MAIN_MENU);

    this->tab = ftxui::Container::Tab(
        {
            this->mainMenu.renderer,
            this->gameOverMenu.renderer,
            this->optionsMenu.renderer,
            this->controlsMenu.renderer,
            this->changeKeyMenu.renderer,
        },
        &this->currentMenuIndex);
}

ftxui::Component Menu::getRenderer()
{
    return ftxui::Renderer(this->tab, [this] {
        ftxui::Element document;

        switch (this->currentMenu) {
            case MenuType::MAIN_MENU:
                document = this->mainMenu.renderer->Render();
                break;
            case MenuType::GAME_OVER:
                document = this->gameOverMenu.renderer->Render();
                break;
            case MenuType::OPTIONS:
                document = this->optionsMenu.renderer->Render();
                break;
            case MenuType::CONTROLS:
                document = this->controlsMenu.renderer->Render();
                break;
            case MenuType::CHANGE_KEY:
                document = this->controlsMenu.renderer->Render();

                document = ftxui::dbox(
                    {document, this->changeKeyMenu.renderer->Render() | ftxui::clear_under | ftxui::center});
                break;
        }

        return document;
    });
}

bool Menu::handleEvent(ftxui::Event event)
{
    if (this->changeKeyMenu.handleEvent(event)) {
        this->setMenu(MenuType::CONTROLS);
    };

    return false;
}
} // namespace Tetris::Menu