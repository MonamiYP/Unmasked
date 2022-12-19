#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/ECS.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"

Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
Manager manager;
auto& player(manager.addEntity());

Game::Game() {}
 
Game::~Game() {}

void Game::init(const char* title, int width, int height, bool full_screen) {
    int flags = 0;
    if(full_screen)
        flags = SDL_WINDOW_FULLSCREEN;

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL_Init successful" << std::endl;

        window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        if(window)
            std::cout << "Window created successfully" << std::endl;
        
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer) {
            SDL_SetRenderDrawColor(renderer, 50, 50, 100, 255);
            std::cout << "Renderer created successfully" << std::endl;
        }
        
        is_running = true;
    }

    map = new Map();
    
    player.addComponent<TransformComponent>();
    player.addComponent<SpriteComponent>("assets/player.png");
    player.addComponent<InputController>();
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
}

void Game::update() {
    manager.refresh();
    manager.update();
}

void Game::render() {
    SDL_RenderClear(renderer);

    map->drawMap();
    manager.draw();

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleared" << std::endl;
}

bool Game::running() {
    return is_running;
}