#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include <string>
#include <cstdio>

#define ROWS 29 //Rows of dots
#define COLS 26 //Cols of dots

#define WIDTH 404 //Starting px of bg tex to draw dots
#define HEIGHT 396 //Ending px of bg tex to draw dots

#define XOFFSET 117 //Width to start drawing dots
#define YOFFSET 28

//
//dotarray class definition: holds location of dots on the grid
class dotarray {

    public:
        dotarray();
        int rows, cols;
        int boardWidth, boardHeight;
        double spacingX, spacingY;
        bool hasDot[ROWS][COLS];


        int numDotsRemaining();

        bool isDot(int row, int col);
        void eat(int row, int col);

};

dotarray::dotarray():
rows(ROWS),
cols(COLS),
boardWidth(WIDTH),
boardHeight(HEIGHT),
spacingX( (double)WIDTH / (double)COLS ),
spacingY( (double)HEIGHT / (double)ROWS )
{
    int i, j;

    ////////////////
    //Fill first row
    for(j = 0; j < cols; j++)
    {
        if(j < 12)
            hasDot[0][j] = true;

        else if(j > 13)
            hasDot[0][j] = true;

        else
            hasDot[0][j] = false;
    }

    /////////////////////////////////
    //Fill second, third, fourth rows
    for(i = 1; i <= 3; i++)
        for(j = 0; j < cols; j++)
        {
            if(j == 0 ||
               j == 5 ||
               j == 11 ||
               j == 14 ||
               j == 20 ||
               j == 25 )
                hasDot[i][j] = true;
            else
                hasDot[i][j] = false;
        }

    ////////////////
    //Fill fifth row
    for(j = 0; j < cols; j++)
        hasDot[4][j] = true;

    /////////////////////////////
    //Fill sixth and seventh rows
    for(i = 5; i <= 6; i++)
        for(j = 0; j < cols; j++)
        {
            if(j == 0 ||
               j == 5 ||
               j == 8 ||
               j == 17 ||
               j == 20 ||
               j == 25 )
                hasDot[i][j] = true;

            else
                hasDot[i][j] = false;
        }

    /////////////////
    //Fill eighth row
    for(j = 0; j < cols; j++)
    {
        if(j <= 5)
            hasDot[7][j] = true;
        else if(j >= 8 && j <= 11)
            hasDot[7][j] = true;
        else if(j >= 14 && j <= 17)
            hasDot[7][j] = true;
        else if(j >= 20)
            hasDot[7][j] = true;
        else
            hasDot[7][j] = false;
    }

    ////////////////
    //Fill rows 9-19
    for(i = 8; i <= 18; i++)
        for(j = 0; j < cols; j++)
        {
            if(j == 5 || j == 20)
                hasDot[i][j] = true;
            else
                hasDot[i][j] = false;
        }

    /////////////
    //Fill row 20
    for(j = 0; j < cols; j++)
    {
        if(j <= 11 || j >= 14)
            hasDot[19][j] = true;
        else
            hasDot[19][j] = false;
    }

    /////////////////////
    //Fill rows 21 and 22
    for(i = 20; i <= 21; i++)
        for(j = 0; j < cols; j++)
        {
            if(j == 0 ||
               j == 5 ||
               j == 11 ||
               j == 14 ||
               j == 20 ||
               j == 25 )
                hasDot[i][j] = true;

            else
                hasDot[i][j] = false;
        }

    /////////////////////////////
    //Fill row 23 (hello Pacman!)
    for(j = 0; j < cols; j++)
    {
        if(j < 12)
            hasDot[22][j] = true;
        else if(j > 13)
            hasDot[22][j] = true;
        else
            hasDot[22][j] = true;
    }

    /////////////////////
    //Fill rows 24 and 25
    for(i = 23; i <= 24; i++)
        for(j = 0; j < cols; j++)
        {
            if(j == 2 ||
               j == 5 ||
               j == 8 ||
               j == 17 ||
               j == 20 ||
               j == 23 )
                hasDot[i][j] = true;

            else
                hasDot[i][j] = false;

        }

    /////////////
    //Fill row 26
    for(j = 0; j < cols; j++)
    {
        if(j <= 5)
            hasDot[25][j] = true;
        else if(j >= 8 && j <= 11)
            hasDot[25][j] = true;
        else if(j >= 14 && j <= 17)
            hasDot[25][j] = true;
        else if(j >= 20)
            hasDot[25][j] = true;
        else
            hasDot[25][j] = false;
    }

    /////////////////////
    //Fill rows 27 and 28
    for(i = 26; i <= 27; i++)
        for(j = 0; j < cols; j++)
        {
            if(j == 0 ||
               j == 11 ||
               j == 14 ||
               j == 25 )
                hasDot[i][j] = true;

            else
                hasDot[i][j] = false;
        }

    //////////////////////////
    //Fill row 29 (FINAL ROW!)
    for(j = 0; j < cols; j++)
        hasDot[28][j] = true;


}

