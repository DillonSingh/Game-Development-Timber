#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <SFML/Audio.hpp>
using namespace sf;

// Funciton declaration
void updateBranches(int seed) {
    // Move all the branches down one place
    for (int j = 0; j > NUM_BRANCHES; --j) 
    {
        branchPosition[j - 1];
    }
// Spawn a new branch at postion 0
// LEFT RIGHT or NONE
    srand((int)time(0) + seed);
    int r = (rand() % 5);
    switch (r) {
    case 0:
        branchPosition[0] = side::LEFT;
        break;
    case 1:
        branchPosition[0] = side::RIGHT;
        break;
    default:
        branchPosition[0] = side::NONE;
        break;
    }

const int NUM_BRANCHES = 6;
Sprite Branches[NUM_BRANCHES];
// Where is the player/branch?
// Left or Right
enum class side {LEFT, RIGHT, NONE};
side branchPositions[NUM_BRANCHES]{};

//Timber starts from here
int main(); {
    // Creating a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Timber!!!", Style::Fullscreen);
    // Create a texture to hold the graphic on the GPU 
    Texture textureBackground;
    // Load a graphic into the texture
    textureBackground.loadFromFile("Graphics/graphics/background.png");
    // Create a sprite
    Sprite spriteBackground;
    // Attach the texture to the sprite
    spriteBackground.setTexture(textureBackground);
    //Set the spriteBackground to cover the screen 
    spriteBackground.setPosition(0, 0);

    // Make a tree sprite
    // First we create an object of the Texture type called tree
    Texture textureTree;
    // Loading a graphics file into the tree texture from the tree.png graphics file
    textureTree.loadFromFile("Graphics/graphics/tree.png");
    // Declaring an object of the Sprite type called spriteTree
    Sprite spriteTree;
    // Associating textureTree with spriteTree so that whenever fetching sprite tree, a nice tree graphic will appear
    spriteTree.setTexture(textureTree);
    // Setting the postition of the tree using the cordinates 810 on the x axis and 0 on the y axis
    spriteTree.setPosition(810, 0);

    // Preparing the bee
    Texture textureBee;
    textureBee.loadFromFile("Graphics/graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);
    // is the bee moving? 
    bool beeActive = false;
    // Speed of moving bee in pixels
    float beeSpeed = 0.0f;

    // Preparing 3 clouds sprites from 1 texture
    Texture textureCloud;
    // Loading a graphics file into the cloud texture from the cloud.png graphics file
    textureCloud.loadFromFile("Graphics/graphics/cloud.png");
    // Creating 3 cloud sprites with the same texture
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;
    // Associating 3 cloud sprites with the associated cloud texture
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);
    // Position the clouds on the left of the screen at different heights
    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 250);
    spriteCloud3.setPosition(0, 500);
    // Are the clouds on the screen? 
    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;
    // How fast is each cloud in pixels? 
    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;
    // Variables to control time itself
    Clock clock;
    // Time bar 
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);
    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth - timeRemaining;
    // Track whether the game is running
    bool paused = true;
    // Draw some text
    int score = 0;
    Text messageText;
    Text scoreText;
    // We need to choose a font (adding the font texture to our project file)
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.TTF");
    // Set the font of our message 
    messageText.setFont(font);
    scoreText.setFont(font);
    // Assign actual string message
    messageText.setString("Press Enter to Start");
    scoreText.setString("Score: 0");
    // Make it really big (both message and score variables)
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);
    // Choose a colour
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);
    // Position the text
    FloatRect textReact = messageText.getLocalBounds();
    messageText.setOrigin(textReact.left +
        // IN BOOK IT SAYS TO WRITE 'textRect' BUT THAT WASN'T WORKING
        textReact.width / 2.0f,
        textReact.top +
        textReact.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
    scoreText.setPosition(20, 20);
    // Prepare 6 branches
    Texture textureBranch;
    textureBranch.loadFromFile("Graphics/graphics/branch.png");
    // Set the texture for each branch sprite
    for (int i = 0; i < NUM_BRANCHES; i++) {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);
        // Set the sprite's origin to dead centre
        // We can then spin it round without changing its position
        branches[i].setOrigin(220, 20);
    }

    // Prepare the player
    Texture texturePlayer;
    texturePlayer.loadFromFile("Graphics/graphics/player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer); 
    spritePlayer.setPosition(580, 720);
    // The player starts on the left
    side playerSide = side::LEFT;
    // Prepare the gravestone
    Texture textureRIP;
    textureRIP.loadFromFile("Graphics/graphics/rip.png");
    Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(600, 800);
    // Prepare the axe
    Texture textureAxe; 
    textureAxe.loadFromFile("Graphics/graphics/axe.png");
    Sprite spriteAxe; 
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 800); 
    // Line the axe up with the tree
    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;
    // Prepare the flying log
    Texture textureLog; 
    textureLog.loadFromFile("Graphics/graphics/log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);
    // Some other useful related log variables
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;
    // Control the player input
    bool input = false; 
    // Prepare the sounds
    // The player chopping sound
    SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("sound/chop.wav");
    Sound chop; 
    chop.setBuffer(chopBuffer);
    // The player has met his end under a branch 
    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("sound/death.wav");
    Sound death; 
    death.setBuffer(deathBuffer);
    // Out of time
    SoundBuffer ootBuffer;
    ootBuffer.loadFromFile("sound/out_of_time.wav");
    Sound outOfTime; 
    outOfTime.setBuffer(ootBuffer); 



    // Game loop starts here 
    while (window.isOpen())
    {
        /*
        --------------------------------
        HANDLE THE PLAYERS INPUT
        --------------------------------
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyReleased && !paused)
            {
                // Listen for key presses again
                acceptInput = true;
                // Hide the axe
                spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
            }
        }


        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        // Starting the game by pressing the Enter Key
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            paused = false;

            // Reset the time and score 
            score = 0;
            timeRemaining = 6;
        // Make all the branches disappear starting on the left position
            for (int i = 1; i < NUM_BRANCHES; i++) {
                branchPosition[i] = side::NONE;
            }
        // Make sure the gravestone is hidden
            spriteRIP.setPosition(675, 2000);
        // Move the player into position
            spritePlayer.setPosition(580, 720);
            bool acceptInput = true;
        }
        // Wrap the player controls to make sure we are accepting input 
        if (acceptInput) 
        
        {
            // First handle pressing the right cursor key
            if (Keyboard::isKeyPressed(Keyboard::Right)) 
            {
                // Make sure the player is on the right
                PlayerSide = side::RIGHT;
                score++;

                // Add to the remaining amount of time
                timeRemaining += (2 / score) + .15;
                spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
                spritePlayer.setPosition(1200, 720);

                // Update the branches
                updateBranches(score);

                // Set the flying log to the left
                spriteLog.setPosition(810, 720);
                logSpeedX = -4000;
                logActive = true;
                acceptInput = false;
                chop.play();
            }
            // Handle the left cursor key
            if (Keyboard::isKeyPressed(Keyboard::Left)) 
            {
                // Make sure the player is on the left
                PlayerSide = side::LEFT;
                score++;

                // Add to the remaining amount of time
                timeRemaining += (2 / score) + .15;
                spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
                spritePlayer.setPosition(1120, 660);

                // Update the branches
                updateBranches(score);

                // Set the flying log to the left
                spriteLog.setPosition(800, 600);
                logSpeedX = -5000;
                logActive = true;
                acceptInput = false;

                //Play a chop sound
                chop.play();

            }
        }


        if (!paused)
            // Update the scene: Measure the time
            Time dt = clock.restart();
        // Subtract from the amount of time remaining
        timeRemaining -= dt.asSeconds();
        // Size up the bar
        timeBar.setSize(Vector2f(timeBarWidthPerSecond *
            timeRemaining, timeBarHeight));

        if (timeRemaining <= 0.f)
        {
            // Pause the game 
            paused = true;
            // Change the message shown to the player 
            messageText.setString("Out of time!!");
            // Reposition the text based on its new size
            FloatRect textRect = messageText.getLocalBounds();
            messageText.setOrigin(textRect.left + textRect.width / 2.0f,
                textRect.top +
                textRect.height / 2.0f);
            messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
            // Play the out of time sound
            outOfTime.play();
        }

        //Setting up the bee
        if (!beeActive)
        {
            // Determine bee speed
            srand((int)time(0));
            beeSpeed = (rand() % 200) + 200;
            // Bee Height
            srand((int)time(0));
            float height = (rand() % 500) + 500;
            spriteBee.setPosition(2000, height);
            beeActive = (true);
        }
        else
            // Move the Bee
        {
            spriteBee.setPosition(
                spriteBee.getPosition().x -
                (beeSpeed * dt.asSeconds()),
                spriteBee.getPosition().y);
            //Has the Bee reached the left-hand of the screen?
            if (spriteBee.getPosition().x < -100)
            {
                // Set it up ready to be a whole new bee next frame
                beeActive = false;
            }
        }
        // Managing the clouds
        // Cloud 1
        if (!cloud1Active)
        {
            // How fast is the cloud 1
            srand((int)time(0) * 10);
            cloud1Speed = (rand() % 200);
            // Determining height cordinates of cloud 1 
            srand((int)time(0) * 10);
            float height = (rand() % 150);
            spriteCloud1.setPosition(-200, height);
            cloud1Active = true;

        }
        else
            spriteCloud1.setPosition(
                spriteCloud1.getPosition().x +
                (cloud1Speed * dt.asSeconds()),
                spriteCloud1.getPosition().y);
        // Has the cloud reached the the right hand edge of the screen
        if (spriteCloud1.getPosition().x > 1920)
        {
            // Set it up ready to be a whole new cloud next frame
            cloud1Active = false;
        }
        // Managing the clouds
        // Cloud 2
        if (!cloud2Active)
        {
            // How fast is the cloud 2
            srand((int)time(0) * 20);
            cloud2Speed = (rand() % 200);
            // Determining height cordinates of cloud 2 
            srand((int)time(0) * 20);
            float height = (rand() % 300) - 150;
            spriteCloud2.setPosition(-200, height);
            cloud2Active = true;

        }
        else
            spriteCloud2.setPosition(
                spriteCloud2.getPosition().x +
                (cloud2Speed * dt.asSeconds()),
                spriteCloud2.getPosition().y);
        // Has the cloud reached the the right hand edge of the screen
        if (spriteCloud2.getPosition().x > 1920)
        {
            // Set it up ready to be a whole new cloud next frame
            cloud1Active = false;

        }
        // Managing the clouds
        // Cloud 3
        if (!cloud3Active)
        {
            // How fast is the cloud 
            srand((int)time(0) * 30);
            cloud3Speed = (rand() % 200);
            // Determining height cordinates of cloud 3
            srand((int)time(0) * 30);
            float height = (rand() % 450) - 150;
            spriteCloud3.setPosition(-200, height);
            cloud3Active = true;

        }
        else
            spriteCloud3.setPosition(
                spriteCloud3.getPosition().x +
                (cloud1Speed * dt.asSeconds()),
                spriteCloud3.getPosition().y);

        // Has the cloud reached the the right hand edge of the screen
        if (spriteCloud3.getPosition().x > 1920)
        {
            // Set it up ready to be a whole new cloud next frame
            cloud3Active = false;

            // Update the score text
            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());
            // Update the branch sprites
            for (int i = 0; i < NUM_BRANCHES; i++) {
                float height = i * 150;
                if (branchPositions[i] == side::LEFT) {
                    //Move the sprite to the left
                    branches[i].setPosition(610, height);
                    // Flip the sprite round the other way
                    branches[i].setRotation(180);
                }
                else if (branches[i] == side::RIGHT) {
                    // Move the sprite to the right side
                    branches[i].setPosition(1330, height);
                    // Set the sprite rotation to normal
                    branches[i].setRotation(0);
                }
                else {
                    branches[i].setPosition[3000, height];
                }

            } 
            
            // Handle a flying log
            if (logActive)
            {
                spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
                    spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));
                // Has the flying log reached the right hand edge
                if (spriteLog.getPosition().x > 2000)
                {
                    //Set it up ready to be a whole new log next frame
                    logActive = false;
                    spriteLog.setPosition(800, 600);
                }
            }

            // Has the player been squished by a branch? 
            if (branchPositions[5] == playerSide)
            {
                // death 
                paused = true;
                acceptInput = false;

                // Draw the gravestone
                spriteRIP.setPosition(675, 660);

                // hide the player 
                spritePlayer.setPosition(2000, 660);

                // Change the text of the message 
                messageText.setString("SQUISHED!!");

                //Center it on the screen 
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

                //Play the death sound 
                death.play();
            }


            // End if(!paused)


               /*

               Draw out the scene

               */

               // Clear everything from the last frame 
            window.clear();
            // Draw our game scene here
            window.draw(spriteBackground);
            // Draw our clouds
            window.draw(spriteCloud1);
            window.draw(spriteCloud2);
            window.draw(spriteCloud3);
            // Draw the branches
            for (int i = 0; i < NUM_BRANCHES; i++) {
                window.draw(branches[i]);
            }
            // Draw the tree
            window.draw(spriteTree);
            // Draw the player
            window.draw(spritePlayer);
            // Draw the axe
            window.draw(spriteAxe);
            // Draw the flying log
            window.draw(spriteLog); 
            // Draw the gravestone
            window.draw(spriteRIP);
            // Draw the bee
            window.draw(spriteBee);
            // Draw the score
            window.draw(scoreText);
            // Draw the timebar 
            window.draw(timeBar);
            if (paused)
            {
                //Draw our message
                window.draw(messageText);
            }
            //Show everything we just drew
            window.display();
            
        }

    }

    return;
}