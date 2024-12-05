#include "play.h"
int dirx = 40, diry = 0;
sf::Sprite snake[table_size * table_size];
int snake_lenght = 3;
sf::Sprite apple, body_bottomleft, body_bottomright, body_horizontal, body_topleft, body_topright, body_vertical, head_left, head_right, head_up, head_down;
sf::RenderWindow window(sf::VideoMode(40*table_size, 40*table_size), "Snake");
bool lost()
{
	// Get the head position
	sf::Vector2f head_pos = snake[snake_lenght - 1].getPosition();

	// Check for border collision
	if (head_pos.x < 0 || head_pos.x >= window.getSize().x || head_pos.y < 0 || head_pos.y >= window.getSize().y)
	{
		return true;
	}

	// Check for self collision
	for (int i = 0; i < snake_lenght - 1; ++i)
	{
		if (snake[i].getPosition() == head_pos)
		{
			return true;
		}
	}

	return false;
}

void placeApple()
{
	std::srand(std::time(nullptr)); // Seed the random number generator

	// Create a list of all possible positions
	std::vector<sf::Vector2f> positions;
	for (int x = 0; x < window.getSize().x; x += 40)
	{
		for (int y = 0; y < window.getSize().y; y += 40)
		{
			positions.emplace_back(x, y);
		}
	}

	// Remove positions occupied by the snake
	for (int i = 0; i < snake_lenght; ++i)
	{
		auto it = std::remove(positions.begin(), positions.end(), snake[i].getPosition());
		positions.erase(it, positions.end());
	}

	// Select a random position from the remaining positions
	if (!positions.empty())
	{
		int index = std::rand() % positions.size();
		apple.setPosition(positions[index]);
	}
}
int play()
{
	//unless a fruit is eaten the body will be moved using dir
	bool moved = false;
	sf::Vector2f ex_head;
	ex_head = snake[snake_lenght - 1].getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && diry==0)
	{
		//direction changed
		moved = true;
		dirx = 0;
		diry = -40;
		snake[snake_lenght - 1] = head_up;
		snake[snake_lenght - 1].setPosition(ex_head.x + dirx, ex_head.y + diry);

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && dirx==0)
	{
		moved = true;
		dirx = 40;
		diry = 0;
		snake[snake_lenght - 1] = head_right;
		snake[snake_lenght - 1].setPosition(ex_head.x + dirx, ex_head.y + diry);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)&& dirx==0)
	{
		moved = true;
		dirx = -40;
		diry = 0;
		snake[snake_lenght - 1] = head_left;
		snake[snake_lenght - 1].setPosition(ex_head.x + dirx, ex_head.y + diry);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && diry==0)
	{
		moved = true;
		dirx = 0;
		diry = 40;
		snake[snake_lenght - 1] = head_down;
		snake[snake_lenght - 1].setPosition(ex_head.x + dirx, ex_head.y + diry);
	}
	else
	{
		//move head same direction
		snake[snake_lenght - 1].move(dirx, diry);

	}
	//head is moved to proper position
	if (apple.getPosition() == snake[snake_lenght - 1].getPosition())
	{
		//fruit eaten
		snake_lenght++;
		snake[snake_lenght - 1] = snake[snake_lenght - 2];
		//snake[snake_lenght - 1].setPosition(snake[snake_lenght - 2].getPosition());
		if (moved == false)
		{
			//adding a new straight body
			if (dirx == 0)
			{
				snake[snake_lenght - 2] = body_vertical;
				snake[snake_lenght - 2].setPosition(ex_head);
			}
			else if (diry == 0)
			{
				snake[snake_lenght - 2] = body_horizontal;
				snake[snake_lenght - 2].setPosition(ex_head);
			}
		}
		else
		{
			//adding a curved body
			if (dirx == 0)
			{
				if (snake[snake_lenght - 3].getPosition().x < snake[snake_lenght - 1].getPosition().x && diry == -40)
				{
					snake[snake_lenght - 2] = body_topleft;
				}
				else if (snake[snake_lenght - 3].getPosition().x > snake[snake_lenght - 1].getPosition().x && diry == -40)
				{
					snake[snake_lenght - 2] = body_topright;
				}
				else if (snake[snake_lenght - 3].getPosition().x < snake[snake_lenght - 1].getPosition().x && diry == 40)
				{
					snake[snake_lenght - 2] = body_bottomleft;
				}
				else if (snake[snake_lenght - 3].getPosition().x > snake[snake_lenght - 1].getPosition().x && diry == 40)
				{
					snake[snake_lenght - 2] = body_bottomright;
				}
			}
			else if (diry == 0)
			{
				if (snake[snake_lenght - 3].getPosition().y < snake[snake_lenght - 1].getPosition().y && dirx == -40)
				{
					snake[snake_lenght - 2] = body_topleft;
				}
				else if (snake[snake_lenght - 3].getPosition().y > snake[snake_lenght - 1].getPosition().y && dirx == -40)
				{
					snake[snake_lenght - 2] = body_bottomleft;
				}
				else if (snake[snake_lenght - 3].getPosition().y < snake[snake_lenght - 1].getPosition().y && dirx == 40)
				{
					snake[snake_lenght - 2] = body_topright;
				}
				else if (snake[snake_lenght - 3].getPosition().y > snake[snake_lenght - 1].getPosition().y && dirx == 40)
				{
					snake[snake_lenght - 2] = body_bottomright;
				}
			}
			snake[snake_lenght - 2].setPosition(ex_head);
		}
		for (int i = 0; i < snake_lenght; i++)
		{
			window.draw(snake[i]);
		}
		placeApple();
		window.draw(apple);
	}
	else
	{
		if (moved == false)
		{
			int found = -1;
			for (int i = 0; i < snake_lenght - 1; i++)
			{
				if (snake[i].getTexture() == body_bottomleft.getTexture() ||
					snake[i].getTexture() == body_bottomright.getTexture() ||
					snake[i].getTexture() == body_topright.getTexture() ||
					snake[i].getTexture() == body_topleft.getTexture())
				{
					found = i;
					
				}
				if (i != snake_lenght - 2)
				{
					snake[i] = snake[i + 1];
				}
				
				snake[i].setPosition(snake[i + 1].getPosition());
			}
			snake[snake_lenght - 2].setPosition(ex_head);
			if (found != -1)
			{
				if (snake[found + 1].getTexture() == head_left.getTexture() ||
					snake[found + 1].getTexture() == head_right.getTexture() ||
					snake[found + 1].getTexture() == body_horizontal.getTexture()
					)
				{
					snake[found].setTexture(*body_horizontal.getTexture());
				}
				else
				{
					snake[found].setTexture(*body_vertical.getTexture());
				}
			}
			for (int i = 0; i < snake_lenght; i++)
			{
				window.draw(snake[i]);
			}
			window.draw(apple);
		}
		else
		{
			sf::Sprite aux;
			aux= snake[snake_lenght - 2];
			if (dirx == 0)
			{
				if (snake[snake_lenght-3].getPosition().x < snake[snake_lenght - 1].getPosition().x && diry == -40)
				{
					snake[snake_lenght - 2] = body_topleft; 
				}
				else if (snake[snake_lenght - 3].getPosition().x > snake[snake_lenght - 1].getPosition().x && diry == -40)
				{
					snake[snake_lenght - 2] = body_topright;
				}
				else if (snake[snake_lenght - 3].getPosition().x < snake[snake_lenght - 1].getPosition().x && diry == 40)
				{
					snake[snake_lenght - 2] = body_bottomleft;
				}
				else if (snake[snake_lenght - 3].getPosition().x > snake[snake_lenght - 1].getPosition().x && diry == 40)
				{
					snake[snake_lenght - 2] = body_bottomright;
				}
			}
			else if (diry == 0)
			{
				if (snake[snake_lenght - 3].getPosition().y < snake[snake_lenght - 1].getPosition().y && dirx == -40)
				{
					snake[snake_lenght - 2] = body_topleft;
				}
				else if (snake[snake_lenght - 3].getPosition().y > snake[snake_lenght - 1].getPosition().y && dirx == -40)
				{
					snake[snake_lenght - 2] = body_bottomleft;
				}
				else if (snake[snake_lenght - 3].getPosition().y < snake[snake_lenght - 1].getPosition().y && dirx == 40)
				{
					snake[snake_lenght - 2] = body_topright;
				}
				else if (snake[snake_lenght - 3].getPosition().y > snake[snake_lenght - 1].getPosition().y && dirx == 40)
				{
					snake[snake_lenght - 2] = body_bottomright;
				}
			}
			snake[snake_lenght - 2].setPosition(ex_head);
			for (int i = 0; i < snake_lenght - 3; i++)
			{

				snake[i] = snake[i + 1];
				window.draw(snake[i]);
			}

			snake[snake_lenght - 3] = aux;
			window.draw(snake[snake_lenght - 3]);
			window.draw(snake[snake_lenght - 2]);
			window.draw(snake[snake_lenght - 1]);
			window.draw(apple);
		}
	}
	return lost();
}
