#include <SFML/Graphics.hpp>

#include "Maze.h"
#include "Characters.h"
#include "Player.h"
#include "Movement.h"
#include "Enemy.h"
#include "Collectibles.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

//function to create wall graphics in the maze
sf::Sprite createWall(int x, int y, const sf::Texture& wallTexture) {
    sf::Sprite wall(wallTexture); //creating a wall sprite of the chosen image
    wall.setPosition({x * 40, y * 40 + 50}); //setting the position as per the tileSize
    wall.setScale({40.f / wallTexture.getSize().x, 40.f / wallTexture.getSize().y}); //scaling to fit the texture into the sprite
    return wall;
}

//function to create passage graphics in the maze
sf::Sprite createPassage(int x, int y, const sf::Texture& passageTexture) {
    sf::Sprite passage(passageTexture); //creating a passage sprite
    passage.setPosition({x * 40, y * 40 + 50}); //setting the position of passage in the window
    passage.setScale({40.f / passageTexture.getSize().x, 40.f / passageTexture.getSize().y}); //scaling to fit the texture into the sprite
    return passage;
}

//function that returns a vector of each pair (playerName and Score)
std::vector<std::pair<std::string, int>> getTopScores(int count = 3){
    std::ifstream scorefile("Scores.txt"); //opening the file for read
    //checking if the file was opened successfully
    if (!scorefile){
        std::cerr<<"Error opening the scores file!";
    }

    //declaring vector to store all the (name, score) pairs
    std::vector<std::pair<std::string, int>> scores;
    std::string name;
    int score;

    //Reading from the file and storing the name and score in vector pair
    while (scorefile >> name >> score){
        scores.push_back({name, score});
    }

    //sorting the scores in descending order
    std::sort(scores.begin(), scores.end(), [](const auto& a, const auto& b){
        return a.second > b.second;
    });

    //keeping only top three scores
    if (scores.size() > count){
        scores.resize(count);
    }

    //returning the top scores
    return scores;
}

//function that is responsible for displaying the top scores in the screen
void showLeaderboard(sf::RenderWindow &window){
    //vector that stores the name and scores of top 3
    std::vector<std::pair<std::string, int>> topScores = getTopScores();

    //loading font from file
    sf::Font font("FiraCode.ttf");

    //setting up Leader board title UI
    sf::Text leaderboard(font);
    leaderboard.setString("Top 3 High Scores");
    leaderboard.setCharacterSize(30);
    leaderboard.setStyle(sf::Text::Bold);
    leaderboard.setFillColor(sf::Color(64,224,208));
    leaderboard.setPosition({250, 600});
    window.draw(leaderboard); //drawing the leader board title to screen

    //displaying the three scores line by line
    for (int i = 0; i < topScores.size(); i++){
        //creating output string stream to build the string with multiple parts
        std::ostringstream oss;
        //keeping all the contents in a proper line for formatting
        oss << i + 1<<". "<<topScores[i].first<<" - "<<topScores[i].second;

        sf::Text scoreText(font);
        scoreText.setString(oss.str()); //converting the stream into single string
        scoreText.setCharacterSize(26); //display size
        scoreText.setPosition({280, 650 + i * 40}); //setting the position of the string in the screen
        window.draw(scoreText);//drawing each score to the window
    }
}

