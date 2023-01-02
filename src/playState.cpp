#include "Game_states/PlayState.hpp"
#include "Game_states/MenuState.hpp"
#include "AssetManager.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

PlayState PlayState::play_state;

Manager manager;
Map* map;

auto& player(manager.addEntity());
auto& enemy(manager.addEntity());
auto& woerm(manager.addEntity());

void PlayState::init() {
    Game::assets->addTexture("terrain", "assets/basic_tilemap.png");
    Game::assets->addTexture("player", "assets/player.png");
    Game::assets->addTexture("enemy", "assets/enemy.png");
    Game::assets->addTexture("woerm", "assets/woerm.png");

    map = new Map("terrain");
    map->loadMap("assets/p28x20.map", 28, 20);

    player.addComponent<TransformComponent>(2);
    player.addComponent<SpriteComponent>("player", true);
    player.addComponent<InputController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(Game::group_player);

    enemy.addComponent<TransformComponent>(100.0f, 100.0f, 32, 32, 2);
    enemy.addComponent<SpriteComponent>("enemy");
    enemy.addGroup(Game::group_enemy);

    woerm.addComponent<TransformComponent>(350.0f, 200.0f, 32, 32, 2);
    woerm.addComponent<SpriteComponent>("woerm", true);
    woerm.addGroup(Game::group_enemy);
}

void PlayState::clean() {
    
}

void PlayState::pause() {
    player.getComponent<TransformComponent>().velocity.zero();
}

void PlayState::resume() {

}

auto& tiles(manager.getGroup(Game::group_map));
auto& players(manager.getGroup(Game::group_player));
auto& enemies(manager.getGroup(Game::group_enemy));
auto& colliders(manager.getGroup(Game::group_collider));

void PlayState::handleEvents(Game* game) {
    if (game->event.type == SDL_KEYDOWN) {
        switch (game->event.key.keysym.sym) {
        case SDLK_SPACE:
            game->pushState(MenuState::instance());
            break;
    
        default:
            break;
        }
    }
}

void PlayState::update(Game* game) {
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

    game->camera.x = player.getComponent<TransformComponent>().position.x - 400;
    game->camera.y = player.getComponent<TransformComponent>().position.y - 320;

    if(game->camera.x < 0) { game->camera.x = 0; }
    if(game->camera.x < 0) { game->camera.y = 0; }
    if(game->camera.x > game->camera.w) { game->camera.x = game->camera.w; }
    if(game->camera.x > game->camera.h) { game->camera.y = game->camera.h; }
}

void PlayState::render(Game* game) {
    SDL_RenderClear(game->renderer);
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

    SDL_RenderPresent(game->renderer);
}