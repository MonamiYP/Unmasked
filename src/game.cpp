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

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& enemy(manager.addEntity());
auto& wall(manager.addEntity());

enum group_labels : std::size_t {
    group_map,
    group_player,
    group_enemy,
    group_collider
};

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
    Map::loadMap("assets/p20x20.map", 20, 20);

    player.addComponent<TransformComponent>(2);
    player.addComponent<SpriteComponent>("assets/player.png");
    player.addComponent<InputController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(group_player);

    enemy.addComponent<TransformComponent>(100.0f, 100.0f, 32, 32, 2);
    enemy.addComponent<SpriteComponent>("assets/enemy.png");
    enemy.addGroup(group_enemy);

    wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
    wall.addComponent<SpriteComponent>("assets/dirt.png");
    wall.addComponent<ColliderComponent>("wall");
    wall.addGroup(group_map);
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
    //Vector2D player_pos = player.getComponent<TransformComponent>().position;
    manager.refresh();
    manager.update();

    for (auto c : colliders) {
        Collision::AABB(player.getComponent<ColliderComponent>(), *c);
        //player.getComponent<TransformComponent>().position = player_pos;
    }
}

auto& tiles(manager.getGroup(group_map));
auto& players(manager.getGroup(group_player));
auto& enemies(manager.getGroup(group_enemy));
auto& colliders(manager.getGroup(group_collider));

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

void Game::addTile(int x, int y, int id) {
    Entity& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, 32, 32, id);
    tile.addGroup(group_map);
}