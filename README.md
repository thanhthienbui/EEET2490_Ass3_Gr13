Task 1: Display ảnh, video với font chữ (Thien)
Task 2: research timer interrupt (Hoang Do)
Topic: Scaffold & Hammer: A platforming game with a character destroying falling projectile or the projectile will blow up the ground underneath the player and lose the game. The high score record with each projectile destroyed and power up taken. Throw button can be held to throw stronger and a thrown hammer to destroy the projectile will inherit the momentum of the object (pseudo per say, move right throw right will be thrown up right while move right will be just right). Hammer will bounce if thrown strong enough. 
Task 1 and 2 deadline: 10/5/2024

Additionmal INformation for TASK 3: 
NAME: Sisyphus's Trial - impress Hades and earn Sisyphus freedom
SCRREN: (WXH) 8x16 tiles screen game + 1 tile padding an 4 sides - 1 tile is a 8x8 pixels patterns for paddings, boulders, bombs, lightning strike, PC (SISYPHUS), power ups -> final size: 18*8 x 10*8 = 144 x 80 pixels -> 11520 bytes
INTRO: Custom video frames for introduction, background, final cutscenes and death screens. (addition, if possible)
FONTS: Sample fonts or custom (decided later if possible)
MAIN GAMEPLAY:
  - Sisyphus move around, jump around the boulders (with A, D and space).
  - Can push nearby boulders by pressing S why moving.
  - Throw falling boulders resting on top by press W (cannot move why the boulder is on top of you) before timer run out and the boulder crush you.
  
  - All object will obey grid of the game. (Sis will move one tile/ move)
  - Boulder fall at steady pace, will rest on top of Sisyhus (PC) and be thrown if pressed, if collided with boulder with opposite vector will break, else will fall down (if bottom is empty, fall down, else fall to left or right side if either are empty)
  - Bombs fall the same but eplode either 2x2 tiles when touch down floor or 4x4 tiles if colllide mid air and os un catchable.
  - Lightnigg will just delete one column, cannnot be catched and do not fall. There is a outline of where it strikes.

  - The level of gradually changed background as you go up as one row finish develop then the screen go up, to eventually reach the top of the cave and you win, with highscore dictate how much boulder destroyed h and what level you reaches (each level give multipictive value to the boulder,lvl 1 give boulder 10, then lvl 2 give 1.25 thus 12, then lvl 3 give 15 then more)
  - PC only have 1 life and died if crushed
  - We aim for 3 stage so far so 3 backgrounds first, work on mechanics and player, boulder and padding sprites. (FOCUS ON SYSTEM DESIGN AND IMPLEMENT, CONTROLS, SPRITES & BACKGROUND AND HIGHSCORE)