bool dotarray::isDot(int row, int col)
{
    return hasDot[row][col];
}

void dotarray::eat(int row, int col)
{
    hasDot[row][col] = false;
}

//
//Pacman class definition
class Pacman {

    public:
        Pacman();

        //Deal with where this pacman can go
        bool canSetOrientation();
        void setOrientation(int orient);
        int getOrientation() const;

        //Process which sprite is current for this pacman
        void animate();


        void move();
        float currentX, currentCenterX;
        float currentY, currentCenterY;
        bool canMove(int x, int y);
        sf::Texture getCurrentTexture() const;
        sf::Vector2u pos;
        void load();
        static const int MAX_STAGE = 6;


    private:
        sf::Texture *pacTexture;
        int orientation;
        int wantToMove;
        int rows[ROWS], cols[COLS];
        int animationStage;
        bool isClosing;

};

Pacman::Pacman():
orientation(4), //right
animationStage(1),
isClosing(false),
currentX(-320.0),
currentY(-338.0),
currentCenterX(currentX - 15),
currentCenterY(currentY - 15)
{
    //pos = sf::Vector2u(  );
    pacTexture = NULL;

}



void Pacman::setOrientation(int orient)
{
    //1 = up, 2 = down, 3 = left, 4 = right
    orientation = orient;

}

