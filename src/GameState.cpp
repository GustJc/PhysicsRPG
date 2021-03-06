#include "GameState.h"
#include "Globals.h"
#include "TextureManager.h"
#include "Engine.h"
#include "Flag.h"
#include "Character.h"
#include "PlayerEntity.h"
#include "Effects.h"
#include "Spawner.h"
#include "Map.h"
#include <cmath>
#include "SpriteBody.h"
#include <iostream>
#include <sstream>
using namespace std;
GameState::GameState(sf::RenderWindow& wnd) :
State(wnd)
{
    //ctor
}
GameState::~GameState()
{
    //dtor

}

void GameState::load(int )
{
    cout << "[Estado] Carregando estado GameState. " << endl;

    m_debug_render = new DebugRender(&window);
    m_debug_render->SetFlags( b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);

    TextureManager::TextureControl.load("background", "data/temp_background.png");

    TextureManager::TextureControl.load("menu_superior", "data/menu_su.png");
    TextureManager::TextureControl.load("tileset", "data/tileset2.png");

    TextureManager::TextureControl.load("player_char", "data/player_char.png");
    TextureManager::TextureControl.load("flag", "data/flag.png");
    TextureManager::TextureControl.load("slime", "data/slime.png");
    TextureManager::TextureControl.load("weak_orc", "data/weak_orc.png");
    TextureManager::TextureControl.load("spawn", "data/spawn.png");

    TextureManager::TextureControl.load("wood", "data/img/wood-block-lowres-16.png");
    TextureManager::TextureControl.load("wood_large", "data/img/wood-block-large.png");
    TextureManager::TextureControl.load("boulder_8", "data/img/boulder-rad8.png");
    TextureManager::TextureControl.load("boulder_16", "data/img/boulder-rad16.png");

    TextureManager::TextureControl.load("explosion", "data/explosion.png");

    TextureManager::TextureControl.load("arrow", "data/arrow.png");
    TextureManager::TextureControl.load("arrow2", "data/arrow_full.png");
    TextureManager::TextureControl.load("arrow_shot", "data/arrow_shot.png");
    TextureManager::TextureControl.load("ui", "data/selection_ui.png");

    b2Vec2 gravity(0.0f, 10.0f);

    //Prepara mundo
    Engine::world = new b2World(gravity);
    world =  Engine::world;

    world->SetAllowSleeping(true);
    world->SetDebugDraw(m_debug_render);

    // Cria Chão
    //b2BodyDef ground_def;
    //ground_def.position.Set(400.0f/pixelsPerMeter, 600.0/pixelsPerMeter);

    //b2Body* m_ground = world->CreateBody(&ground_def);
    mock = new SpriteBody();
    mock->getBodyDef()->position.Set(400.0f/pixelsPerMeter, 600.0/pixelsPerMeter);

    b2PolygonShape* groundBox = mock->getBodyShape();

    //m_ground->SetUserData(mock);
    //b2PolygonShape groundBox;
    groundBox->SetAsBox(1000.f/pixelsPerMeter, 80.f/pixelsPerMeter);
    //m_ground->CreateFixture(&groundBox, 0.0f);
    mock->createBody(*world);
    mock->getBody()->SetType(b2_staticBody);


    this->flag = new Flag();
    flag->setTexture(TextureManager::TextureControl.get("flag"), 29, 46, 2, 400);
    flag->getSprite()->setOrigin(15,23);
    flag->getBodyDef()->position.Set(1100.0f/pixelsPerMeter, (520.f-23.f)/pixelsPerMeter);
    ((b2PolygonShape*)flag->getBodyShape() )->SetAsBox(14.0f/pixelsPerMeter,23.0f/pixelsPerMeter);
    flag->createBody(*world);
    flag->getBody()->SetUserData(flag);
    Engine::bodylist.push_back(flag);

    this->player = new PlayerEntity(world, -300, 500);
    Engine::bodylist.push_back(this->player);

    //in FooTest constructor
    world->SetContactListener(&listenner);


    Map::MapControl.loadMap(Map::MapControl.map_name);
    if (!music.openFromFile(Map::MapControl.music_name) ){
        cout << "[Erro] Erro ao carregar musica" << endl;
    } else
    {
        music.play();
        music.setLoop(true);
    }
}

