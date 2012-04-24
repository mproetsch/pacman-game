#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <string>
#include <cstdio>


//
//Pacman class definition
class Pacman {

    public:
        Pacman();
        void setOrientation(int orient);
        int getOrientation() const;
        int getAnimationStage() const;
        void animate();
        sf::Sprite getCurrentSprite();
        void load();
        static const int MAX_STAGE = 6;


    private:
        sf::Texture *pacTexture;
        sf::Sprite *pacSprite;
        int orientation;
        int animationStage;
        bool isClosing;
};

Pacman::Pacman():
orientation(1),
animationStage(1),
isClosing(false)
{
    pacTexture = NULL;
    pacSprite = NULL;

}

void Pacman::setOrientation(int orient)
{
    orientation = orient;
}

int Pacman::getOrientation() const
{
    return orientation;
}

int Pacman::getAnimationStage() const
{
    return animationStage;
}

void Pacman::animate()
{
    if(animationStage == MAX_STAGE) {
        animationStage--;
        isClosing = true;
    }
    else if(animationStage == 1) {
        isClosing = false;
        animationStage++;
    }
    else if(isClosing)
        animationStage--;
    else
        animationStage++;

}

sf::Sprite Pacman::getCurrentSprite()
{
    return pacSprite[animationStage-1];
    printf("%d", animationStage);
}

void Pacman::load()
{
    pacTexture = new sf::Texture[Pacman::MAX_STAGE];
    pacSprite = new sf::Sprite[Pacman::MAX_STAGE];

    for(int i = 0; i < Pacman::MAX_STAGE; i++) {

    char get[20];
    sprintf(get, "resources/pac-%d.png", i+1);
    if(!pacTexture[i].loadFromFile(std::string(get)))
       return;
    pacTexture[i].bind();

    }

    for(int i = 1; i <= Pacman::MAX_STAGE; i++)
        pacSprite[i-1].setTexture(pacTexture[i-1]);


}



int main()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(640, 480), "SFML Pacman", sf::Style::Default, sf::ContextSettings(32));
    App.setFramerateLimit(60);

    // Load a sprite to display
//    sf::Texture texture;
//    if (!texture.loadFromFile("resources/background.png"))
//        return EXIT_FAILURE;

    //Allocate a new Pacman
    Pacman pac;
    pac.load();

    //Enable depth test for background and pacman sprites
    glEnable( GL_DEPTH_TEST );



    sf::Texture backgroundTex;
    if(!backgroundTex.loadFromFile("resources/background.png"))
        return EXIT_FAILURE;
    sf::Sprite backgroundSprite(backgroundTex);





    //Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return EXIT_FAILURE;

    sf::Text text;
    text.setFont(font);

    //Make a clock
    //sf::Clock clock;
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

        //Draw the background
        App.draw(backgroundSprite);

        //int elapsed = clock.getElapsedTime().asMilliseconds() % 50;

        //Get the next animation of Pacman and draw it to App
        pac.animate();
        App.draw(pac.getCurrentSprite());

        //Draw the time
        //char timestr[20];
        //sprintf(timestr, "%d", elapsed);
        //text.setString(std::string(timestr));
        //App.draw(text);

        // Update the window
        App.display();
    }

    return EXIT_SUCCESS;
}
