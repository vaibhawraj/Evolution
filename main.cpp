/***********************************
Project Topic :: Paddle And Ball Video Game Using OpenGL
Code By       :: Vaibhaw Raj, 110101266, CS-'C', B.Tech IInd Yr, Sharda University
Started On    :: Sept 10, 2012
Restarted On  :: Sept 16, 2012
Code Added On :: 4:20 PM Sept 18, 2012
Code Added On :: 7:24 PM Sept 28, 2012
Code Added On :: 10:05 AM Sept 29, 2012
Code Added On :: Oct 25, 2012
Code Added On :: Oct 26, 2012
Code Added On :: Nov 27, 2012
Code Added On :: Dec 09, 2012

Refference ::
    1> OpenGl Book :: Beginning OpenGl Game Programming  Author :: Dave Astle, Kevin Hawkins
    2> MSDN Library :: msdn.microsoft.com
    3> C Plus Plus :: www.cplusplus.com
    4> Sound Effect :: www.sounds-resource.com
    5> BackGround Music :: www.IndieGameMusic.com
                  Track Credit ::
                        ==================================================
                        Track Name -> Transform
                        Author -> Roald Strauss
                        Genre -> Electronic (Aggresive, Dark)
                        ==================================================
                        ==================================================
                        Track Name -> A Dark Heart
                        Author -> Robert Shaw
                        Genre -> Rock (Aggresive, Motivated)
                        ==================================================
                        ==================================================
                        Track Name -> A Monotonic Day (Game Menu)
                        Author -> Roald Strauss
                        Genre -> Electronic (Aggresive)
                        ==================================================
                        ==================================================
                        Track Name -> Another Retro Tune (Game Menu,Intro Story)
                        Author -> Roald Strauss
                        Genre -> Electronic (Aggresive)
                        ==================================================                        
                        ==================================================
                        Track Name -> Crunchy (Bring The War)
                        Author -> Collin Cusce
                        Genre -> Rock (Aggresive)
                        ==================================================
                        ==================================================
                        Track Name -> Danger (Boss Level)
                        Author -> Roald Strauss
                        Genre -> Electronic (Aggresive)
                        ==================================================
***********************************/
#define _CRT_SECURE_NO_WARNINGS
/*Header Files*/
#include <windows.h>
#include <windowsx.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <mmsystem.h>
#include "CTargaImage.h"
#include "PABstructure.h"
#include "PABglobal.h"
#include "PABclass.h"
#include "PABimage.h"

/*File Included*/
#include "PABfont.cpp"
#include "CTargaImage.cpp"
#include "PABclass.cpp"
#include "PABtexture.cpp"
#include "PABmusic.cpp"
#include "PABerror.cpp"
#include "PABmisc.cpp"
/**************************
 * Function Declarations
 *
 **************************/




/**************************
 * WinMain
 *
 **************************/
cl_paddle obj_paddle;
cl_ball obj_ball;
cl_level obj_level;
cl_sb obj_sb;
cl_power obj_power;
cl_bot obj_bot;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName="OOP Project";
    RegisterClass (&wc);

    DEVMODE devmode;
    memset(&devmode,0,sizeof(DEVMODE));
    devmode.dmSize = sizeof(devmode);
    devmode.dmPelsWidth = scrwidth;
    devmode.dmPelsHeight = scrheight;
    devmode.dmBitsPerPel = 32;
    devmode.dmFields = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
    if ( fullscreen != TRUE )
       {
         if ( ChangeDisplaySettings(&devmode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL )
            {
               LPCWSTR stro;
			   char str[100];
               sprintf(str,"Fullscreen Mode Failed %d %d",scrwidth,scrheight);
               MessageBox(NULL, str, NULL, MB_OK);
               fullscreen = FALSE;
            }
       }
    if ( fullscreen )
       {
          wstyle = WS_POPUP | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
       }
    else
       {
          wstyle = WS_POPUP | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
          scrheight = 720;
          scrwidth = 1354;
       }
       
    /* create main window */
    hWnd = CreateWindow ("OOP Project", "Paddle And Ball Game", wstyle,
      0, 0, scrwidth, scrheight,
      NULL, NULL, hInstance, NULL);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);

    /* program main loop */

    Main_Game();
    //Game Shutdown
    Shutdown();

    return msg.wParam;
}

void Shutdown()
{     
    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);
     /* destroy the window explicitly */
    DestroyWindow (hWnd);
    exit(1);
}
/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;
    case WM_KEYUP:
         KB.key = -1;
        return 0;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case 'Q':
        case 'q':
            PostQuitMessage(0);
  			Shutdown();
            return 0;
        }
        KB.key = wParam;
        return 0;
    case WM_LBUTTONDOWN:
         ball.stick=0;
         Mouse.Button = 0;
         return 0;
    case WM_RBUTTONDOWN:
         Mouse.Button = 1;
         return 0;
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
         Mouse.Button = -1;
         return 0;
    case WM_MOUSEMOVE:
         Mouse.X =  ((GET_X_LPARAM(lParam) - scrwidth/2)*game_scrwidth)/scrwidth;
         Mouse.Y =  ((- GET_Y_LPARAM(lParam) + scrheight/2)*game_scrheight)/scrheight;
         Mouse.Button = -1;
         switch(wParam)
           {
               case MK_LBUTTON:
                    Mouse.Button = 0;
                    return 0;
               case MK_RBUTTON:
                    Mouse.Button = 1;
                    return 0;
           }
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}


