#include "t_game/t_game.hpp"
#include "t_engine/t_enums.hpp"

namespace Tetris::Game
{
unsigned Game::calculateTicks(double ms)
{
    return ms / 1000 * this->config.updatesPerSecond;
}

double Game::calculateGravity()
{
    return std::min(
        (1000
         / (isSoftDrop && this->config.softDropGravity < this->score.getGravity() ? this->config.softDropGravity
                                                                                  : this->score.getGravity()))
            / this->config.updatesPerSecond,
        (double)std::max(this->board.getRowsToObstacle(), 1.)
    );
}

void Game::handleGravity()
{
    this->storeDelayTicks++;
    double offset       = this->calculateGravity();
    double prevPosition = this->board.getCurrent()->currentPosition.y;

    if (this->board.tryMoveCurrent({0, offset}))
    {
        this->storeDelayTicks = 0;

        double nextPosition = this->board.getCurrent()->currentPosition.y;

        if ((int)prevPosition != (int)nextPosition)
        {
            this->triggers.push_back(Tetris::Engine::Trigger::NEXT_ROW);
        }
    }
}

void Game::handleSoftDrop()
{
    if (!this->isSoftDrop)
    {
        return;
    }

    if (this->softDropDelayTicks == this->calculateTicks(this->config.softDropDelay))
    {
        this->isSoftDrop         = 0;
        this->softDropDelayTicks = 0;
    }

    this->softDropDelayTicks++;
}

void Game::handleDrop()
{
    if (this->storeDelayTicks != this->calculateTicks(this->config.storeDelay))
    {
        return;
    }

    this->handleStore();
    this->storeDelayTicks = 0;
}

void Game::handleStore()
{
    if (this->board.canMoveCurrent({0, 1}))
    {
        return;
    }

    SpinType lastSpinType = this->board.getCurrent()->getSpinType();

    int linesCleared = this->board.store(this->next.pop());

    if (linesCleared > 0)
    {
        this->comboDelayTicks = this->calculateTicks(this->config.comboDelay);
        this->score.update(linesCleared, this->board.isBoardClear(), lastSpinType);
        this->board.getCurrent()->resetSpinData();
    }

    this->hold.unblock();

    if (this->board.isGameOver) {
        this->exitType = Tetris::Engine::ExitType::CONTINUE;
    }
}

void Game::handleSwapHold()
{
    Tetromino tetromino = this->hold.has() ? this->hold.get() : this->next.pop();

    this->hold.set(*this->board.getCurrent());
    this->board.setCurrent(tetromino);
    this->hold.block();
}

void Game::handleCombo()
{
    if (this->comboDelayTicks == 0)
    {
        this->score.resetCombo();
    }

    if (this->comboDelayTicks > 0)
    {
        this->comboDelayTicks--;
    }
}

Game::Game(Tetris::Config::Config &config, Tetris::Config::Controls &controls)
{
    this->score = Score();
    this->next  = Next();
    this->hold  = Hold();
    this->board = Board(this->next.pop());

    this->config   = config;
    this->controls = controls;

    this->softDropDelayTicks = 0;
    this->comboDelayTicks    = 0;
    this->storeDelayTicks    = 0;

    this->score.level = config.level;

    this->isSoftDrop = false;

    this->exitType = Tetris::Engine::ExitType::ABORT;
}

void Game::update()
{
    this->handleSoftDrop();
    this->handleGravity();
    this->handleDrop();
    this->handleCombo();
    this->handleTriggers();
}

void Game::handleInput()
{
    for (const auto &trigger : this->inputTriggers)
    {
        switch (trigger)
        {
        case Engine::Trigger::KEY_MOVE_LEFT:
            this->board.tryMoveCurrent({-1, 0});

            break;
        case Engine::Trigger::KEY_MOVE_RIGHT:
            this->board.tryMoveCurrent({1, 0});

            break;
        case Engine::Trigger::KEY_ROTATE_LEFT:
            this->board.tryRotateCurrent(RotationType::LEFT);

            break;
        case Engine::Trigger::KEY_ROTATE_RIGHT:
            this->board.tryRotateCurrent(RotationType::RIGHT);

            break;
        case Engine::Trigger::KEY_SWAP_HOLD:
            this->handleSwapHold();

            break;
        case Engine::Trigger::KEY_SOFT_DROP:
            this->isSoftDrop         = true;
            this->softDropDelayTicks = 0;

            break;
        case Engine::Trigger::KEY_HARD_DROP:
            this->score.add(ScoreType::HARD_DROP, (int)this->board.getRowsToObstacle());
            this->board.tryMoveCurrent({0, this->board.getRowsToObstacle()});
            this->handleStore();

            break;
        case Engine::Trigger::KEY_FORFEIT:
            this->board.isGameOver = true;
            this->exitType = Tetris::Engine::ExitType::CONTINUE;

            break;
        case Engine::Trigger::KEY_RETRY:
            this->board.isGameOver = true;
            this->exitType = Tetris::Engine::ExitType::RETRY;
        default:
            break;
        }
    }

    this->inputTriggers.clear();
}

void Game::handleTriggers()
{
    for (const auto &trigger : this->triggers)
    {
        switch (trigger)
        {
        case Tetris::Engine::Trigger::NEXT_ROW:
            if (this->isSoftDrop)
            {
                this->score.add(ScoreType::SOFT_DROP, 1);
            }

            break;
        default:
            break;
        }
    }

    this->triggers.clear();
}

bool Game::handleEvent(ftxui::Event event)
{
    Tetris::Engine::Trigger trigger = this->controls.handleEvent(event);

    if (trigger != Tetris::Engine::Trigger::NONE)
    {
        this->inputTriggers.push_back(trigger);
    }

    return false;
}

ftxui::Element Game::getDebugElement()
{
    return ftxui::window(
               ftxui::text("Debug"),
               ftxui::vbox({
                   Tetris::Renderer::KeyValue::create("Hold Blocked", this->hold.isBlocked),
                   Tetris::Renderer::KeyValue::create("Gravity", this->score.getGravity()),
                   Tetris::Renderer::KeyValue::create("Gravity per update", this->calculateGravity()),
                   Tetris::Renderer::KeyValue::create("Soft drop", this->isSoftDrop),
                   Tetris::Renderer::KeyValue::create(
                       "Soft drop delay", this->softDropDelayTicks * this->config.updatesPerSecond
                   ),
                   Tetris::Renderer::KeyValue::create(
                       "Store delay", this->storeDelayTicks * this->config.updatesPerSecond
                   ),
                   Tetris::Renderer::KeyValue::create(
                       "Combo delay", this->comboDelayTicks * this->config.updatesPerSecond
                   ),
               })
           )
           | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 30);
}

ftxui::Component Game::getRenderer()
{
    return ftxui::Renderer([this] {
        ftxui::Elements elements;

        elements.push_back(
            ftxui::vbox(
                {this->score.getStatsElement(),
                 ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 13),
                 this->score.getComboElement()}
            )
            | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 20)
        );

        elements.push_back(this->board.getElement(this->config.isEasyMode));
        elements.push_back(
            this->score.getComboGaugeElement(
                (double)this->comboDelayTicks / this->calculateTicks(this->config.comboDelay)
            )
            | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, this->board.height)
        );

        elements.push_back({ftxui::vbox(
            {this->next.getElement(),
             ftxui::filler() | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 10),
             this->hold.getElement()}
        )});

        if (this->config.isDebug)
        {
            elements.push_back(ftxui::filler() | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 3));

            elements.push_back(ftxui::vbox({this->board.getDebugElement(this->calculateGravity())}));

            elements.push_back(ftxui::vbox({this->getDebugElement()}));
        }

        return ftxui::hbox(elements) | ftxui::center;
    });
}

bool Game::isGameOver()
{
    return this->board.isGameOver;
}

int Game::getScore()
{
    return this->score.score;
}

} // namespace Tetris::Game