//function that displays the Game Over screen to the user
bool showGameOverScreen(sf::RenderWindow& window, sf::Font& font, int mazeSize, int tileSize, int score){
    //clearing the window with black background
    window.clear(sf::Color::Black);

    sf::Texture gameOverTexture;

    // Loading the texture with error checking
    if (!gameOverTexture.loadFromFile("gameover.png")) {
        std::cerr << "Error: Could not load game over texture!" << std::endl;
        return 1;
    }
    //creating a sprite using the texture
    sf::Sprite gameOver(gameOverTexture);
    //positioning the sprite in the top center of the window
    gameOver.setPosition({mazeSize*tileSize/2.f - 250, mazeSize*tileSize/2.f - 450});

    //creating a text object to display the player's final score
    sf::Text finalScore(font);
    finalScore.setString("Your Final Score: " + std::to_string(score)); //converting the int score to string
    finalScore.setCharacterSize(40);
    finalScore.setFillColor(sf::Color(0, 150, 255));
    finalScore.setStyle(sf::Text::Bold);
    finalScore.setPosition({mazeSize * tileSize / 2.f - 250, mazeSize * tileSize / 2.f + 150});

    //creating a text object to display the "Game Over" message
    sf::Text gameOverText(font);
    gameOverText.setString(" Game Over! \n Caught You!"); //Display Message
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition({mazeSize * tileSize / 2.f - 180, mazeSize * tileSize / 2.f});

    //drawing all elements on the window
    window.draw(gameOver);
    window.draw(gameOverText);
    window.draw(finalScore);

    //displaying the leader board below the score
    showLeaderboard(window);

    //presenting all the drawings on the screen
    window.display();

    //pausing the screen for 5sec for the user to see the message and then closing it
    sf::sleep(sf::seconds(5));
}

//function to display the Level Complete Screen
bool showLevelCompleteScreen(sf::RenderWindow& window, sf::Font& font, int mazeSize, int tileSize, int playerLevel, int score){
    //clearing the screen with black
    window.clear(sf::Color::Black);

    sf::Texture winTexture;

    //Loading texture with error checking
    if (!winTexture.loadFromFile("trophy.png")) {
        std::cerr << "Error: Could not load game over texture!" << std::endl;
        return 1;
    }
    //creating a sprite with the texture
    sf::Sprite trophy(winTexture);
    //positioning the sprite to the top-center
    trophy.setPosition({mazeSize*tileSize/2.f - 250, mazeSize*tileSize/2.f - 450});

    //creating a text object to display Level complete message
    sf::Text levelCompleteText(font);

    //Text UI
    levelCompleteText.setString("Level Complete!");
    levelCompleteText.setCharacterSize(50);
    levelCompleteText.setFillColor(sf::Color::Yellow);
    levelCompleteText.setStyle(sf::Text::Bold);
    levelCompleteText.setPosition({mazeSize * tileSize /2.f - 230, mazeSize * tileSize /2.f - 20});

    //creating a text object to display the final score
    sf::Text finalScore(font);
    //Text UI
    finalScore.setString("Your Final Score: " + std::to_string(score));
    finalScore.setCharacterSize(40);
    finalScore.setFillColor(sf::Color(0, 150, 255));
    finalScore.setStyle(sf::Text::Bold);
    finalScore.setPosition({mazeSize * tileSize / 2.f - 250, mazeSize * tileSize / 2.f + 50});

    sf::Text choiceText(font);
    //asking the user as per their level
    if (playerLevel == 1){
        //giving user the option to move to next level if in level 1
        choiceText.setString("Press Enter to move to Next Level \n       Press Esc to Quit");
        choiceText.setCharacterSize(30);
        choiceText.setFillColor(sf::Color(135,206,235));
        choiceText.setPosition({mazeSize * tileSize /2.f - 280, mazeSize * tileSize /2.f + 100});
    }
    else{
        //if the user has won the game asking user if they want to play again
        choiceText.setString("Press Enter to Play Again \n       Press Esc to Quit");
        choiceText.setCharacterSize(30);
        choiceText.setFillColor(sf::Color(135,206,235));
        choiceText.setPosition({mazeSize * tileSize /2.f - 280, mazeSize * tileSize /2.f + 100});
    }

    //drawing all the elements in the screen
    window.draw(trophy);
    window.draw(levelCompleteText);
    window.draw(finalScore);
    window.draw(choiceText);
    //displaying leader board below the message
    showLeaderboard(window);
    window.display();

    //checking if the window is open
    while (window.isOpen()){
        //while an event is detected
        while(const std::optional event = window.pollEvent()){

            //if user presses close button - "close requested" event
            if (event->is<sf::Event::Closed>()){
                window.close();
            }

            //checking for keyboard movements to understand user's choices
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                switch (keyPressed->scancode){
                case sf::Keyboard::Scancode::Enter:
                    return true; //user wants to move to next level

                case sf::Keyboard::Scancode::Escape:
                    return false; //user wants to quit the game

                default:
                    return false; //any other key pressed also leads to quit

                }
            }
        }
    }
    return false;
}