/********************************************************************************************************************** /
Main Game Code

  Variable Names... Every name begins with prefix in small letter reffering to its type. e.d fn_var_name for function

/ **********************************************************************************************************************/

void Main_Game()
{
     //Different Screens Will be called from here
     //Loading Functions   --> Load Texture()
     Mouse.Button = -1;
     KB.key = -1;
     if(Game_Start == 0)
     {
        Load_Enviroment();
        Load_Texture();
        Load_Maps();
     }
     Game_Start = 1;
     
     //                        Load Music()
     //                        Load Maps()
    
     //Fn_Scr_Welcome() --> Welcome Screen()
     //Fn_Scr_Main() --> Main Screen()
     //   Fn_Scr_Select_Zone () --> Select Zone Screen()  --> Zone 1 --> Zone 2 --> Zone 3
     //Retrive Current Level & Current Score
     FILE *fp;
     int cur_score=0;
     fp = fopen("fs_lvl.fs","rb");
     if(fp == NULL)
        {
             cur_score = 0;
             int_cur_zone = 0;
             int_cur_map = 0;
             no_of_ball = 3;
             obj_sb.pass(0);
        }
     else
        {
             int i=0;
             fsc.score = 0;
             fsc.map_no = -1;
             fsc.no_of_ball = 0;
             fread(&fsc,sizeof(fsc),1,fp);
             cur_score = fsc.score;
             int_cur_map = fsc.map_no + 1;
             no_of_ball = fsc.no_of_ball;
             if(int_cur_map == 0) no_of_ball = 3;
             if(no_of_ball < 1) no_of_ball = 3;
             if(int_cur_map <no_of_levels[int_cur_zone])
                 int_cur_zone = 0;
             else
                {
                  int_cur_map = 0;
                  int_cur_zone = 0;
                  no_of_ball = 3;
                  cur_score = 0;
                }
             obj_sb.pass(cur_score);
             fclose(fp);
        }   Fn_Scr_Welcome();
	    //    Fn_Welcome();
	        FILE *bgmus;
	        if((bgmus=fopen("sounds/bgmus.mus","rb"))!=NULL)
	          {
                 int temp_val;
                 fread(&temp_val,sizeof(temp_val),1,bgmus);
                 cur_bg_music_index = temp_val + 1;
                 if(cur_bg_music_index > max_bg_music_index) cur_bg_music_index = 0;
                 fclose(bgmus);
              }
           bgmus=fopen("sounds/bgmus.mus","wb");
           fwrite(&cur_bg_music_index,sizeof(cur_bg_music_index),1,bgmus);
           fclose(bgmus);
           playmusic();
         while(int_cur_map<no_of_levels[int_cur_zone])
            {
            if(int_cur_map%6 == 5 && cur_bg_music_index!=3)
                {
                   stop_playmusic();
                   cur_bg_music_index = 3;
                   playmusic();
                }
            else if((int_cur_map%6 == 2 || int_cur_map%6 == 3 || int_cur_map%6 == 4) && (cur_bg_music_index != 2))
                {
                   stop_playmusic();
                   cur_bg_music_index = 2;
                   playmusic();
                }
            else if((int_cur_map%6 == 1 || int_cur_map%6 == 0) && (cur_bg_music_index != 1 && cur_bg_music_index != 0))
                {
                   stop_playmusic();
                   cur_bg_music_index = rand() % 2;
                   playmusic();
                }
            Fn_Scr_Load_Map_Details(); //--> Load Map Details()
            Fn_Game_Loop();
            fsc.map_no = int_cur_map;
            fsc.score = obj_sb.score;
            fsc.no_of_ball = no_of_ball;
            fp = fopen("fs_lvl.fs","wb");
            fwrite(&fsc,sizeof(fsc),1,fp);
            fclose(fp);
			int_cur_map++;
            }
            Fn_Game_Over();
     //         Fn_End_Game() --> Return To Main Screen()
     //Fn_About()
     //Fn_Exit()         

}

