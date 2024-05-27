void displayOptions();
int input(int total_arg, char args_list[][50]);
int compare_arg(char args_list[][50]);
void execute();

// font
void playFont();

// clearScreen
void clearScreen();

// image
void drawImage();

// video
void playVideo(int x, int y);

//welcome screen
void drawWelcomeScreen(int screen_w, int screen_h);
//draw end game screen
void drawWinGameScreen(int screen_w, int screen_h);

//game
void playGame();
//data logging
void logCommand(char command);