// ----------------------------------- framebf.h ------------------------------------- 
void framebf_init(int f_width, int f_height); 
void drawPixelARGB32(int x, int y, unsigned int attr); 
void drawRectARGB32(int x1, int y1, int x2, int y2, unsigned int attr, int fill); 
void drawImageARGB32(int cur_x, int cur_y, int i_width, int i_height,int f_width, int f_height, const unsigned long* image_bit);