void Fn_Scr_Welcome() 
{
     GLfloat fwidth=300,fheight=75;
     GLfloat rot=0;  //degree
     GLfloat fdepth[]={-36.0,-12.0,12.0,36.0},fcentery=0.0;
     int controls = 0;
     int cur_high=0;
     int maxy=35;
     int i,j;
     GLfloat xheight,xwidth;
     GLint xdiv=100,ydiv=100;
     GLfloat xwid,yhei;
     GLfloat depth[xdiv+1][ydiv+1];
     GLfloat txwid,tyhei;
     xheight = game_scrheight;
     xwidth = game_scrwidth;
     xwid = (2*xwidth)/xdiv;
     yhei = (2*xheight)/ydiv;
     txwid = 1.0f/xdiv;
     tyhei = 1.0f/ydiv;
     menu_stop();
     menu_play();
     for(i=0;i<=xdiv;i++)
       for(j=0;j<=ydiv;j++)
          depth[i][j]=0;
       while (!bQuit)
       {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
                bQuit = TRUE;
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
            /* OpenGL animation code goes here */
            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear (GL_COLOR_BUFFER_BIT);
            ShowCursor(FALSE);
            GLuint text;
            text = zone_bg[1][1];
            if(disable_text==1)
             {
                glEnable(GL_TEXTURE_2D);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
             }
             //BGround
             glPushMatrix();
             glLoadIdentity();
             glColor3f(1.0,1.0,1.0);
            // glBindTexture(GL_TEXTURE_2D, text);
             /*
             glTranslatef(-(GLfloat)game_scrwidth/2,-(GLfloat)game_scrheight/2,scrnear);
             glBegin(GL_LINE_LOOP);
               for(i=0;i<xdiv;i++)
                 for(j=0;j<ydiv;j++)
                    {
                         glTexCoord2f(i*txwid,j*tyhei);  glVertex3f(i*xwid,j*yhei,0);
                         glTexCoord2f(i*txwid + txwid,j*tyhei);  glVertex3f(i*xwid + xwid,j*yhei,0);
                         glTexCoord2f(i*txwid + txwid,j*tyhei + tyhei);  glVertex3f(i*xwid + xwid,j*yhei + yhei,0);
                         glTexCoord2f(i*txwid,j*tyhei + tyhei);  glVertex3f(i*xwid,j*yhei + yhei,0);
                    }
             glEnd();
             glPopMatrix();
             */
             glPushMatrix();
             glLoadIdentity();
             glColor3f(1.0,1.0,1.0);
             glBindTexture(GL_TEXTURE_2D, menutext);
             glTranslatef((GLfloat)-game_scrwidth,-(GLfloat)game_scrheight,scrfar);
             glBegin(GL_LINE_LOOP);
               for(i=0;i<xdiv;i++)
                 for(j=0;j<ydiv;j++)
                    {
                         glTexCoord2f(i*txwid,j*tyhei);  
                            glVertex3f(i*xwid,j*yhei,depth[i][j]);
                         glTexCoord2f(i*txwid + txwid,j*tyhei);  
                            glVertex3f(i*xwid + xwid,j*yhei,depth[i+1][j]);
                         glTexCoord2f(i*txwid + txwid,j*tyhei + tyhei);  
                            glVertex3f(i*xwid + xwid,j*yhei + yhei,depth[i+1][j+1]);
                         glTexCoord2f(i*txwid,j*tyhei + tyhei);  
                            glVertex3f(i*xwid,j*yhei + yhei,depth[i][j+1]);
                    }
             glEnd();
             glPopMatrix();
             glDisable(GL_TEXTURE_2D);
             glDisable(GL_BLEND);
             //BGground
             
             for(i=0;i<=xdiv;i++)
               for(j=0;j<=ydiv;j++)
                  {
                   GLfloat tx,ty,dis;
                   tx = ((-game_scrwidth + (i * xwid)) - (Mouse.X));
                   ty = ((-game_scrheight + (j * yhei)) - (Mouse.Y));
                   dis = sqrt(pow(ty,2) + pow(tx,2));
                   if(dis <= 300)
                      ty=((300-dis)*(700))/300;
                   else
                      ty=0;             
                   depth[i][j]=ty;
                  }
             
             //Panel
             if(controls == 0) // For appearance of Controls Screen
             {
             glPushMatrix();
                char str[][50]={"Continue","New Game","Control","Exit"};
     
                if(int_cur_map == 0)
                    maxy = -50;
                else
                    maxy = 30;
                if(Mouse.Y < maxy && Mouse.Y>-300 && (Mouse.X <= 300 && Mouse.X >= -300))
                    fcentery = Mouse.Y;

                if(Mouse.X >= -fwidth/2 && Mouse.X <= fwidth/2)
                {
                  int temp = cur_high;
                if(Mouse.Y >=0 && Mouse.Y <= 65 && int_cur_map != 0 ) cur_high=1;
                else if(Mouse.Y <=-50 && Mouse.Y >= -110) cur_high=2;
                else if(Mouse.Y <=-160 && Mouse.Y >= -220) cur_high=3;
                else if(Mouse.Y <=-270 && Mouse.Y >= -335) cur_high=4;
                else cur_high = 0;
                if(temp != cur_high && cur_high != 0) select();
                }
                else cur_high = 0;
                if(Mouse.Y >=65) {
                           if(fcentery>maxy+5 || fcentery<maxy-5)
                              { 
                                if(fcentery>maxy) fcentery-=5;
                                else fcentery+=5;
                              }
                           else
                              fcentery=maxy;
                           }
             rot=(((fcentery-30)*(36-(-36)))/((-300)-(30)))+(-36);
             int l;
             if(int_cur_map != 0)
                  l=0;
             else
                  l=1;
             for(i=3;i>=l;i--)
             {
                glPushMatrix();       
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glTranslatef(0.0,fcentery,scrnear-400);
                glTranslatef(0.0,320*sin(((rot+fdepth[3-i])*3.14)/180),400*cos(((rot+fdepth[3-i])*3.14)/180));
                if(i+1==cur_high)
                   {
                   glColor4f(1.0,1.0,0.5,0.5);
                   /*
                   glEnable(GL_TEXTURE_2D);
                   glBindTexture(GL_TEXTURE_2D, menutext);
                   glBegin(GL_QUADS);
                      glTexCoord2i(0,1);  glVertex2f(fwidth/2,fheight/2);
                      glTexCoord2i(0,0);  glVertex2f(fwidth/2,-fheight/2);
                      glTexCoord2i(1,0);  glVertex2f(-fwidth/2,-fheight/2);
                      glTexCoord2i(1,1);  glVertex2f(-fwidth/2,fheight/2);
                   glEnd();
                   glDisable(GL_TEXTURE_2D);
                   */
                   //
                
                       glColor4f(0.5,0.2,0.5,0.7); 
                       glBegin(GL_QUADS);
                           glVertex2f(fwidth/2,fheight/4);
                           glVertex2f(fwidth/2,-fheight/4);
                           glVertex2f(-fwidth/2,-fheight/4);
                           glVertex2f(-fwidth/2,fheight/4);
                       glEnd();
                       glTranslatef(-((fwidth/2)+20),((fheight/2)-15),0.0);
                       glBegin(GL_QUADS);
                          glColor4f(0.6,0.6,0.0,0.8);
                          glVertex3f(5,35,0);
                          glVertex3f(5,-35,0);
                          glVertex3f(-5,-35,0);
                          glVertex3f(-5,35,0);
                          glVertex3f(65,40,0);
                          glVertex3f(65,30,0);
                          glVertex3f(-5,30,0);
                          glVertex3f(-5,40,0);
                       glEnd();
                       glTranslatef(((fwidth)+2*20),-((fheight)-2*15),0.0);
                       glRotatef(180,0.0,0.0,1.0);
                       glBegin(GL_QUADS);
                          glColor4f(0.6,0.6,0.0,0.8);
                          glVertex3f(5,35,0);
                          glVertex3f(5,-35,0);
                          glVertex3f(-5,-35,0);
                          glVertex3f(-5,35,0);
                          glVertex3f(65,40,0);
                          glVertex3f(65,30,0);
                          glVertex3f(-5,30,0);
                          glVertex3f(-5,40,0);
                       glEnd();
                
                   //
                   glColor4f(1.0,0.6,0.0,1);
                   PABfont.puttext(str[i],-((strlen(str[i])*38.0)/2.0),(fheight/2) + fcentery + (320*sin(((rot+fdepth[3-i])*3.14)/180)),400*cos(((rot+fdepth[3-i])*3.14)/180)-400,38,fheight,0,1,1);
                   }
                else
                  {
                 /*  glColor4f(0.5,0.2,0.5,0.7); 
                   glBegin(GL_QUADS);
                      glVertex2f(fwidth/2,fheight/2);
                      glVertex2f(fwidth/2,-fheight/2);
                      glVertex2f(-fwidth/2,-fheight/2);
                      glVertex2f(-fwidth/2,fheight/2);
                   glEnd();*/
                   glColor4f(1.0,1.0,1.0,1);
                   PABfont.puttext(str[i],-((strlen(str[i])*30.0)/2.0),(fheight/2) + fcentery + (320*sin(((rot+fdepth[3-i])*3.14)/180)),400*cos(((rot+fdepth[3-i])*3.14)/180)-400,30,fheight,0,1,1);
                   }
                glPopMatrix();
             }
                glDisable(GL_BLEND);
             glPopMatrix();
             //End of Panel
             }
             else
             {
                 //Control Panel
                  GLfloat height=450,width=1200;
                  glPushMatrix();
                     glEnable(GL_BLEND);
                     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   
                     glPushMatrix();
                        glTranslatef(-((width/2)+50),((height/2)+15),scrnear);
                        glBegin(GL_QUADS);
                            glColor4f(0.6,0.6,0.0,0.8);
                            glVertex3f(5,35,0);
                            glVertex3f(5,-35,0);
                            glVertex3f(-5,-35,0);
                            glVertex3f(-5,35,0);
                            glVertex3f(65,40,0);
                            glVertex3f(65,30,0);
                            glVertex3f(-5,30,0);
                            glVertex3f(-5,40,0);
                        glEnd();
                     glPopMatrix();
                  glPushMatrix();
                  glTranslatef(((width/2)+50),-((height/2)+15),scrnear);
                  glRotatef(180,0.0,0.0,1.0);
                  glBegin(GL_QUADS);
                      glColor4f(0.6,0.6,0.0,0.8);
                      glVertex3f(5,35,0);
                      glVertex3f(5,-35,0);
                      glVertex3f(-5,-35,0);
                      glVertex3f(-5,35,0);
                      glVertex3f(65,40,0);
                      glVertex3f(65,30,0);
                      glVertex3f(-5,30,0);
                      glVertex3f(-5,40,0);
                  glEnd();
                  glPopMatrix();
                  glPushMatrix();
                  glBegin(GL_QUADS);
                      glColor4f(0.0,0.3,0.0,0.8);
                      glVertex3f(-width/2,height/2,scrnear);
                      glVertex3f(width/2,height/2,scrnear);
                      glVertex3f(width/2,-height/2,scrnear);
                      glVertex3f(-width/2,-height/2,scrnear);
                  glEnd();
                  glBegin(GL_LINE_LOOP);
                      glColor4f(0.0,1.0,1.0,0.8);
                      glVertex3f(-(width-15)/2,(height-15)/2,scrnear);
                      glVertex3f((width-15)/2,(height-15)/2,scrnear);
                      glVertex3f((width-15)/2,-(height-15)/2,scrnear);
                      glVertex3f(-(width-15)/2,-(height-15)/2,scrnear);
                      glVertex3f(-(width-15)/2,(height-15)/2,scrnear);
                  glEnd();
             glDisable(GL_BLEND);
  //   glTranslatef(0.0,0.0,scrnear);
             glPopMatrix();
             glPushMatrix();
                glColor3f(0.7,0.3,1.0);
                PABfont.puttext("Controls",-(width-50)/2,(height-50)/2,40,40,4.5,1);
                glColor3f(1.0,0.0,1.0);
                PABfont.puttext("Mouse        To Move Paddle Left And Right",-(width-140)/2,(height/2)-100,30,40,7,1);
                PABfont.puttext("Left Button  To Fire or Release Ball",-(width-140)/2,(height/2)-170,30,40,7,1);
                PABfont.puttext("Q            Immediate Exit To Windows",-(width-140)/2,(height/2)-240,30,40,7,1);
                PABfont.puttext("R            Return To Game Menu",-(width-140)/2,(height/2)-310,30,40,7,1);
                PABfont.puttext("ESC          To Pause n Resume Game",-(width-140)/2,(height/2)-380,30,40,7,1);
             glPopMatrix();
             if(KB.key != -1 )
             {
                Mouse.Button = -1;
                controls = 0;
             }
                 //End of Control Panel
             }
             //Mouse Cursor
             glPushMatrix();
                glLoadIdentity();
                glTranslatef(Mouse.X,Mouse.Y,scrnear);
                glColor3f(1.0,0.0,0.0);
                glBegin(GL_LINE_LOOP);
                   glVertex3f(0,0,0);
                   glVertex3f(10,-25,0);
                   glVertex3f(10,-10,0);
                   glVertex3f(25,-10,0);
                   glVertex3f(0,0,0);
                   glVertex3f(25,-10,0);
                   glVertex3f(10,-10,0);
                   glVertex3f(10,-8,0);
                   glVertex3f(50,-48,0);
                   for(i=0;i<=5;i++)
                   {
                      glVertex3f(50+(2*i),-(48+(2*i)),0);
                      glVertex3f((50+(2*i))+15,-((50+(2*i))-2),0);
                      glVertex3f(50+(2*i),-(48+(2*i)),0);
                   }
        //           glVertex3f(48,-50,0);
                   for(i=5;i>=0;i--)
                   {
                      glVertex3f(48+(2*i),-(50+(2*i)),0);
                      glVertex3f(48+(2*i),-((65+(2*i))),0);
                      glVertex3f(48+(2*i),-(50+(2*i)),0);
                   }
                   glVertex3f(50,-52,0);
                   glVertex3f(10,-12,0);
                   glVertex3f(10,-10,0);
                   glVertex3f(25,-10,0);                   
                glEnd();
               glPopMatrix();
             glPushMatrix();
			     glColor3f(1.0f,1.0f,0.0f);
			     PABfont.puttext("Programmed By Vaibhaw Raj",270,-340,500,40,4.5);
				 glColor3f(1.0f,1.0f,1.0f);
			 glPopMatrix();
            SwapBuffers (hDC);
            if(Mouse.Button == 0) 
              {
               if(cur_high==4)
                {
                  PostQuitMessage(0);                            
                  Shutdown();
                }
               if(cur_high==2)
                {
                    FILE *fp;
                    fp = fopen("fs_lvl.fs","wb");
                    fsc.map_no = -1;
                    fsc.score = 0;
                    fwrite(&fsc,sizeof(fsc),1,fp);
                    fclose(fp);
                    int_cur_map = 0;
                    int_cur_zone = 0;
                    no_of_ball = 3;
                    obj_sb.pass(0);
                    menu_stop();
                    return;
                }
               if(cur_high==3)
                {
                    controls = 1;
                    cur_high = 0;
                }
               if(cur_high==1)
                    {
                    menu_stop();
                    return;
                    }
               Mouse.Button = -1;
              }
            Sleep(30);
       }
}
void Fn_Scr_Main() {}
void Fn_Scr_Select_Zone() {}
void Fn_Scr_Load_Map_Details() 
{
     obj_level.Load_Map(&map_zone[int_cur_zone][int_cur_map]);
     obj_power.Init();
     obj_power.Load_Power();
     obj_paddle.Init_Paddle();
     obj_ball.Init_Ball();
     obj_bot.Init();
     obj_sb.Init(int_cur_zone, int_cur_map);
}
void Fn_Game_Loop() 
     {
       while (!bQuit)
       {
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                bQuit = TRUE;
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear (GL_COLOR_BUFFER_BIT);
            //if(KB.key=='n' || KB.key=='N') {  KB.key = -1; return;}
            if(KB.key == 'r' || KB.key == 'R') { stop_playmusic(); Main_Game(); Shutdown(); }
            obj_level.Plot_Map();
            obj_paddle.Plot_Paddle();
            obj_ball.Plot_Ball();
            obj_paddle.Plot_Elec();
            obj_bot.Plot_Bot();
            obj_power.Plot_Power();
            obj_sb.Plot_SB();
			glPushMatrix();
			     glColor3f(1.0f,1.0f,0.0f);
			     PABfont.puttext("Programmed By Vaibhaw Raj",270,-340,500,40,4.5);
				 glColor3f(1.0f,1.0f,1.0f);
			glPopMatrix();
            ShowCursor(FALSE);
            if(KB.key==VK_ESCAPE) 
                {  
                   KB.key = -1;
                   pause_playmusic(); 
                   ingame_pause();
                   resume_playmusic(); 
                }
            else
            {
            SwapBuffers (hDC);
            Sleep(30);
            }            
           //Game Over Detection 
               if(brick_start==NULL)
					{
                      if(int_cur_map + 1 < no_of_levels[int_cur_zone])
					   {
                          if(obj_sb.constant_score())
						   return;
					   }
                      else
                       { 
                       Fn_Game_Over(); 
                       }				
					}

            }
       }
}
void Fn_End_Game() {}
void Fn_About() {}
void Fn_Exit() {}
//Extra Functions
void Add_Power(st_brick_type *ptr)
{
     st_power_type *n_power,*ppt;
         if(ptr->release_power == 1 && ptr->power_type != 0 && power_avail!=NULL)
           {
              n_power = power_avail;
              power_avail=power_avail->next;
              n_power->type = ptr->power_type;
              n_power->dx = ball.dx/2;
              n_power->dy = ball.dy;
              n_power->ay = -1;
              n_power->x = ptr->x;
              n_power->y = ptr->y;
              n_power->width = 5;
              n_power->height = 5;
              n_power->cwidth = 15;
              n_power->cheight = 15;
              n_power->owidth = 50;
              n_power->oheight = 50;
              n_power->rz = 0;
              n_power->cz = ball.cz / 5;
              n_power->next = NULL;
              n_power->text = power_text[n_power->type];
              n_power->enable = 1;
              if (power_start == NULL)
                   power_start = n_power;
                else
                   {
                      ppt = power_start;
                      while(ppt->next != NULL)
                         ppt = ppt->next;
                      ppt->next = n_power;
                   }
              ptr->power_type = 0;
              ptr->release_power = 0;
           }
     obj_power.Start = power_start;
}
void Fn_Game_Over() 
     {
     GLfloat fwidth=300,fheight=75;
     GLfloat fdepth[]={-36.0,-12.0,12.0,36.0},fcentery=0.0;
     int i,j;
     GLfloat xheight,xwidth;
     GLint xdiv=100,ydiv=100;
     GLfloat xwid,yhei;
     GLfloat depth[xdiv+1][ydiv+1];
     GLfloat txwid,tyhei;
     xheight = game_scrheight;
     xwidth = game_scrwidth;
     xwid = (2*xwidth)/xdiv;
     yhei = (2*xheight)/ydiv;
     txwid = 1.0f/xdiv;
     tyhei = 1.0f/ydiv;
     stop_playmusic();
     menu_play();
     for(i=0;i<=xdiv;i++)
       for(j=0;j<=ydiv;j++)
          depth[i][j]=0;
       while (!bQuit)
       {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
                bQuit = TRUE;
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
            /* OpenGL animation code goes here */
            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear (GL_COLOR_BUFFER_BIT);
            ShowCursor(FALSE);
            GLuint text;
            text = zone_bg[1][1];
            if(disable_text==1)
             {
                glEnable(GL_TEXTURE_2D);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
             }
             //BGround
             glPushMatrix();
             glLoadIdentity();
             glColor3f(1.0,1.0,1.0);
             glPushMatrix();
             glLoadIdentity();
             glColor3f(1.0,1.0,1.0);
             glBindTexture(GL_TEXTURE_2D, menutext);
             glTranslatef((GLfloat)-game_scrwidth,-(GLfloat)game_scrheight,scrfar);
             glBegin(GL_LINE_LOOP);
               for(i=0;i<xdiv;i++)
                 for(j=0;j<ydiv;j++)
                    {
                         glTexCoord2f(i*txwid,j*tyhei);  
                            glVertex3f(i*xwid,j*yhei,depth[i][j]);
                         glTexCoord2f(i*txwid + txwid,j*tyhei);  
                            glVertex3f(i*xwid + xwid,j*yhei,depth[i+1][j]);
                         glTexCoord2f(i*txwid + txwid,j*tyhei + tyhei);  
                            glVertex3f(i*xwid + xwid,j*yhei + yhei,depth[i+1][j+1]);
                         glTexCoord2f(i*txwid,j*tyhei + tyhei);  
                            glVertex3f(i*xwid,j*yhei + yhei,depth[i][j+1]);
                    }
             glEnd();
             glPopMatrix();
             glDisable(GL_TEXTURE_2D);
             glDisable(GL_BLEND);
             //BGground
             
             for(i=0;i<=xdiv;i++)
               for(j=0;j<=ydiv;j++)
                  {
                   GLfloat tx,ty,dis;
                   tx = ((-game_scrwidth + (i * xwid)) - (Mouse.X));
                   ty = ((-game_scrheight + (j * yhei)) - (Mouse.Y));
                   dis = sqrt(pow(ty,2) + pow(tx,2));
                   if(dis <= 300)
                      ty=((300-dis)*(700))/300;
                   else
                      ty=0;             
                   depth[i][j]=ty;
                  }
             
                  GLfloat height=450,width=1200;
                  glPushMatrix();
                     glEnable(GL_BLEND);
                     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   
                     glPushMatrix();
                        glTranslatef(-((width/2)+50),((height/2)+15),scrnear);
                        glBegin(GL_QUADS);
                            glColor4f(0.6,0.6,0.0,0.8);
                            glVertex3f(5,35,0);
                            glVertex3f(5,-35,0);
                            glVertex3f(-5,-35,0);
                            glVertex3f(-5,35,0);
                            glVertex3f(65,40,0);
                            glVertex3f(65,30,0);
                            glVertex3f(-5,30,0);
                            glVertex3f(-5,40,0);
                        glEnd();
                     glPopMatrix();
                  glPushMatrix();
                  glTranslatef(((width/2)+50),-((height/2)+15),scrnear);
                  glRotatef(180,0.0,0.0,1.0);
                  glBegin(GL_QUADS);
                      glColor4f(0.6,0.6,0.0,0.8);
                      glVertex3f(5,35,0);
                      glVertex3f(5,-35,0);
                      glVertex3f(-5,-35,0);
                      glVertex3f(-5,35,0);
                      glVertex3f(65,40,0);
                      glVertex3f(65,30,0);
                      glVertex3f(-5,30,0);
                      glVertex3f(-5,40,0);
                  glEnd();
                  glPopMatrix();
                  glPushMatrix();
                  glBegin(GL_QUADS);
                      glColor4f(0.0,0.3,0.0,0.8);
                      glVertex3f(-width/2,height/2,scrnear);
                      glVertex3f(width/2,height/2,scrnear);
                      glVertex3f(width/2,-height/2,scrnear);
                      glVertex3f(-width/2,-height/2,scrnear);
                  glEnd();
                  glBegin(GL_LINE_LOOP);
                      glColor4f(0.0,1.0,1.0,0.8);
                      glVertex3f(-(width-15)/2,(height-15)/2,scrnear);
                      glVertex3f((width-15)/2,(height-15)/2,scrnear);
                      glVertex3f((width-15)/2,-(height-15)/2,scrnear);
                      glVertex3f(-(width-15)/2,-(height-15)/2,scrnear);
                      glVertex3f(-(width-15)/2,(height-15)/2,scrnear);
                  glEnd();
             glDisable(GL_BLEND);
  //   glTranslatef(0.0,0.0,scrnear);
             glPopMatrix();
           
                 //End of Control Panel
             
             //Mouse Cursor
             glPushMatrix();
                glLoadIdentity();
                glTranslatef(Mouse.X,Mouse.Y,scrnear);
                glColor3f(1.0,0.0,0.0);
                glBegin(GL_LINE_LOOP);
                   glVertex3f(0,0,0);
                   glVertex3f(10,-25,0);
                   glVertex3f(10,-10,0);
                   glVertex3f(25,-10,0);
                   glVertex3f(0,0,0);
                   glVertex3f(25,-10,0);
                   glVertex3f(10,-10,0);
                   glVertex3f(10,-8,0);
                   glVertex3f(50,-48,0);
                   for(i=0;i<=5;i++)
                   {
                      glVertex3f(50+(2*i),-(48+(2*i)),0);
                      glVertex3f((50+(2*i))+15,-((50+(2*i))-2),0);
                      glVertex3f(50+(2*i),-(48+(2*i)),0);
                   }
        //           glVertex3f(48,-50,0);
                   for(i=5;i>=0;i--)
                   {
                      glVertex3f(48+(2*i),-(50+(2*i)),0);
                      glVertex3f(48+(2*i),-((65+(2*i))),0);
                      glVertex3f(48+(2*i),-(50+(2*i)),0);
                   }
                   glVertex3f(50,-52,0);
                   glVertex3f(10,-12,0);
                   glVertex3f(10,-10,0);
                   glVertex3f(25,-10,0);                   
                glEnd();
               glPopMatrix();
             //
            char str[100];
			sprintf(str,"Your Score - %d\0",obj_sb.getscore());
        	glPushMatrix();
			     glColor3f(1.0f,1.0f,0.0f);
			     PABfont.puttext("GAME OVER",-120,100,30,40,4.5,1);
				 PABfont.puttext(str,(-1)*(GLfloat)(strlen(str)*28)/2,40,30,40,4.5,1);
			     sprintf(str,"Thank You\0",obj_sb.getscore());
				 PABfont.puttext(str,(-1)*(GLfloat)(strlen(str)*28)/2,-20,30,40,0,1);
				 sprintf(str,"Press Esc Key\0",obj_sb.getscore());
				 PABfont.puttext(str,(-1)*(GLfloat)(strlen(str)*28)/2,-80,30,40,0,1);
				 glColor3f(1.0f,1.0f,1.0f);
			glPopMatrix();
            
			glPushMatrix();
			     glColor3f(1.0f,1.0f,0.0f);
			     PABfont.puttext("Programmed By Vaibhaw Raj",270,-340,500,40,4.5);
				 glColor3f(1.0f,1.0f,1.0f);
			glPopMatrix();
			if(KB.key == VK_ESCAPE)
			    {
                  KB.key = -1;
                  Main_Game();
                }
            SwapBuffers (hDC);
            Sleep(30);
       }

     /////////////////////////////////////////////////////////////

     }