//function that displays the initial welcome window to the user
bool showWelcomeScreen(sf::RenderWindow& window, sf::Font& fontW, sf::Font& fontI, int mazeSize, int tileSize, std::string& nickname){
    //clearing the screen with black
    window.clear(sf::Color::Black);

    //creating a text object and working on its UI
    sf::Text welcomeText(fontW);
    welcomeText.setString("WELCOME");
    welcomeText.setCharacterSize(50);
    welcomeText.setFillColor(sf::Color(135,206,235));
    welcomeText.setPosition({mazeSize * tileSize/2.f - 150, mazeSize * tileSize/2.f - 300});

    sf::Text gameName(fontW);
    //Text UI
    gameName.setString("THE MAZE RUNNER");
    gameName.setCharacterSize(60);
    gameName.setFillColor(sf::Color(0, 150, 255));
    gameName.setPosition({mazeSize * tileSize/2.f - 360, mazeSize * tileSize/2.f - 230});

    sf::Text gameTagline(fontI);
    //Text UI
    gameTagline.setString("|| Run for your Life ||");
    gameTagline.setCharacterSize(40);
    gameTagline.setLetterSpacing(0.5f);
    gameTagline.setFillColor(sf::Color(64,224,208));
    gameTagline.setPosition({mazeSize*tileSize/2.f - 230, mazeSize*tileSize/2.f - 150});

    sf::Text gameInstructions1(fontI);
    //Text UI
    gameInstructions1.setString("To Win Outsmart Devils and Collect All Stars");
    gameInstructions1.setCharacterSize(25);
    gameInstructions1.setLetterSpacing(0.8f);
    gameInstructions1.setFillColor(sf::Color(135,206,235));
    gameInstructions1.setPosition({mazeSize*tileSize/2.f - 300,mazeSize*tileSize/2.f - 80});

    sf::Text gameInstructions2(fontI);
    //Text UI
    gameInstructions2.setString("Use WASD Keys or Arrow Keys to Move");
    gameInstructions2.setCharacterSize(25);
    gameInstructions2.setLetterSpacing(0.8f);
    gameInstructions2.setFillColor(sf::Color(135,206,235));
    gameInstructions2.setPosition({mazeSize*tileSize/2.f - 250,mazeSize*tileSize/2.f - 50});

    //creating a rectangle shape object that will serve as an input box
    sf::RectangleShape inputBox;
    inputBox.setSize(sf::Vector2f({400, 50}));//setting its size
    inputBox.setFillColor(sf::Color(50,50,50));
    inputBox.setPosition({mazeSize*tileSize/2.f - 200, mazeSize*tileSize/2.f + 60}); //handling its positioning in the screen

    //creating a text object that will display over the text box
    sf::Text nicknameLabel(fontI);
    //text UI
    nicknameLabel.setString("Your Nickname");
    nicknameLabel.setCharacterSize(25);
    nicknameLabel.setFillColor(sf::Color::White);
    nicknameLabel.setPosition({mazeSize * tileSize / 2.f - 100, mazeSize * tileSize / 2.f + 10});

    //setting the text UI for the user typed name
    sf::Text nicknameText(fontI);
    nicknameText.setCharacterSize(22);
    nicknameText.setFillColor(sf::Color::White);
    //setting its position inside the text box
    nicknameText.setPosition({inputBox.getPosition().x + 10, inputBox.getPosition().y + 10});

    //drawing all the elements to the window
    window.draw(welcomeText);
    window.draw(gameName);
    window.draw(gameTagline);
    window.draw(gameInstructions1);
    window.draw(gameInstructions2);
    window.draw(inputBox);
    window.draw(nicknameLabel);

    //presenting all elements to the screen
    window.display();

    //event loop
    while (window.isOpen()){
        while(const std::optional event = window.pollEvent()){
            //checking if the user closes using the close button
            if(event->is<sf::Event::Closed>()){
                window.close();
                return false;
            }

            //handling the text input for the nickname
            if (const auto* textEntered = event->getIf<sf::Event::TextEntered>()){
                //if user presses backspace(ASCII code 8) then remove the last character
                if(textEntered -> unicode == 8){
                    if (!nickname.empty()){ //checking if the name is empty or not
                        nickname.pop_back();//removing the last character
                    }
                }

                //if the input is printable and within the ASCII range
                else if(textEntered -> unicode < 128 && std::isprint(static_cast<char>(textEntered->unicode))){
                    if (nickname.size() < 16){ //limiting nickname to 16 characters
                        //adding the typed characters to the nickname string
                        nickname += static_cast<char>(textEntered ->unicode);
                    }
                }
            }

            //deciding how the user moves forward
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                switch (keyPressed->scancode){
                case sf::Keyboard::Scancode::Enter: //user is taken to the game
                    return true;
                case sf::Keyboard::Scancode::Escape: //user quits the game
                    window.close();
                    return false;
                default:
                    break;
                }
            }
        }

        //updating the display string with the latest nickname input
        std::string displayName = nickname;
        nicknameText.setString(displayName);

        //redrawing all the elements so that the updated name is displayed to the user
        //clearing the screen with black
        window.clear(sf::Color::Black);
        //drawing all the elements
        window.draw(welcomeText);
        window.draw(gameName);
        window.draw(gameTagline);
        window.draw(gameInstructions1);
        window.draw(gameInstructions2);
        window.draw(inputBox);
        window.draw(nicknameLabel);
        window.draw(nicknameText);
        //presenting to the screen
        window.display();
    }
}


