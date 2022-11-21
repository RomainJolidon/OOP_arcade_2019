/*
** EPITECH PROJECT, 2023
** OOP_arcade_2019
** File description:
** Created by rjolidon,
*/

#include "../include/LibAllegro.hpp"

LibAllegro::LibAllegro()
: _name("Allegro5"),
_window(nullptr),
_event_queue(nullptr),
_timer(nullptr),
_running(true),
_redraw(true)
{

    if (!al_init()) {
        std::cout << "Failed to initialize Allegro5" << std::endl;
        return;
    }
    _window = al_create_display(1920, 1080);
    if (!_window) {
        std::cout << "Failed to load Allegro5 display Module" << std::endl;
        return;
    }

    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_keyboard();

    _event_queue = al_create_event_queue();
    _timer = al_create_timer(1.0 / 30);

    al_register_event_source(_event_queue, al_get_display_event_source(_window));
    al_register_event_source(_event_queue, al_get_timer_event_source(_timer));
    al_register_event_source(_event_queue, al_get_keyboard_event_source());

    al_start_timer(_timer);
}

LibAllegro::~LibAllegro()
{
    al_destroy_display(_window);
    al_destroy_event_queue(_event_queue);
    al_destroy_timer(_timer);
}

void LibAllegro::initWindow()
{
    _window = al_create_display(1920, 1080);
    _event_queue = al_create_event_queue();
    _timer = al_create_timer(1.0 / 30);

    al_register_event_source(_event_queue, al_get_display_event_source(_window));
    al_register_event_source(_event_queue, al_get_timer_event_source(_timer));
    al_register_event_source(_event_queue, al_get_keyboard_event_source());
    al_start_timer(_timer);
}

void LibAllegro::destroyWindow()
{
    al_destroy_display(_window);
    al_destroy_event_queue(_event_queue);
    al_destroy_timer(_timer);
}

bool LibAllegro::isOpen() const
{
    return (_running);
}

void LibAllegro::drawEntity(const Entity &ent_1)
{
    int size = 32;
    ALLEGRO_COLOR blackColor = al_map_rgb(0, 0, 0);
    float x = ent_1.getPosX() * 32;
    float y = ent_1.getPosY() * 32;

    switch (ent_1.getType()) {
    case TypeEntity ::PLAYER_1:
        al_draw_filled_rectangle(x, y, x + size, y + size, al_map_rgb(0, 0, 255));
        al_draw_rectangle(x, y, x + size, y + size, blackColor, 3);
        break;
    case TypeEntity ::PLAYER_2:
        al_draw_filled_rectangle(x, y, x + size, y + size, al_map_rgb(0, 0, 240));
        al_draw_rectangle(x, y, x + size, y + size, blackColor, 3);
        break;
    case TypeEntity ::PLAYER_3:
        al_draw_filled_rectangle(x, y, x + size, y + size, al_map_rgb(0, 0, 200));
        al_draw_rectangle(x, y, x + size, y + size, blackColor, 3);
        break;
    case TypeEntity ::ENEMY_1:
        al_draw_filled_rectangle(x, y, x + size, y + size, al_map_rgb(255, 0, 0));
        al_draw_rectangle(x, y, x + size, y + size, blackColor, 3);
        break;
    case TypeEntity ::ENEMY_2:
        al_draw_filled_rectangle(x, y, x + size, y + size, al_map_rgb(240, 0, 0));
        al_draw_rectangle(x, y, x + size, y + size, blackColor, 3);
        break;
    case TypeEntity ::ENEMY_3:
        al_draw_filled_rectangle(x, y, x + size, y + size, al_map_rgb(170, 10, 10));
        al_draw_rectangle(x, y, x + size, y + size, blackColor, 3);
        break;
    case TypeEntity ::WALL_1:
        al_draw_filled_rectangle(x, y, x + size, y + size, al_map_rgb(55, 55, 55));
        al_draw_rectangle(x, y, x + size, y + size, blackColor, 3);
        break;
    case TypeEntity ::WALL_2:
        al_draw_filled_rectangle(x, y, x + size, y + size, al_map_rgb(65, 65, 65));
        al_draw_rectangle(x, y, x + size, y + size, blackColor, 3);
        break;
    case TypeEntity ::WALL_3:
        al_draw_filled_rectangle(x, y, x + size, y + size, al_map_rgb(75, 75, 75));
        al_draw_rectangle(x, y, x + size, y + size, blackColor, 3);
        break;
    case TypeEntity ::FLOOR:
        al_draw_filled_rectangle(x, y, x + size, y + size, al_map_rgb(0, 200, 0));
        al_draw_rectangle(x, y, x + size, y + size, blackColor, 3);
        break;
    case TypeEntity ::BONUS_1:
        al_draw_filled_rectangle(x, y, x + size, y + size, al_map_rgb(255,255,0));
        al_draw_rectangle(x, y, x + size, y + size, blackColor, 3);
        break;
    case TypeEntity ::BONUS_2:
        al_draw_filled_rectangle(x, y, x + size, y + size, al_map_rgb(200,200,100));
        al_draw_rectangle(x, y, x + size, y + size, blackColor, 3);
        break;
    case TypeEntity ::BONUS_3:
        al_draw_filled_rectangle(x, y, x + size, y + size, al_map_rgb(255,255,255));
        al_draw_rectangle(x, y, x + size, y + size, blackColor, 3);
        break;
    case TypeEntity ::BULLET:
        al_draw_filled_rectangle(x, y, x + size, y + size, al_map_rgb(240,240,70));
        al_draw_rectangle(x, y, x + size, y + size, blackColor, 3);
        break;
    default:
        al_draw_filled_rectangle(x, y, x + size, y + size, al_map_rgb(255,0,255));
        al_draw_rectangle(x, y, x + size, y + size, blackColor, 3);
        break;
    }
}