void Fn_Welcome() 
     {
       while (!bQuit)
       {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
                bQuit = TRUE;
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
            /* OpenGL animation code goes here */
            glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
            glClear (GL_COLOR_BUFFER_BIT);
			char str[100];
        	glPushMatrix();
			     glColor3f(1.0f,1.0f,0.0f);
				 sprintf(str,"Evolution : Paddle And Ball Game");
				 PABfont.puttext(str,(-1)*(GLfloat)(strlen(str)*28)/2,320,30,40,4.5,1);
			     sprintf(str,"OOP Project");
			     PABfont.puttext(str,(-1)*(GLfloat)(strlen(str)*28)/2,40,30,40,0,1);
				 sprintf(str,"Sharda University");
			     PABfont.puttext(str,(-1)*(GLfloat)(strlen(str)*28)/2,-20,30,40,0,1);
			     if(int_cur_map == 0)
				        sprintf(str,"Press S To Start");
                 else
                        sprintf(str,"Press C To Continue or S To New Start");
				 PABfont.puttext(str,(-1)*(GLfloat)(strlen(str)*28)/2,-80,30,40,0,1);
				 glColor3f(1.0f,1.0f,1.0f);
			glPopMatrix();
            
			glPushMatrix();
			     glColor3f(1.0f,1.0f,0.0f);
			     PABfont.puttext("Programmed By Vaibhaw Raj",270,-340,500,40,4.5);
				 glColor3f(1.0f,1.0f,1.0f);
			glPopMatrix();
            ShowCursor(FALSE);
            SwapBuffers (hDC);
            Sleep(30);
			if(KB.key == (int)'S' || KB.key == (int)'s')
			   {
                    FILE *fp;
                    fp = fopen("fs_lvl.fs","wb");
                    fsc.map_no = -1;
                    fsc.score = 0;
                    fwrite(&fsc,sizeof(fsc),1,fp);
                    fclose(fp);
                    int_cur_map = 0;
                    int_cur_zone = 0;
                    obj_sb.pass(0);
                    return;
               }
			else if(KB.key == (int)'C' || KB.key == (int)'c')
			   {
                     return;
               }  
       }
     }
