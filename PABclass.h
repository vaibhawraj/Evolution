//PABclass.h
//Code Added By Vaibhaw Raj, 110101266
//Created On Sept 16, 2012
//Code Added On Sept 18, 2012  //cl_level
//Code Added On Sept 21, 2012  //cl_ball & cl_paddle
//Code Added On Sept 28, 2012  //cl_power & cl_sb
//Code Added On Oct 3, 2012    //cl_weapon
//Code Added On Oct 2, 2012    //cl_bot
#ifndef PABclass_H
#define PABclass_H

class cl_level
{
    private:   
        long int timer; 
    public:
        st_brick_type *Start;
        void Load_Map(st_map_type *map);
        void Plot_ScoreBoard();
        void Plot_Map();
        void Draw_Brick(st_brick_type *ptr);
        void Animate(st_brick_type *ptr);
        void Init_Brick(st_brick_type *temp);
        void Release(st_brick_type *temp);
};



class cl_paddle
{
      private:
        GLfloat tx;
      public:
        void Init_Paddle();
        void Plot_Paddle();
        void Draw_Paddle();
        void Plot_Elec();
        void Animate();
};

class cl_ball
{
      private:
        int tail_len;
        int delay;
        int timer;
        st_ball_type tail_queue[20];
      public:
        void Init_Ball();
        void Plot_Ball();
        void Draw_Ball();
        void Draw_Tail();
        void Detect_Collision();
};

class cl_sb //score board
{
      private:
         int zone;
         int map;
		 int s_len;
		 int oscore;
		 st_instant_score_type obj_instant[200];
		 int top;
		 long int timer;
		 st_box_type b_thumb[3][3];
      public:
		 int score;
         GLfloat x;
         GLfloat y;
         GLfloat width;
         GLfloat height;
         void Init(int zo,int ma);
         void Plot_SB();
         void Draw_SB();
		 void Draw_Score_Instants();
		 void Draw_Score();
         void Draw_Thumb(st_box_type &box);
		 void pass(int sc,GLfloat,GLfloat);
		 inline int constant_score() {return (score==oscore)?1:0;};
		 inline int getscore() {return score;};
		 inline void pass(int sc){score=sc;}
};

class cl_weapon
{
      private:
         GLfloat x;
         GLfloat y;
         int delay;
         GLuint text;
         GLfloat width;
         GLfloat height;
         int enable_fire;
      public:
         GLfloat recoily;
         int enable;
         st_bullet_type *Start;
         void Init();
         void Init_Bullet(st_bullet_type *temp);
         void Draw_Weapon();
         void Draw_Bullet(st_bullet_type *temp);
         void Plot_Bullet();
         void Plot_Weapon();
         void Animate_Weapon();
         void Animate_Bullet(st_bullet_type *temp);
         void Detect_Collision(st_bullet_type *temp);
};

class cl_power
{
      private:
         int no_power[10];
         int no_type;
      public:
         cl_weapon gun_bullet;
         st_power_type *Start;
         void Init();
         void Init_Power(st_power_type *temp);
         void Release(st_power_type *temp);
         void Draw_Power(st_power_type *temp);
         void Plot_Power();
         void Animate(st_power_type *temp);         
         void Load_Power();
         void Detect_Collision(st_power_type *temp);
};

class cl_bot
{
      private:
         st_bomb_type *Start_Bomb;
         st_bot_type *Start;

         long int frequency;
      public:
         unsigned long int timer;
         void Init();
         void Init_Bot(st_bot_type *temp);
         void Init_Bomb(st_bomb_type *temp);
         void Release();
         void Release_Bomb();
         void Draw_Bot(st_bot_type *temp);
         void Draw_Bomb(st_bomb_type *temp);
         void Plot_Bot();
         void Plot_Bomb();
         void Animate(st_bot_type *temp);
         void Animate_Bomb(st_bomb_type *temp);
         void Add_Bot();
         void Detect_Collision(st_bot_type *temp);
         void Detect_Collision_Bomb(st_bomb_type *temp);
};



#endif