KeyBind LibAllegro::inputListener(const ALLEGRO_EVENT& event) const
{
    switch (event.keyboard.keycode) {
    case ALLEGRO_KEY_UP:
        return (KeyBind::ARROWUP);
    case ALLEGRO_KEY_DOWN:
        return (KeyBind::ARROWDOWN);
    case ALLEGRO_KEY_LEFT:
        return (KeyBind::ARROWLEFT);
    case ALLEGRO_KEY_RIGHT:
        return (KeyBind::ARROWRIGHT);
    case ALLEGRO_KEY_ENTER:
        return (KeyBind::ENTER);
    case ALLEGRO_KEY_BACKSPACE:
        return (KeyBind::RETURN);
    case ALLEGRO_KEY_F1:
        return (KeyBind::F1);
    case ALLEGRO_KEY_F2:
        return (KeyBind::F2);
    case ALLEGRO_KEY_F3:
        return (KeyBind::F3);
    case ALLEGRO_KEY_F4:
        return (KeyBind::F4);
    case ALLEGRO_KEY_F5:
        return (KeyBind::F5);
    case ALLEGRO_KEY_F6:
        return (KeyBind::F6);
    case ALLEGRO_KEY_F7:
        return (KeyBind::F7);
     default:
         break;
    }
    for (int key = 1; key <= 26; key++) {
        if (event.keyboard.keycode == key)
            return (static_cast<KeyBind>(key + 5));
    }
    return NONE;
}

KeyBind LibAllegro::eventListener() {
    ALLEGRO_EVENT event;
    KeyBind  key = KeyBind::NONE;

    while (!al_is_event_queue_empty(_event_queue)) {
        al_wait_for_event(_event_queue, &event);
        switch (event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            _running = false;
            break;
        case ALLEGRO_EVENT_TIMER:
            _redraw = true;
            break;
        case ALLEGRO_EVENT_KEY_CHAR:
            key = inputListener(event);
            break;
        default:
            break;
        }
    }
    return (key);
}

void LibAllegro::oneCycleDisplay() const
{
    if (_window) {
        al_flip_display();
    }
//    if (_redraw && al_is_event_queue_empty(_event_queue)) {
        //_redraw = false;
  //  }
}

void LibAllegro::displayMenu(const MenuInfo &menuInfo)
{
    (void)menuInfo;
    if (_redraw) {
        menu.drawBackgroundBoxes(menuInfo.getActiveBoxIdx());
        menu.drawSelectionList(menuInfo.getGraphList(), menuInfo.getGraphIdx(),
            30, 80);
        menu.drawSelectionList(menuInfo.getGameList(), menuInfo.getGameIdx(),
            980, 80);
        menu.drawUsername(menuInfo.getUserName());
        menu.drawScoreBoard(menuInfo.getGameScores());
        menu.displayMenu();
    }
}

void LibAllegro::oneCycleClear()
{
    al_clear_to_color(al_map_rgb(89,54,54));
}

extern "C" IDisplayModule *entryPoint()
{
    return (new LibAllegro());
}