void update(int sc,GLfloat x, GLfloat y)
{
	obj_sb.pass(sc,x,y);
}
void ingame_pause()
{
     pause_flag = 1;
     snd_pause();
     GLfloat height=150,width=500;
     glPushMatrix();
        glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   
     glPushMatrix();
     glTranslatef(-((width/2)+50),((height/2)+15),scrnear);
     glBegin(GL_QUADS);
         glColor4f(0.6,0.6,0.0,0.8);
         glVertex3f(5,35,0);
         glVertex3f(5,-35,0);
         glVertex3f(-5,-35,0);
         glVertex3f(-5,35,0);
         glVertex3f(65,40,0);
         glVertex3f(65,30,0);
         glVertex3f(-5,30,0);
         glVertex3f(-5,40,0);
     glEnd();
     glPopMatrix();
     glPushMatrix();
     glTranslatef(((width/2)+50),-((height/2)+15),scrnear);
     glRotatef(180,0.0,0.0,1.0);
     glBegin(GL_QUADS);
         glColor4f(0.6,0.6,0.0,0.8);
         glVertex3f(5,35,0);
         glVertex3f(5,-35,0);
         glVertex3f(-5,-35,0);
         glVertex3f(-5,35,0);
         glVertex3f(65,40,0);
         glVertex3f(65,30,0);
         glVertex3f(-5,30,0);
         glVertex3f(-5,40,0);
     glEnd();
     glPopMatrix();
     glPushMatrix();
     glBegin(GL_QUADS);
         glColor4f(0.0,0.3,0.0,0.5);
         glVertex3f(-width/2,height/2,scrnear);
         glVertex3f(width/2,height/2,scrnear);
         glVertex3f(width/2,-height/2,scrnear);
         glVertex3f(-width/2,-height/2,scrnear);
     glEnd();
     glBegin(GL_LINE_LOOP);
         glColor4f(0.0,0.1,0.0,0.5);
         glVertex3f(-(width-15)/2,(height-15)/2,scrnear);
         glVertex3f((width-15)/2,(height-15)/2,scrnear);
         glVertex3f((width-15)/2,-(height-15)/2,scrnear);
         glVertex3f(-(width-15)/2,-(height-15)/2,scrnear);
         glVertex3f(-(width-15)/2,(height-15)/2,scrnear);
     glEnd();
     glDisable(GL_BLEND);
  //   glTranslatef(0.0,0.0,scrnear);
     glPopMatrix();
     glPushMatrix();
     glColor3f(0.7,0.3,1.0);
     PABfont.puttext("Pause",-(width-10)/2,(height-10)/2,(width-10),(height-10),4.5);
     glPopMatrix();
     SwapBuffers(hDC);
     while (!bQuit)
       {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
         
            if (msg.message == WM_QUIT)
                bQuit = TRUE;
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }

        KB.key==VK_ESCAPE;
        if(KB.key==VK_ESCAPE)
        {
           pause_flag=0;
           snd_pause(); 
           KB.key = -1; 
           return;
        }        
        Sleep(30);
       }
}

