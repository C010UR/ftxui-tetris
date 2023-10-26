#include "t_menu/t_menu.hpp"

namespace Tetris::Menu
{

void Menu::setMenu(Tetris::Menu::MenuType menu)
{
    this->currentMenu      = menu;
    this->currentMenuIndex = (int)menu;
}

void Menu::startGame()
{
    this->isStartGame = true;
    this->screen.Exit();
}

void Menu::exitGame()
{
    this->isStartGame = false;
    this->screen.Exit();
}

Menu::Menu(
    ftxui::ScreenInteractive &screen,
    Tetris::Config::Config   &config,
    Tetris::Config::Controls &controls,
    bool                      isGameOver
)
    : config(config), controls(controls), screen(screen)
{
    auto startButtonHandler    = [this] { this->startGame(); };
    auto optionsButtonHandler  = [this] { this->setMenu(Tetris::Menu::MenuType::OPTIONS); };
    auto controlsButtonHandler = [this] { this->setMenu(Tetris::Menu::MenuType::CONTROLS); };
    auto mainMenuButtonHandler = [this] { this->setMenu(Tetris::Menu::MenuType::MAIN_MENU); };
    auto exitButtonHandler     = [this] { this->exitGame(); };
    auto changeKeyHandler      = [this](Tetris::Engine::Trigger trigger) {
        this->changeKeyMenu.isModalOpen = true;
        this->changeKeyMenu.trigger     = trigger;
        this->setMenu(Tetris::Menu::MenuType::CHANGE_KEY);
    };

    this->mainMenu = Tetris::Menu::MainMenu();
    this->mainMenu.init(startButtonHandler, optionsButtonHandler, controlsButtonHandler, exitButtonHandler);

    this->gameOverMenu = Tetris::Menu::GameOver();
    this->gameOverMenu.init(mainMenuButtonHandler, startButtonHandler, exitButtonHandler);

    this->optionsMenu = Tetris::Menu::Options();
    this->optionsMenu.init(this->config, mainMenuButtonHandler);

    this->changeKeyMenu = Tetris::Menu::ChangeKey();
    this->changeKeyMenu.init(this->controls);

    this->controlsMenu = Tetris::Menu::Controls();
    this->controlsMenu.init(this->controls, changeKeyHandler, mainMenuButtonHandler);

    this->setMenu(isGameOver ? Tetris::Menu::MenuType::GAME_OVER : Tetris::Menu::MenuType::MAIN_MENU);

    this->tab = ftxui::Container::Tab(
        {
            this->mainMenu.renderer,
            this->gameOverMenu.renderer,
            this->optionsMenu.renderer,
            this->controlsMenu.renderer,
            this->changeKeyMenu.renderer,
        },
        &this->currentMenuIndex
    );
}

ftxui::Component Menu::getRenderer()
{
    return ftxui::Renderer(this->tab, [this] {
        ftxui::Element document;

        switch (this->currentMenu)
        {
        case Tetris::Menu::MenuType::MAIN_MENU:
            document = this->mainMenu.renderer->Render();
            break;
        case Tetris::Menu::MenuType::GAME_OVER:
            document = this->gameOverMenu.renderer->Render();
            break;
        case Tetris::Menu::MenuType::OPTIONS:
            document = this->optionsMenu.renderer->Render();
            break;
        case Tetris::Menu::MenuType::CONTROLS:
            document = this->controlsMenu.renderer->Render();
            break;
        case Tetris::Menu::MenuType::CHANGE_KEY:
            document = this->controlsMenu.renderer->Render();

            document
                = ftxui::dbox({document, this->changeKeyMenu.renderer->Render() | ftxui::clear_under | ftxui::center});
            break;
        }

        return document;
    });
}

bool Menu::handleEvent(ftxui::Event event)
{
    if (this->changeKeyMenu.handleEvent(event))
    {
        this->setMenu(Tetris::Menu::MenuType::CONTROLS);
    };

    return false;
}
} // namespace Tetris::Menu