int main() {
    //creating objects of the required classes
    Maze maze;
    Movement mover;
    Player player;
    Collectibles collect;

    //loading the maze layout
    maze.loadFromFile();
    //defining the mazeSize and tileSize
    int mazeSize = maze.getMaxSize();
    int tileSize = 40;

    //creating a window with proper size
    sf::RenderWindow window(sf::VideoMode({mazeSize * tileSize, (mazeSize * tileSize) + 50}), "2D Maze Game");

    window.setFramerateLimit(60);

    //Loading fonts
    sf::Font fontW("SuperPixel.ttf");
    sf::Font fontI("FiraCode.ttf");

    //initializing an empty string that stores the player name
    std::string nickname = "";
    //showing the welcome screen and getting the nickname input, if the player exits ending the program
    if (!showWelcomeScreen(window, fontW, fontI, mazeSize, tileSize, nickname)){
        return 0;
    }

    //creating a texture object for wall
    sf::Texture wallTexture;

    //loading textures with error checking
    if (!wallTexture.loadFromFile("maze wall.png")) {
        std::cerr << "Error: Could not load wall texture!" << std::endl;
        return 1;
    }

    //creating a texture object for passage s
    sf::Texture passageTexture;
    if (!passageTexture.loadFromFile("passage.png")) {
        std::cerr << "Error: Could not load passage texture!" << std::endl;
        return 1;
    }

    //creating a texture object for player
    sf::Texture playerTexture;
    if(!playerTexture.loadFromFile("player.png")){
        std::cerr<<"Error: Could not load player texture!" << std::endl;
        return 1;
    }

    //creating a player sprite from the texture
    sf::Sprite playerSprite(playerTexture);
    playerSprite.setPosition({tileSize, tileSize + 50});

    //creating a texture object for collectibles
    sf::Texture collectiblesTexture;
    if(!collectiblesTexture.loadFromFile("collect.png")){
        std::cerr<<"Error: Could not load collectible texture!"<<std::endl;
    }

    //declaring vectors to store wall and passage sprites for rendering
    std::vector<sf::Sprite> walls;
    std::vector<sf::Sprite> passages;

    //creating the maze elements by checking each cell of the maze grid
    for (int i = 0; i < mazeSize; i++) {
        for (int j = 0; j < mazeSize; j++) {
            //if the current cell is a wall character, then creating a wall sprite and storing it
            if (maze.getMazeGrid(i,j) == '|' || maze.getMazeGrid(i,j) == '-' || maze.getMazeGrid(i,j) == '+') {
                walls.push_back(createWall(i, j, wallTexture));
            }
            //if the current cell is empty then creating a passage sprite and storing it
            if (maze.getMazeGrid(i, j) == ' '){
                passages.push_back(createPassage(i, j, passageTexture));
            }
        }
    }

    //initializing enemy spawning positions using enemy default constructor
    std::vector<Enemy> enemies = {
        Enemy(2, 17),
        Enemy(10, 13),
        Enemy(7, 6),
        Enemy(12, 12),
        Enemy(16, 6)
    };

    //creating a texture object for enemy
    sf::Texture enemyTexture;
    if(!enemyTexture.loadFromFile("enemy.png")){
        std::cerr<<"Error: Could not load enemy texture!"<<std::endl;
        return 1;
    }

    //creating a enemy sprite with the texture
    sf::Sprite enemySprite(enemyTexture);

    //giving a start message
    std::string statusMessage = "Welcome to the Maze";

    //initializing the player level to 1
    int playerLevel = 1;
    int frameCounter = 0;
    //different speeds of enemy for different levels
    const int level1enemyMoveDelay = 30;
    const int level2enemyMoveDelay = 15;

    //The Main game loop
    while (window.isOpen()) {
        while(const std::optional event = window.pollEvent()){

            //if user presses close button - "close requested" event
            if (event->is<sf::Event::Closed>()){
                window.close();
            }

            //the movement logic
            //detecting the key pressed(WASD/arrow keys) and moving the player accordingly
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                switch (keyPressed->scancode){
                //moving player left
                case sf::Keyboard::Scancode::A:
                case sf::Keyboard::Scancode::Left:
                    mover.movePlayer(maze, player, 'A', statusMessage);
                    break;
                //moving player right
                case sf::Keyboard::Scancode::D:
                case sf::Keyboard::Scancode::Right:
                    mover.movePlayer(maze, player, 'D', statusMessage);
                    break;
                //moving player up
                case sf::Keyboard::Scancode::W:
                case sf::Keyboard::Scancode::Up:
                    mover.movePlayer(maze, player,'W', statusMessage);
                    break;
                //moving player down
                case sf::Keyboard::Scancode::S:
                case sf::Keyboard::Scancode::Down:
                    mover.movePlayer(maze, player, 'S', statusMessage);
                    break;
                //closing the window if escape button is pressed
                case sf::Keyboard::Scancode::Escape:
                    window.close();
                    break;
                default:
                    break;
                }

            }

        }

        //updating the position of the player
        playerSprite.setPosition({player.getPosX() * tileSize, player.getPosY() * tileSize + 50});

        //updating the enemy speed as per their level
        if (playerLevel == 1){
            if (frameCounter % level1enemyMoveDelay == 0){
                //looping through all enemies and updating their positions
                for (auto& enemy: enemies){
                    enemy.moveEnemy(maze);
                }
            }
            frameCounter++; //incrementing frame counter for next check
        }
        else if (playerLevel == 2){
            if (frameCounter % level2enemyMoveDelay == 0){
                for (auto& enemy: enemies){
                    enemy.moveEnemy(maze);
                }
            }
            frameCounter++; //incrementing frame counter for next check
        }


        //checking if all the collectibles have been collected
        bool allCollected = true;
        //looping to check each cell to find if all have been collected
        for (int i = 0; i < mazeSize && allCollected; i++){
            for (int j = 0; j < mazeSize; j++){
                if (maze.getMazeGrid(j, i) == '*' && !maze.collectibles[i][j].isCollected()){
                    allCollected = false; //setting flag to false if the collectible is not collected
                    break;
                }
            }
        }


        // Clear screen with black background
        window.clear(sf::Color::Black);

        //drawing the passages first (behind walls)
        for (const auto& ipassage : passages) {
            window.draw(ipassage);
        }

        //drawing collectibles as marked in the maze grid
        for (int i = 0; i < mazeSize; i++){
            for (int j = 0; j < mazeSize; j++){
                if (maze.getMazeGrid(j, i) == '*' && !maze.collectibles[i][j].isCollected()){
                    //creating a collectible sprite
                    sf::Sprite star(collectiblesTexture);

                    //setting scale to reduce the size of the sprite by 50%
                    float scale = 0.5f;
                    star.setScale({scale, scale});
                    //calculating width and height after scaling based on the texture
                    float width = collectiblesTexture.getSize().x * scale;
                    float height = collectiblesTexture.getSize().y * scale;
                    //setting position of the star and centering it to the center of the grid cell
                    star.setPosition({j*40 + (40-width)/2, (i*40 + (40-height)/2) + 50});

                    //drawing collectibles on the maze
                    window.draw(star);
                }
            }
        }

        //drawing the walls at last
        for (const auto& iwall : walls) {
            window.draw(iwall);
        }

        //drawing the player
        window.draw(playerSprite);

        //drawing enemies at the set locations
        for(const auto& enemy: enemies){
            enemySprite.setPosition({enemy.getPosX() * tileSize, enemy.getPosY() * tileSize + 50});
            window.draw(enemySprite);
        }

        //font UI and text for showing on top of the game screen
        sf::Font font;
        if (font.openFromFile("FiraCode.ttf")){
            //Text UI for status message
            sf::Text statusText(font);
            statusText.setString(statusMessage);
            statusText.setCharacterSize(24);
            statusText.setFillColor(sf::Color::White);
            statusText.setPosition({10, 10});

            //text UI for scores
            sf::Text scoreText(font);
            scoreText.setString("Score: " + std::to_string(player.getScore()));
            scoreText.setCharacterSize(24);
            scoreText.setFillColor(sf::Color::Red);
            scoreText.setPosition({mazeSize*tileSize - 180, 10});

            //text UI for level
            sf::Text levelText(font);
            levelText.setString("Level: "+std::to_string(playerLevel));
            levelText.setCharacterSize(24);
            levelText.setFillColor(sf::Color(0, 150, 255));
            levelText.setPosition({mazeSize*tileSize/2.f, 10});

            //drawing all the text on the screen
            window.draw(statusText);
            window.draw(levelText);
            window.draw(scoreText);
        }

        //getting the final score of the player
        int finalScore = player.getScore();

        //enemy collision then game ends logic
        //checking if the player coordinates align with the enemy coordinates
        for (const auto& enemy: enemies){
            if (enemy.getPosX() == player.getPosX() && enemy.getPosY() == player.getPosY()){
                //saving the player name and score so that they can be updated in leader board
                player.saveToFile(nickname, player.getScore());
                //displaying the game over screen
                showGameOverScreen(window, font, mazeSize, tileSize, finalScore);
                window.close();
                break;
            }
        }

        //win logic
        //if all the collectibles are collected then displaying the level complete screen
        if (allCollected){
            //saving the player score and name
            player.saveToFile(nickname, player.getScore());
            //displaying the level complete screen and getting the user choice to move forward
            bool moveForward = showLevelCompleteScreen(window, font, mazeSize, tileSize, playerLevel, finalScore);
            if (moveForward){
                //if player in level 1 updating to level 2
                playerLevel = 2;
                //resetting the maze, collectibles and player positions
                maze.createMazeLayout();
                maze.loadFromFile();
                player = Player();
                //if level 2 setting the score to the level 1 score and updating it
                player.setScore(finalScore);
                //updating the status message
                statusMessage = "Level " + std::to_string(playerLevel) + " Started!";
                continue;
            }
            else{
                //if user wants to quit closing the screen
                window.close();
            }
        }

        //displaying all the elements in the screen
        window.display();

    }

    return 0;
}
