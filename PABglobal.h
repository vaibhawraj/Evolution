//PABglobal.h
//Code Added By Vaibhaw Raj, 110101266
//Created On Sept 16, 2012
//Modified On Sept 16, 2012
//Code Added On 4:20 Sept 18, 2012
//Code Added On 7:47 Sept 18, 2012
//Code Added On Sept 22, 2012
//Code Added On Sept 29, 2012
//Code Added On Oct 3, 2012
//Code Added On Oct 26, 2012
//Code Added On Nov 27, 2012  -- Concept of Available Space for Linked List from pre allocated Memory as Array
//Code Added On Dec 9, 2012  -- Music in the Game and More Life feature
#ifndef PABglobal_h
#define PABglobal_h

//Windows Function & Enable/Disable Opengl Function
HWND hWnd;
WNDCLASS wc;
HGLRC hRC;        
DWORD wstyle;
LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);
void Shutdown();

//Main Functions
     void Main_Game();
     void Fn_Scr_Welcome();
     void Fn_Scr_Main();
     void Fn_Scr_Select_Zone();
     void Fn_Scr_Load_Map_Details();
     void Fn_Game_Loop();
     void Fn_Game_Over();
	 void Fn_Welcome();
     void Fn_End_Game();
     void Fn_About();
     void Fn_Exit();
     void Error_Code(int,char []="");
     int send_report(char str[],char [] = "debug.PAB"); //Handling Error

     char rep[100]; //Error String
//End of Main Functions
//Loading Functions
     void Load_Texture();
     void Load_Maps();
     void Load_Enviroment();
//End of Loading Functions
//Extra Function
     void Add_Power(st_brick_type *ptr);
     int check_line_crossing(double a, double b, double c, double d, double x1, double y1, double x2, double y2);
     void loading_progress();
     void join_array();
	 void update(int,GLfloat,GLfloat);
	 void ingame_pause();
     
//Screen Related Global Variables
         int scrheight = 768;  //GetSystemMetrics(SM_CYMAXIMIZED);
         int scrwidth = 1366;//GetSystemMetrics(SM_CXFULLSCREEN);
         GLfloat game_scrheight = 768;
         GLfloat game_scrwidth = 1366;
         GLfloat scrnear =  -1366;
         GLfloat scrfar = -2732;
         BOOL bQuit = FALSE;
         HDC hDC;
         MSG msg;
         BOOL fullscreen = TRUE;
         int pause_flag=0;
         
//Game Related Variables
         short int int_cur_zone = 0;
         short int int_cur_map = 0;
         short int no_of_levels[3];
         short int no_of_ball = 0;
         int Game_Start = 0;
//         class CTargaImage;
         CTargaImage texture_image;         
//Texture Objects Variable
         GLuint brick_texture[4][6];
         GLuint ball_text_A;
         GLuint ph,pl,pr,pdl,wp,bu[3];
         GLuint sb_bg, zone_bg[4][4],power_text[10];
         GLuint bot[3][8][8];
         GLuint bomb[3][5];
		 GLuint PABfontface;
		 GLuint thumb;
		 GLuint menutext;
         int disable_text = 1;
         
//Structures Defination
         st_mouse_type Mouse;
         st_kb_type KB;
         st_map_type map_zone[3][12];
         st_paddle_type paddle;
         st_ball_type ball;
         st_border_type border;
         st_brick_type ms_brick[500];  //memory space for brick
         st_brick_type *brick_start = NULL, *brick_avail = ms_brick;
         st_power_type ms_power[100];
         st_power_type *power_start = NULL, *power_avail = ms_power;
         st_bot_type ms_bot[200];
         st_bot_type *bot_start,*bot_avail = ms_bot;
         st_bomb_type ms_bomb[20];
         st_bomb_type *bomb_avail = ms_bomb;
         st_bullet_type ms_bullet[5]; //memory space for bullet
         st_bullet_type *bullet_avail = ms_bullet;
         st_fs_type fsc;
//Welcome Message
		 char w_msg1[]="Evolution : Paddle And Ball Game";
		 char w_msg2[]="OOP Project";
		 char w_msg3[]="Sharda University";
		 char w_msg4[]="Press Any Key To Start";
//Music Functions Declaration
         char mcirtn[50];
         void brickHit(int);
         void snd_fire_bullet();
         void snd_fire_bullethit();
         int snd_alien_scream();
         void snd_alien_scream(int fno);
         void snd_alien_hello();
         void snd_alien_bump();
         void snd_ball_hit();
         void snd_power();
         void snd_bot_bomb();
		 void snd_alien_response();
		 void snd_alien_firo();
		 void snd_ball_up();
		 void pause_playmusic();
		 void stop_playmusic();
		 void resume_playmusic();
         void snd_pause();
         void menu_play();
         void menu_stop();
         void select();
		 char cur_bg_music[][100]={"Track1.mp3","Track2.mp3","Track3.mp3","Track4.mp3"};
		 int cur_bg_music_index=0;
		 int max_bg_music_index=1;
#endif
