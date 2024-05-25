Task 1: Display ảnh, video với font chữ (Thien)
Task 2: research timer interrupt (Hoang Do)
Topic: Scaffold & Hammer: A platforming game with a character destroying falling projectile or the projectile will blow up the ground underneath the player and lose the game. The high score record with each projectile destroyed and power up taken. Throw button can be held to throw stronger and a thrown hammer to destroy the projectile will inherit the momentum of the object (pseudo per say, move right throw right will be thrown up right while move right will be just right). Hammer will bounce if thrown strong enough. 
Task 1 and 2 deadline: 10/5/2024

Additionmal INformation for TASK 3: 
NAME:Blind -> simple maze game with 3 premade levels with timer to reach to exit and win the game, touch the walls or timer run out -> return to level starts. Beat 3 levels greated with game win screen
SCRREN: 1024 x 768 screen res, 16x12 tile
INTRO: Custom yellow characters + blue goal post, black walls and while starting place
FONTS: Sample fonts to display the welcome and end game screen and level words
MAIN GAMEPLAY:
  - PC move around left, right up and down (with W,A,S,D). After a certain time without getting gold he return to white spot
  - Wall is black as background color, touch it the PC will return to white spot and timer resets.
  - Advance to next level by get to blue goal post.
  - We aim for 3 stage so far so 3 levels, work on levels, players and collision (FOCUS ON SYSTEM DESIGN AND IMPLEMENT, CONTROLS)
  - - Make welcome screen and Win screen --- welcome screen done, the win screen is just the same principal with final played time, the lower the better
- Grid Map is 640/16 x 480/16 (wxh), 3, 4 or 5 level with each are more difficult than other, 1st have no walls, 2nd have some wall in between, 3 have walls section and bends, 4 have a true maze. Each maze must be customed as 2D arrays with each value is either 0(none), 1(spawn), 2 (walls), 3 (goal post, get and finish level) and 4 (walls but highlighted). Spawn and Goal post must be highlighted and static throughout all levels but walls changed. The highlighted walls are wipted out and renewed thorugh levels (reds into blacks again).
- Display spawn point and goal post according to map and drawn player character in top. Update the scannned walls into highlighted walls by replaceing value at that wall tile 2 to 4 and draw any tiles with highlighted tiles. Check logic player location in grid first to either keep current location or back to spawn when died then draw player on top of background maze. 
- 2 ways to highlighed walls, one is to scan at a distance of 4 tiles, if there is any in the distance, highlighted it by changing value from 2 to 4. And one is when hit by walls, check player location, if it is walls ==2, move player to spawn point by chanigng x1, y1 and x2, y2 and change that grid value at that location from 2 to 4, make it highlighted. 
- movement checking --- done, edge detection done too, move at 16x16 tiles. 
- timer for advanced timer
- lighting and lamp

https://github.com/babbleberry/rpi4-osdev/tree/master/part6-breakout check this link for  moving and collusion