int Pacman::getOrientation() const
{
    return orientation;
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

void Pacman::move()
{
    if(orientation == 1)
        currentY+= 2;
    else if(orientation == 2)
        currentY-= 2;
    else if(orientation == 3)
        currentX+= 2;
    else if(orientation == 4)
        currentX-= 2;

    //check for wrap
    if(abs(currentCenterX - currentCenterY) <= 0.01) {
        currentCenterX = 492;
        currentX = currentCenterX + 15;
    }

    else if(abs(currentCenterX - currentCenterY) <= 0.01) {
        currentCenterX = 145;
        currentX = currentCenterX + 15;
    }


    //Check for bounds

}

//
//Return the address of the current texture in memory
sf::Texture Pacman::getCurrentTexture() const
{
    return pacTexture[ (orientation-1)*(MAX_STAGE)
                    + (animationStage-1)];
}



void Pacman::load()
{

    sf::Image pacImg[2*MAX_STAGE];
    pacTexture = new sf::Texture[4*MAX_STAGE];

    //Load all images, which comes out to 2*MAX_STAGE
    for(int i = 0; i < 2*MAX_STAGE; i++) {

        if(i < MAX_STAGE) {
            //Load horizontal sprites
            char get[20];
            sprintf(get, "resources/pac-%d.png", i+1);
            if(!pacImg[i].loadFromFile(std::string(get)))
                return;
        }
        else {
            char get[20];
            sprintf(get, "resources/pac-vert-%d.png", i-MAX_STAGE + 1);
            if(!pacImg[i].loadFromFile(std::string(get)))
                return;
        }
    }

    //Right-facing images are stored in pacImg[0] - pacImg[MAX_STAGE-1],
    //Up-facing images are stored in pacImg[MAX_STAGE] - pacImg[2*MAX_STAGE -1]
    //So load all dat shyt into pacTexture
    for(int i = 0; i < 4*MAX_STAGE; i++) {

        if(i < MAX_STAGE) {
            //Right-facing images
            //Don't need to perform transform
            //Load these images into fourth section of pacTexture
            pacTexture[i+3*MAX_STAGE].loadFromImage(pacImg[i]);
        }
        else if(i < 2*MAX_STAGE) {
            //Upward-facing images
            //Don't need to perform transform
            //Load these images into first section of pacTexture
            pacTexture[i-MAX_STAGE].loadFromImage(pacImg[i]);
        }
        else if(i < 3*MAX_STAGE) {
            //Make these the downward-facing images by flipping the
            //upward-facing pacmans in pacImg.
            //Then load these images into second section of pacTexture
            pacImg[i-MAX_STAGE].flipVertically();
            pacTexture[i-MAX_STAGE].loadFromImage(pacImg[i-MAX_STAGE]);
        }
        else {
            //Make these the left-facing images by flipping
            //the right-facing pacmans in pacImg
            //Then load these images into the third section of pacTexture
            pacImg[i-3*MAX_STAGE].flipHorizontally();
            pacTexture[i-MAX_STAGE].loadFromImage(pacImg[i-3*MAX_STAGE]);
        }
    }

}


///////////////
///////////////
//Main function
int main()
{
    //Enable depth test for background and pacman sprites
    //glEnable( GL_DEPTH_TEST );

    // Create the main window
    sf::RenderWindow App(sf::VideoMode(640, 480), "SFML Pacman",
                         sf::Style::Default,
                         sf::ContextSettings(32));
    App.setFramerateLimit(60);
    //Initialize glew
    if( glewInit() != GLEW_OK )
        return EXIT_FAILURE;


    //and allocate an array of vertices
    GLuint data;
    //Fill vertex buffer with data
    const GLfloat vertices[] = {
        -1.0f, 1.0f,
        -0.9f, 0.9f,
        -0.9f, 1.f,

        0.f, 0.f,
        0.f, 0.5f,
        -0.5f, 0.5f };
    //Fill up indices
    const GLubyte indices[] = {
        0, 1,  2, 3,
        4, 5,  6, 7  };

    //glGenBuffers(1, &data);
    //Load square verts into the buffer object, GL_ARRAY_BUFFER
    //glBindBuffer( GL_ARRAY_BUFFER, data );
    //glBufferData( GL_ARRAY_BUFFER, 4*3*sizeof( GLfloat ), vertices, GL_STATIC_DRAW );

    // Enable Z-buffer read and write
    //glEnable(GL_DEPTH_TEST);
    //glDepthMask(GL_TRUE);
    //glClearDepth(1.f);


    //Allocate a new dot grid
    dotarray dots;
    //Allocate a new Pacman
    Pacman pac;
    pac.load();

    //Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return EXIT_FAILURE;
    sf::Text text;
    text.setFont(font);

    //Load the bg sprite
    sf::Texture backgroundTex;
    if(!backgroundTex.loadFromFile("resources/background.png"))
        return EXIT_FAILURE;
    sf::Sprite backgroundSprite(backgroundTex);



	// Start the game loop

	sf::Sprite currentSprite;

    while (App.isOpen())
    {
        // Process events
        sf::Event event;
        while (App.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                App.close();

            if(event.type == sf::Event::KeyPressed) {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    pac.setOrientation(1);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    pac.setOrientation(2);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    pac.setOrientation(3);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    pac.setOrientation(4);
            }
        }

        //pac.setOrientation( (int)(clock.getElapsedTime().asSeconds()) % 4 + 1);

        //Get the next animation of pacman, and draw it against the background
        pac.animate();
        pac.move();
        const sf::Texture currentTexture = pac.getCurrentTexture();
        currentSprite.setTexture(currentTexture);
        currentSprite.setOrigin(pac.currentX, pac.currentY);

        App.pushGLStates();
        App.draw(backgroundSprite);
        App.draw(currentSprite);
        App.popGLStates();





        /*
        //Draw the mouse position
        char mousestr[20];
        float mouseposX = sf::Mouse::getPosition(App).x * 200.f /
                            App.getSize().x - 100.f;
        sprintf(mousestr, "%10f", mouseposX);
        text.setString(std::string(mousestr));
        App.pushGLStates();
        App.draw(text);
        App.popGLStates();
        */


        //Clear the depth buffer
        glClear( GL_DEPTH_BUFFER_BIT );
        //Activate the window
        App.setActive();
        //Draw the square
        //Enable drawing from vertex arrays


        /************ DRAW SOME DOTS ***********
        glEnableClientState( GL_VERTEX_ARRAY );

        for(int i = 0; i < dots.rows; i++)
            for(int j = 0; j < dots.cols; j++) {

                if(dots.hasDot[i][j]) {
                    //DO OPENGL HERE
                }

            }

        glDrawArrays( GL_TRIANGLES, 0, 6 * dots.numDotsRemaining );

        glDisableClientState( GL_VERTEX_ARRAY );
        /************ DRAW SOME DOTS *************/



        // Update the window
        App.display();
    }

    return EXIT_SUCCESS;
}
