#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
#include "AssetManager.hpp"

Manager manager;
Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,800,640 };

AssetManager* Game::assets = new AssetManager();

auto& player(manager.addEntity());
auto& enemy(manager.addEntity());
auto& woerm(manager.addEntity());

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
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            std::cout << "Renderer created successfully" << std::endl;
        }
        is_running = true;
    }

    assets->addTexture("terrain", "assets/basic_tilemap.png");
    assets->addTexture("player", "assets/player.png");
    assets->addTexture("enemy", "assets/enemy.png");
    assets->addTexture("woerm", "assets/woerm.png");

    map = new Map("terrain");
    map->loadMap("assets/p28x20.map", 28, 20);

    player.addComponent<TransformComponent>(2);
    player.addComponent<SpriteComponent>("player", true);
    player.addComponent<InputController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(group_player);

    enemy.addComponent<TransformComponent>(100.0f, 100.0f, 32, 32, 2);
    enemy.addComponent<SpriteComponent>("enemy");
    enemy.addGroup(group_enemy);

    woerm.addComponent<TransformComponent>(350.0f, 200.0f, 32, 32, 2);
    woerm.addComponent<SpriteComponent>("woerm", true);
    woerm.addGroup(group_enemy);
}

auto& tiles(manager.getGroup(Game::group_map));
auto& players(manager.getGroup(Game::group_player));
auto& enemies(manager.getGroup(Game::group_enemy));
auto& colliders(manager.getGroup(Game::group_collider));

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
    Vector2D player_position = player.getComponent<TransformComponent>().position;

    manager.refresh();
    manager.update();

    SDL_Rect player_collider = player.getComponent<ColliderComponent>().collider;

    for (auto& c : colliders) {
        SDL_Rect collider = c->getComponent<ColliderComponent>().collider;
        if(Collision::AABB(collider, player_collider)) {
            player.getComponent<TransformComponent>().position = player_position;
        }
    }

    camera.x = player.getComponent<TransformComponent>().position.x - 400;
    camera.y = player.getComponent<TransformComponent>().position.y - 320;

    if(camera.x < 0) { camera.x = 0; }
    if(camera.x < 0) { camera.y = 0; }
    if(camera.x > camera.w) { camera.x = camera.w; }
    if(camera.x > camera.h) { camera.y = camera.h; }
}

void Game::render() {
    SDL_RenderClear(renderer);
    for (auto& e : tiles) {
        e->draw();
    }
    for (auto& e : players) {
        e->draw();
    }
    for (auto& e : enemies) {
        e->draw();
    }
    for (auto& e : colliders) {
        e->draw();
    }

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