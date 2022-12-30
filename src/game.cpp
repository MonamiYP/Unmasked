#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

Manager manager;
Map* map;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

SDL_Rect Game::camera = { 0,0,800,640 };

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& enemy(manager.addEntity());
auto& woerm(manager.addEntity());

const char* map_file = "assets/basic_tilemap.png";

enum group_labels : std::size_t {
    group_map,
    group_player,
    group_enemy,
    group_collider
};

auto& tiles(manager.getGroup(group_map));
auto& players(manager.getGroup(group_player));
auto& enemies(manager.getGroup(group_enemy));
auto& colliders(manager.getGroup(group_collider));

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
    Map::loadMap("assets/p28x20.map", 28, 20);

    player.addComponent<TransformComponent>(2);
    player.addComponent<SpriteComponent>("assets/player.png", true);
    player.addComponent<InputController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(group_player);

    enemy.addComponent<TransformComponent>(100.0f, 100.0f, 32, 32, 2);
    enemy.addComponent<SpriteComponent>("assets/enemy.png");
    enemy.addGroup(group_enemy);

    woerm.addComponent<TransformComponent>(350.0f, 200.0f, 32, 32, 2);
    woerm.addComponent<SpriteComponent>("assets/woerm.png", true);
    woerm.addGroup(group_enemy);
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

void Game::addTile(int src_x, int src_y, int x_pos, int y_pos) {
    Entity& tile(manager.addEntity());
    tile.addComponent<TileComponent>(src_x, src_y, x_pos, y_pos, map_file);
    tile.addGroup(group_map);
}