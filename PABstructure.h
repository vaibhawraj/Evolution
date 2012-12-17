//PABstructure.h
//Code Added By Vaibhaw Raj, 110101266
//Created On Sept 16, 2012
//Code Added On Sept 18, 2012
//Code Added On Sept 30, 2012
//Code Added On Oct 3, 2012
//Code Added On Oct 25, 2012     //Updated Brick Structure
                                 //Added St_Lvl_header
//Code Added On Oct 26, 2012     //Structure of Bot && Bomb
#ifndef PABstructure_H
#define PABstructure_H

typedef struct st_mouse
 {
     GLfloat X;
     GLfloat Y;
     int Button; //0 - Left  1 - Right
 }st_mouse_type;
 
typedef struct st_keyboard
 {
     int key;
 }st_kb_type;
 
typedef struct st_brick
 {
     int row;
     int col;
     GLfloat x;
     GLfloat y;
     GLfloat z;
     GLfloat height;
     GLfloat width;
     int type;
     int anim;
     GLfloat ny;
     GLfloat oy;
     GLfloat ox;
	 GLfloat color[3];
     int frame;
     int strength;
     int power_type;
     int release_power;
     GLuint text;
     struct st_brick *next;//Normal Flow
     struct st_brick *prev;
     //Immediate Attached Bricks Link
     struct st_brick *u1;
     struct st_brick *u2;
     struct st_brick *d1;
     struct st_brick *d2;
     struct st_brick *p1;
     struct st_brick *p2;
     struct st_brick *n1;
     struct st_brick *n2;
     struct st_bot *bot;
 }st_brick_type;

typedef struct st_paddle
 {
     GLfloat x;
     GLfloat y;
     GLfloat length;
     GLfloat olength;
     GLfloat width;
     int magnet;
     int type;
 }st_paddle_type;
 
typedef struct st_map
 {
     char Map[20][25];
     int No_of_brick;
     int col;
     int row;
     int width;
     int height;
 }st_map_type;
 
typedef struct st_ball
 {
     GLfloat x;
     GLfloat y;
     GLfloat dx;
     GLfloat dy;
     GLfloat rz;
     GLfloat cz;
     int type;
     GLfloat radius;
     GLint maxspeed;
     int stick;
     GLfloat stpos;
 }st_ball_type;

typedef struct st_border
 {
     GLfloat x1;
     GLfloat y1;
     GLfloat x2;
     GLfloat y2;
 }st_border_type;

typedef struct st_power
 {
     GLfloat x;
     GLfloat y;
     GLfloat dx;
     GLfloat dy;
     GLfloat ay;
     GLfloat ax;
     GLfloat rz;
     GLuint text;
     GLfloat cz;                  //0 - Nothing
     int type;                //1 - Expand
     GLfloat height;              //2 - Shrink
     GLfloat width;               //3 - Kill
     GLfloat cheight;
     GLfloat cwidth;
     GLfloat oheight;
     GLfloat owidth;              //7 - Call Bot
     int enable;              //6 - Breaker
     struct st_power *next;   //4 - Magnet
 }st_power_type;              //5 - Speedy

typedef struct st_bullet
 {
     GLfloat x;
     GLfloat y;
     GLfloat dy;
     GLfloat width;
     GLfloat height;
     int explode;
     GLuint text;
     int frame;
     struct st_bullet *next;
 }st_bullet_type;                       
                              
typedef struct st_header
{
       int nob;
       char col;
       char row;
       char width;
       char height;
       char map[700];
}st_lvl;

typedef struct st_bot
{
        GLfloat x;
        GLfloat y;
        GLfloat rz;
        GLfloat cz;
        GLfloat dx;
        GLfloat dy;
        int strength;
        GLfloat height;
        GLfloat oheight;
        GLfloat owidth;
        GLfloat width;  // D  0 - Entering
        int anim;   // D  1 - Looking Left StandAlone Right
                    // D  2 - Dance
                    // X 3 - Jumping
                    // D 4 - Looking Up
                    //   5 - Raising Bomb
                    //   6 - Throwing Bomb
                    //   7 - Falling
        int bomb;   //   1 - Raising Bomb  2 - Throwing Bomb 0 - Neutral
        unsigned long int timer;  //   timer for measuring intervals between each bomb throw
        long int change_anim_frequency;
        int bot_frame;
        int fall;
        int dead;
        int trackno;
        GLfloat color[3];   //Red, Blue, Green, White
        st_brick_type *brick;
        struct st_bot *next;
        GLuint text;
}st_bot_type;

typedef struct st_bomb
{
        GLfloat x;
        GLfloat y;
        GLfloat dx;
        GLfloat dy;
        GLfloat rz;
        GLfloat cz;
        GLfloat height;
        GLfloat width;
        int bomb_frame;
        int explode;
        GLuint text;
        struct st_bomb *next;
}st_bomb_type;

typedef struct st_instant_score
{
	    GLfloat x;
		GLfloat y;
		GLfloat color[4];
		GLint score;
		int timer;
}st_instant_score_type;

typedef struct st_box
{
	GLfloat x;
	GLfloat y;
	GLfloat owidth;
	GLfloat rx;
	GLfloat cx;
	GLfloat oheight;
	GLuint front_tex;
	GLfloat t_width;
	GLfloat t_height;
	GLfloat width;
	GLfloat height;
	GLfloat depth;
	GLfloat t_x;
	GLfloat t_y;
	long int timer;
	int triger;
}st_box_type;

typedef struct st_file_score
{
    int map_no;
    int score;
    short int no_of_ball;
}st_fs_type;
#endif
