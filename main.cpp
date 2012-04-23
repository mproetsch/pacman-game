#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

int main()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML window");

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;

    sf::Vector2u size( texture.getSize() );

    uint width = size.x;
    uint height = size.y;

    //sf::RenderWindow App(sf::VideoMode(width, height), "SFML window");


    //Load a sprite with the image data from texture
    sf::Sprite sprite(texture);

    //Great a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return EXIT_FAILURE;

    sf::Text text("Hello world!", font, 30);

	// Start the game loop
    while (App.isOpen())
    {
        // Process events
        sf::Event event;
        while (App.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                App.close();
        }

        // Clear screen
        App.clear();

        // Draw the sprite
        App.draw(sprite);

        //Draw the string
        App.draw(text);

        // Update the window
        App.display();
    }

    return EXIT_SUCCESS;
}
