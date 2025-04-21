A 2D Maze Game in C++ using SFML 3.0.0

THE MAZE RUNNER 
||Run for your Life||

Game Features:
1. Grid-based Movement
   A maze grid is loaded from the file and displayed in the screen using a 2D character array. 
   The player navigates the maze using the keyboard keys (WASD or Arrow Keys).
   
2. Name and Score System
   The player is prompted for name in the welcome screen at the start of the game.
   Each star = 10 points
   The collection of stars increase the score of the player.
   
3. Collision Detection
   - Wall Collision: When the player collides with a wall, the position remains unchanged and a status message indicating "Cannot Move There!" is displayed.
   - Enmey Collision: This calls for "Game Over"

4. Enemy Random Movement
   Enemies are programmed to move randomly. The directions have been defined in an array and a random direction is chosen from there to make the enemies move.
   Each move is validated to check if the new position for the enemy is wall or not, in order to prevent unusual behavior like passing through walls.
   
5. Multiple Levels
   As the levels increase the speed of the enemies increase, making the game more interesting and challenging.
   Each level progression adds on the score.
   
6. Graphical Interface with SFML
   The game uses SFML 3.0.0 for graphics: sprites, textures, fonts and shapes to bring the maze to life.
   
7. Leaderboard 
   The top 3 scores with the player names are displayed using a leaderboard system.
   The data is read from "scores.txt" and sorted in descending order.
   
9. Save and Load System
   The player position and maze staus is updated to the file "maze.txt".
   The player name and scores are appended to the file "scores.txt" for leaderboaard display.

----------------------------------------------------------------------
How to Play?
It is a simple maze game, where the objective is to collect all the scattered stars while dodging the enemies. 
The game is fully controlled using the keyboard. 

Player Movement:
Key W / Up arrow key - To move up
Key A / Left arrow key - To move left
Key S / Down arrow key - To move down
Key D / Right arrow key - To move right

Winning the Game
- The player needs to collect all the collectibles that have been scattered in the maze
- The player needs to avoid enemies
- A Level Complete message with the final score and the leaderboard with top 3 high scores is displayed in the screen.

Game Over
- If the player collides with an enemy, the game ends.
- A Game Over message with the final score and the leaderboard with top 3 high scores is displayed in the screen.

Exiting the Game
- Press Esc Key
- Close window by clicking the close button on the title bar

