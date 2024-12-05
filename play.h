#ifndef PLAY_H
#define PLAY_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <vector>
#define table_size 10
extern sf::Sprite snake[table_size * table_size];
extern int snake_lenght;
extern sf::Sprite apple, body_bottomleft, body_bottomright, body_horizontal, body_topleft, body_topright, body_vertical, head_left, head_right, head_up, head_down;
extern sf::RenderWindow window;
int play();
#endif