int GameState::unload()
{
    delete mock;
    if(m_debug_render != nullptr)
        delete m_debug_render;
    if(world != nullptr)
        delete world;

    if(Engine::bodylist.empty() == false)
    {
        for(int i = 0; i < (int) Engine::bodylist.size(); i++)
            delete Engine::bodylist[i];

        Engine::bodylist.clear();
    }

    if(Engine::effectslist.empty() == false)
    {
        for(int i = 0; i < (int) Engine::effectslist.size(); i++)
            delete Engine::effectslist[i];

        Engine::effectslist.clear();
    }

    sf::View& view = Engine::EngineControl.getViewGame();
    view.reset(sf::FloatRect(0, 0, 800, 600));
    view.setCenter(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f);

    window.setView(view);

    return mStack;
}

eStateType GameState::update(float dt)
{
    world->Step(dt, 8, 4);

    for(int i = 0; i < (int) Engine::bodylist.size(); i++)
    {
        Engine::bodylist[i]->update(dt);
    }

    for(int i = 0; i < (int) Engine::effectslist.size(); i++)
    {
        Engine::effectslist[i]->update(dt);
    }

    if(this->flag->isDead())
        this->mStado = GST_WIN;

    if(this->player->isDead())
        this->mStado = GST_LOSE;

    return mStado;
}

void GameState::events(sf::Event& event)
{
    player->events(event);

    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Escape)
        {
            mStado = GST_MENU;
        }
        else if(event.key.code == sf::Keyboard::Q){
            isDebug = !isDebug;
        }
        else if(event.key.code == sf::Keyboard::E){
            isGrid = !isGrid;
        }
        else if(event.key.code == sf::Keyboard::K){
            mStado = GST_WIN;
        }
//Debug Controls

        if(event.key.code == sf::Keyboard::X)
        {
            SplashAnimation* sa = new SplashAnimation(TextureManager::TextureControl.get("explosion"), sf::Vector2i(16,16),
                                      b2Vec2(300/pixelsPerMeter, (500)/pixelsPerMeter), 5, 100, sf::Vector2f(5.0, 5.0) );
            sa->inicialImpulse = b2Vec2(1, 1);
        }
        if(event.key.code == sf::Keyboard::Z)
        {
            SplashText* sa = new SplashText("Teste",
                                                 b2Vec2((100)/pixelsPerMeter, (500)/pixelsPerMeter)
                                                 ,sf::Color::Blue, 30, 1000);
            sa->inicialImpulse = b2Vec2(1, 1);
        }

//Move camera
        else if(event.key.code == sf::Keyboard::D)
        {
            sf::View& view = Engine::EngineControl.getViewGame();
            view.move(sf::Vector2f(20,0));
            window.setView(view);
        }
        else if(event.key.code == sf::Keyboard::A)
        {
            sf::View& view = Engine::EngineControl.getViewGame();
            view.move(sf::Vector2f(-20,0));
            window.setView(view);
        }
        else if(event.key.code == sf::Keyboard::W)
        {
            sf::View& view = Engine::EngineControl.getViewGame();
            view.move(sf::Vector2f(0,-20));
            window.setView(view);
        }
        else if(event.key.code == sf::Keyboard::S)
        {
            sf::View& view = Engine::EngineControl.getViewGame();
            view.move(sf::Vector2f(0,20));
            window.setView(view);
        }
//Zoom
        if(event.key.control)
        {
            if(event.key.code == sf::Keyboard::Equal)
            {
                sf::View& view = Engine::EngineControl.getViewGame();
                view.zoom(0.8f);
                window.setView(view);
            }
            else
            if(event.key.code == sf::Keyboard::Dash)
            {
                sf::View& view = Engine::EngineControl.getViewGame();
                view.zoom(1.2f);
                window.setView(view);
            }
        }

    }
}

