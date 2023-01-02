#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
#include "AssetManager.hpp"
#include "Game_states/GameState.hpp"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,800,640 };

AssetManager* Game::assets = new AssetManager();

Game::Game() {}
 
Game::~Game() {}

void Game::init(const char* title, int width, int height, bool m_fullscreen) {
    int flags = 0;
    if(m_fullscreen)
        flags = SDL_WINDOW_FULLSCREEN;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL_Init successful" << std::endl;

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags | SDL_WINDOW_RESIZABLE);
        if(window)
            std::cout << "Window created successfully" << std::endl;
        
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            std::cout << "Renderer created successfully" << std::endl;
        }
        fullscreen = m_fullscreen;
        is_running = true;
    }
}

void Game::handleEvents() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        default:
            break;
    }
    game_states.back()->handleEvents(this);
}

void Game::update() {
    game_states.back()->update(this);
}

void Game::render() {
    game_states.back()->render(this);
}

void Game::clean() {
    // Cleanup all the states
    while (!game_states.empty()){
        game_states.back()->clean();
        game_states.pop_back();
    }

    if (fullscreen) {
        SDL_SetWindowSize(window, 640, 480);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleared" << std::endl;
}

bool Game::running() {
    return is_running;
}

void Game::changeState(GameState* game_state) {
    if (!game_states.empty()) {
        game_states.back()->clean();
        game_states.pop_back();
    }

    game_states.push_back(game_state);
    game_states.back()->init();
}

void Game::pushState(GameState* game_state) {
    if (!game_states.empty()) {
        game_states.back()->pause();
    }

    game_states.push_back(game_state);
    game_states.back()->init();
}

void Game::popState() {
    if (!game_states.empty()) {
        game_states.back()->clean();
        game_states.pop_back();
    }

    if (!game_states.empty()) {
        game_states.back()->resume();
    }
}