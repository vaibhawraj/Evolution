//PABmusic.cpp
//Code Added on Dec 09, 2012
#ifndef PABmusic_CPP
#define PABmusic_CPP
void brickHit(int type)
{
     char fname[70];
     static int btype[]={0,0,0,0,0};
     if(btype[type]==4) btype[type]=0;
     if(type==4)
     sprintf(fname,"Play sounds/brick%d%d.wav from 130",type,btype[type]++);
     else
     sprintf(fname,"Play sounds/brick%d%d.wav",type,btype[type]++);
//     sprintf(fname,"Play project_pab.exe/0",type,btype[type]++);
     mciSendString(fname,mcirtn,0,hWnd);
}
void snd_ball_hit()
{
     char fname[70];
     static int btype=0;
     if(btype==3) btype=0;
     sprintf(fname,"Play sounds/ballhit%d.wav",btype++);
//     mciSendString(fname,mcirtn,0,hWnd);
}
void snd_power()
{
     char fname[70];
     static int btype=0;
     if(btype==3) btype=0;
     sprintf(fname,"Play sounds/power%d.wav",btype++);
     mciSendString(fname,mcirtn,0,hWnd);
}
void playmusic()
{
     char fname[100];
     switch(cur_bg_music_index)
      {
        case 0:
             sprintf(fname,"Play sounds/%s from 25000 repeat",cur_bg_music[cur_bg_music_index]);
             break;
        default:
             sprintf(fname,"Play sounds/%s from 0 repeat",cur_bg_music[cur_bg_music_index]);
             break;
        }
     mciSendString(fname,mcirtn,0,hWnd);
}
void pause_playmusic()
{
     char fname[100];
     sprintf(fname,"Pause sounds/%s",cur_bg_music[cur_bg_music_index]);
     mciSendString(fname,mcirtn,0,hWnd);
}
void stop_playmusic()
{
     char fname[100];
     sprintf(fname,"Stop sounds/%s",cur_bg_music[cur_bg_music_index]);
     mciSendString(fname,mcirtn,0,hWnd);
     sprintf(fname,"Close sounds/%s",cur_bg_music[cur_bg_music_index]);
     mciSendString(fname,mcirtn,0,hWnd);
}
void resume_playmusic()
{
     char fname[100];
     sprintf(fname,"Resume sounds/%s",cur_bg_music[cur_bg_music_index]);
     mciSendString(fname,mcirtn,0,hWnd);
}
void snd_fire_bullet()
{
     char fname[70];
     static int sndstack=0;
     if(sndstack==3) sndstack=0;
     sprintf(fname,"Play sounds/bullet%d.wav",sndstack++);
     mciSendString(fname,mcirtn,0,hWnd);
};
void snd_fire_bullethit()
{
     char fname[70];
     static int sndstack=0;
     if(sndstack==3) sndstack=0;
     sprintf(fname,"Play sounds/bullet_hit%d.wav",sndstack++);
     mciSendString(fname,mcirtn,0,hWnd);
};
int snd_alien_scream()
{
    char fname[70];
    static int fno=-1;
    int rtr;
    fno++;
    rtr = fno;
    if(fno==6) fno=0;
    sprintf(fname,"Play sounds/alien-scream%d.wav",fno);
    mciSendString(fname,mcirtn,0,hWnd);
    return rtr;
}
void snd_alien_scream(int fno)
{
    char fname[70];
    if(fno==-1) return;
    sprintf(fname,"Stop sounds/alien-scream%d.wav",fno);
    mciSendString(fname,mcirtn,0,hWnd);
}
void snd_alien_hello()
{
    mciSendString("Play sounds/alien-hello.wav",mcirtn,0,hWnd);
}
void snd_alien_bump()
{
     char fname[70];
     static int sndstack=0;
     if(sndstack==4) sndstack=0;
     sprintf(fname,"Play sounds/alien-bump%d.wav",sndstack++);
     mciSendString(fname,mcirtn,0,hWnd);
}
void snd_bot_bomb()
{
     char fname[70];
     static int sndstack=0;
     if(sndstack==3) sndstack=0;
     sprintf(fname,"Play sounds/botbombhit%d.wav",sndstack++);
     mciSendString(fname,mcirtn,0,hWnd);
}
void snd_alien_response()
{
     char fname[70];
     static int sndstack=0;
     if(sndstack==6) sndstack=0;
     sprintf(fname,"Play sounds/alien-response%d.wav",sndstack++);
     mciSendString(fname,mcirtn,0,hWnd);
}
void snd_alien_firo()
{
     char fname[70];
     static int sndstack=0;
     if(sndstack==3) sndstack=0;
     sprintf(fname,"Play sounds/alien-firo%d.wav",sndstack++);
     mciSendString(fname,mcirtn,0,hWnd);
}
void snd_ball_up()
{
     char fname[70];
     sprintf(fname,"Play sounds/ballup.wav");
     mciSendString(fname,NULL,0,hWnd);
}                    
void snd_pause()
{
     mciSendString("Play sounds/pause.wav",NULL,0,NULL);
}
void menu_play()
{
     mciSendString("Play sounds/menu.mp3 from 0 repeat",NULL,0,NULL);
}
void menu_stop()
{
     mciSendString("Stop sounds/menu.mp3",NULL,0,NULL);
}
void select()
{
     mciSendString("Play sounds/reset.wav",NULL,0,NULL);
}
#endif