void GameState::render()
{
    sf::Sprite background;
    background.setTexture(TextureManager::TextureControl.get("background"));
    background.setPosition( window.mapPixelToCoords(sf::Vector2i(-this->window.getView().getCenter().x*0.15 - 100,0) ) );
    window.draw(background);

    //Draw floor
    Engine::EngineControl.drawRectVertex(-600,520,2000,160);
    for(int x = -500; x < 2000; x+= 100)
        Engine::EngineControl.drawRectVertex(x,520,2,160,sf::Color(0,100,0));

    for(int i = 0; i < (int) Engine::bodylist.size(); i++)
    {
        Engine::bodylist[i]->render(window);
    }

    sf::Vector2f offset = window.getView().getCenter();
    sf::Vector2f start(offset.x - WINDOW_WIDTH/2.f, offset.y - WINDOW_HEIGHT/2.f);

    //Draw grid
    if(isGrid)
    {
        for(int x = start.x; x < start.x+WINDOW_WIDTH; x+= 16)
            Engine::EngineControl.drawLine(x, start.y, x, start.y+WINDOW_HEIGHT, sf::Color(0,0,0, 20));
        for(int y = start.y; y < start.y+WINDOW_HEIGHT; y+= 16)
            Engine::EngineControl.drawLine(start.x, y, start.x+WINDOW_WIDTH, y, sf::Color(0,0,0, 50) );
    }

    //Effects layer
    for(int i = 0; i < (int) Engine::effectslist.size(); i++)
    {
        Engine::effectslist[i]->render(window);
    }

    //Draw selection area
    sf::Vector2i mouseTemp = sf::Mouse::getPosition(window);
    sf::Vector2f mouse = window.mapPixelToCoords(mouseTemp);

    int width = 16;
    int height = 16;
    if(selectedId == 2) width = 16 * 4;
    if(selectedId == 3) height = 16 * 4;
    Engine::EngineControl.drawRectVertex( floor(mouse.x/16.f)*16, floor(mouse.y/16.f)*16, width, height, sf::Color(100,50,100,50) );

    renderUI();


    //Draw debug data
    if(isDebug)
        world->DrawDebugData();
}

#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
void GameState::loadMap(string filename)
{
    ifstream file;
    string absFileName("./data/map/"+filename);
    file.open( absFileName.c_str());

    if(file.is_open() == false){
        printf("Nao foi possivel abrir o arquivo: %s.\n", absFileName.c_str());
        return;
    }


    float x, y, angle;
    int type;
    while(file >> x >> y >> type >> angle)
    {
        cout << "x: " << x << endl;
        cout << "type: " << type << endl;
        SpriteBody* sp_body = new SpriteBody(type);
        sp_body->createBody(*world);
        sp_body->getBody()->SetFixedRotation(false);
        sp_body->getBody()->SetTransform(b2Vec2(x,y), angle);

        Engine::bodylist.push_back(sp_body);

    }

    file.close();

    cout << "Map loaded: " << absFileName << endl;

}

void GameState::renderUI()
{
    sf::Sprite menu;
    menu.setTexture(TextureManager::TextureControl.get("menu_superior"));
    menu.setPosition( window.mapPixelToCoords(sf::Vector2i(0,0) ) );
    window.draw(menu);

    stringstream ss;
    ss << this->player->gold;
    sf::Text gold(ss.str(), Engine::EngineControl.getFont());
    gold.setColor(sf::Color::Yellow);
    gold.setPosition( window.mapPixelToCoords(sf::Vector2i(400 - gold.getGlobalBounds().width/2.f, 80) ) );
    window.draw(gold);

    int startpX = 310;
    int startpY = 0;

    sf::Sprite ui;
    if(player->shotTimer.getElapsedTime().asSeconds() > player->shot_cooldown)
    {
        ui.setTexture(TextureManager::TextureControl.get("ui"));
        ui.setTextureRect(sf::IntRect(0,0, 80, 80) );
        ui.setPosition( window.mapPixelToCoords(sf::Vector2i(startpX,startpY) ) );
        window.draw(ui);
    }
    else
    {
        ui.setTexture(TextureManager::TextureControl.get("ui"));
        ui.setTextureRect(sf::IntRect(80,0, 80, 80) );
        ui.setPosition( window.mapPixelToCoords(sf::Vector2i(startpX,startpY) ) );
        window.draw(ui);
    }

    if(player->shotTimer.getElapsedTime().asSeconds() > player->shot_cooldown
            && (player->selectedShot == 2 || player->gold >= player->goldCost)
            )
    {
        ui.setTexture(TextureManager::TextureControl.get("ui"));
        ui.setTextureRect(sf::IntRect(0,80, 80, 80) );
        ui.setPosition( window.mapPixelToCoords(sf::Vector2i(startpX+100,startpY) ) );
        window.draw(ui);
    }
    else
    {
        ui.setTexture(TextureManager::TextureControl.get("ui"));
        ui.setTextureRect(sf::IntRect(80,80, 80, 80) );
        ui.setPosition( window.mapPixelToCoords(sf::Vector2i(startpX+100,startpY) ) );
        window.draw(ui);
    }

}

