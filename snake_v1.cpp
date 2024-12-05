#include "play.h"
int main()
{
    sf::Texture headTexture;
    if (!headTexture.loadFromFile("C:\\Users\\aniso\\source\\repos\\snake_v1\\Graphics\\head_down.png"))
    {
        return -1;
    }
    head_down.setTexture(headTexture);

    // Load additional textures and create sprites
    sf::Texture appleTexture, bodyBottomLeftTexture, bodyBottomRightTexture, bodyHorizontalTexture, bodyTopLeftTexture, bodyTopRightTexture, bodyVerticalTexture, headLeftTexture, headRightTexture, headUpTexture;

    if (!appleTexture.loadFromFile("Graphics\\apple.png") ||
        !bodyBottomLeftTexture.loadFromFile("Graphics\\body_bottomleft.png") ||
        !bodyBottomRightTexture.loadFromFile("Graphics\\body_bottomright.png") ||
        !bodyHorizontalTexture.loadFromFile("Graphics\\body_horizontal.png") ||
        !bodyTopLeftTexture.loadFromFile("Graphics\\body_topleft.png") ||
        !bodyTopRightTexture.loadFromFile("Graphics\\body_topright.png") ||
        !bodyVerticalTexture.loadFromFile("Graphics\\body_vertical.png") ||
        !headLeftTexture.loadFromFile("Graphics\\head_left.png") ||
        !headRightTexture.loadFromFile("Graphics\\head_right.png") ||
        !headUpTexture.loadFromFile("Graphics\\head_up.png"))
    {
        return -1;
    }

    apple.setTexture(appleTexture);
    body_bottomleft.setTexture(bodyBottomLeftTexture);
    body_bottomright.setTexture(bodyBottomRightTexture);
    body_horizontal.setTexture(bodyHorizontalTexture);
    body_topleft.setTexture(bodyTopLeftTexture);
    body_topright.setTexture(bodyTopRightTexture);
    body_vertical.setTexture(bodyVerticalTexture);
    head_left.setTexture(headLeftTexture);
    head_right.setTexture(headRightTexture);
    head_up.setTexture(headUpTexture);
 
    sf::Image table_img;
    table_img.create(table_size * 40, table_size * 40, sf::Color::White);

    for (int i = 0; i < table_size; ++i)
    {
        for (int j = 0; j < table_size; ++j)
        {
            sf::Color color = ((i + j) % 2 == 0) ? sf::Color::White : sf::Color(128, 128, 128);
            for (int x = 0; x < 40; ++x)
            {
                for (int y = 0; y < 40; ++y)
                {
                    table_img.setPixel(i * 40 + x, j * 40 + y, color);
                }
            }
        }
    }
    sf::Texture table_texture;
    table_texture.loadFromImage(table_img);
    sf::Sprite table;
    table.setTexture(table_texture);
    head_right.setPosition(80, 0);
    body_horizontal.setPosition(40, 0);

    snake[0] = body_horizontal;
    snake[1] = body_horizontal;
    snake[2] = head_right;
    apple.setPosition(40, 40);
    // Main loop
    window.setFramerateLimit(2);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(table);
        if (play())
        {
            //you lost
            window.clear(sf::Color::Red);
            sf::Text text;
            sf::Font font;
            font.loadFromFile("GOLGOE__.TTF");
            text.setString("YOU LOST!");
            text.setFont(font);
            text.setCharacterSize(40);
            text.setPosition(table_size / 2, table_size / 2);
            window.draw(text);
            window.display();
            sf::sleep(sf::seconds(1));
            window.close();
        }
        window.display();
    }

    return 0;
}
