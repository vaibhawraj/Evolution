//PABtexture.cpp
//Code Added By Vaibhaw Raj, 110101266
//Created On Sept 16, 2012
//Code Added On Sept 18, 2012
//Code Added On Sept 21, 2012
//Code Added On Sept 22, 2012
//Code Added On Sept 28, 2012
//Code Added On Sept 29, 2012
//Code Added On Oct 3, 2012
//Code Addded On Oct 25, 2012     //Added New Level Loading Mechanism
#ifndef PABtexture_CPP
#define PABtexture_CPP
int x;
int y=0;
int pc=0; //progress_count
int width=35;
void Load_Texture() 
{
     
       int i,j;
       char tex_fn[50];
       x=(int) border.x1;
       FILE *gpc;
       gpc = fopen("fpc.pc","rb");
       if(gpc!=NULL)
       {fread(&width,sizeof(pc),1,gpc);
        width = (int)game_scrwidth / width;
        fclose(gpc);
       }
       gpc = NULL;
     //Loading Blue Brick Texture (L)
      for(i=5;i>=0;i--)
       {
        sprintf(tex_fn,"texture/bbt%d.raj",i);
        if(!texture_image.Load(tex_fn)) {Error_Code(1101,tex_fn); return;}
        glGenTextures(1, &brick_texture[1][i]);
        glBindTexture(GL_TEXTURE_2D, brick_texture[1][i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_image.GetWidth(), texture_image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image.GetImage());
        texture_image.Release();
        loading_progress();
       }
       for(i=5;i>=0;i--)
       {
        sprintf(tex_fn,"texture/tbt%d.raj",i);
        if(!texture_image.Load(tex_fn)) {Error_Code(1101,tex_fn); return;}
        glGenTextures(1, &brick_texture[2][i]);
        glBindTexture(GL_TEXTURE_2D, brick_texture[2][i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_image.GetWidth(), texture_image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image.GetImage());
        texture_image.Release();
        loading_progress();
       }
       for(i=5;i>=0;i--)
       {
        sprintf(tex_fn,"texture/lbt%d.raj",i);
        if(!texture_image.Load(tex_fn)) {Error_Code(1101,tex_fn); return;}
        glGenTextures(1, &brick_texture[3][i]);
        glBindTexture(GL_TEXTURE_2D, brick_texture[3][i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_image.GetWidth(), texture_image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image.GetImage());
        texture_image.Release();
        loading_progress();
       }
      //  send_report("Bricks\n");
      //Power
      for(i=1;i<8;i++)
       {
        sprintf(tex_fn,"texture/pt%d.raj",i);
        if(!texture_image.Load(tex_fn)) {Error_Code(1101,tex_fn); return;}
        glGenTextures(1, &power_text[i]);
        glBindTexture(GL_TEXTURE_2D, power_text[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_image.GetWidth(), texture_image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image.GetImage());
        texture_image.Release();
        loading_progress();
       } 
            //   send_report("Power\n");
       //Weapon
       if(!texture_image.Load("texture/w1.raj")) {Error_Code(1101,"w1.raj"); return;}
        glGenTextures(1, &wp);
        glBindTexture(GL_TEXTURE_2D, wp);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_image.GetWidth(), texture_image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image.GetImage());
        texture_image.Release();
        loading_progress();
       //Thumbnail
       if(!texture_image.Load("texture/thumb.raj")) {Error_Code(1101,"w1.raj"); return;}
        glGenTextures(1, &thumb);
        glBindTexture(GL_TEXTURE_2D, thumb);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_image.GetWidth(), texture_image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image.GetImage());
        texture_image.Release();
        loading_progress();
      
		//      send_report("Weapons\n");
        //Bullet
        for(i=1;i<=3;i++)
        {
        sprintf(tex_fn,"texture/bu%d.raj",i);
        if(!texture_image.Load(tex_fn)) {Error_Code(1101,tex_fn); return;}
        glGenTextures(1, &bu[i-1]);
        glBindTexture(GL_TEXTURE_2D, bu[i-1]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_image.GetWidth(), texture_image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image.GetImage());
        texture_image.Release();
        loading_progress();
        }
        //        send_report("Bullets\n");
        //Ball
        if(!texture_image.Load("texture/bball.raj")) {Error_Code(1101,"bball.raj"); return;}
        glGenTextures(1, &ball_text_A);
        glBindTexture(GL_TEXTURE_2D, ball_text_A);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_image.GetWidth(), texture_image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image.GetImage());
        texture_image.Release();
        loading_progress();
		//PABfontface
		if(!texture_image.Load("texture/PABFont.raj")) {Error_Code(1101,"PABfont.raj"); return;}
        glGenTextures(1, &PABfontface);
        glBindTexture(GL_TEXTURE_2D, PABfontface);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_image.GetWidth(), texture_image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image.GetImage());
        texture_image.Release();
        loading_progress();
     
                 //       send_report("Ball\n");
        //Paddle Holder
        if(!texture_image.Load("texture/ph.raj")) {Error_Code(1101,"ph.raj"); return;}
        glGenTextures(1, &ph);
        glBindTexture(GL_TEXTURE_2D, ph);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_image.GetWidth(), texture_image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image.GetImage());
        texture_image.Release();
        loading_progress();        
                // send_report("PAddleHolder\n");
        //Paddle Left
        if(!texture_image.Load("texture/pleft.raj")) {Error_Code(1101,"pleft.raj"); return;}
        glGenTextures(1, &pl);
        glBindTexture(GL_TEXTURE_2D, pl);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_image.GetWidth(), texture_image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image.GetImage());
        texture_image.Release();
        loading_progress();
                        // send_report("Paddle LEft\n");
        //Paddle Right
        if(!texture_image.Load("texture/pright.raj")) {Error_Code(1101,"pright.raj"); return;}
        glGenTextures(1, &pr);
        glBindTexture(GL_TEXTURE_2D, pr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_image.GetWidth(), texture_image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image.GetImage());
        texture_image.Release();
        loading_progress();
                // send_report("Paddle Right\n");
        //Paddle
        if(!texture_image.Load("texture/pdl.raj")) {Error_Code(1101,"pright.raj"); return;}
        glGenTextures(1, &pdl);
        glBindTexture(GL_TEXTURE_2D, pdl);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_image.GetWidth(), texture_image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image.GetImage());
        texture_image.Release();
        loading_progress();
        //Menu texture
        if(!texture_image.Load("texture/mscr.raj")) {Error_Code(1101,"mscr.raj"); return;}
        glGenTextures(1, &menutext);
        glBindTexture(GL_TEXTURE_2D, menutext);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_image.GetWidth(), texture_image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image.GetImage());
        texture_image.Release();
        loading_progress();
                        // send_report("Paddle\n");
        //Score Board Background
        if(!texture_image.Load("texture/sb_bg.raj")) {Error_Code(1101,"sb_bg.raj"); return;}
        glGenTextures(1, &sb_bg);
        glBindTexture(GL_TEXTURE_2D, sb_bg);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_image.GetWidth(), texture_image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image.GetImage());
        texture_image.Release();
        loading_progress();
                        // send_report("Score Board\n");
        //Alien Bot Default pose
		j=0;
        for(j=0;j<=7;j++)
        {
        if(j==3 || j==6) continue;
        for(i=0;i<=7;i++)
        {
          if((j==5 && i==5)|| (j==1 && i==5) || (j==7 && i==4)) break;
          sprintf(tex_fn,"texture/AlienBot/AlienBot%d%d.raj",j,i);
          if(!texture_image.Load(tex_fn)) {Error_Code(1101,tex_fn); return;}
          glGenTextures(1, &bot[0][j][i]);
          glBindTexture(GL_TEXTURE_2D, bot[0][j][i]);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_image.GetWidth(), texture_image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image.GetImage());
          texture_image.Release();
		  // send_report(tex_fn);
		  // send_report("\n");
         loading_progress();          
        }
        }
        //Alien Bot Bomb
        for(i=0;i<=5;i++)
        {
          sprintf(tex_fn,"texture/AlienBot/BotBomb%d.raj",i);
          if(!texture_image.Load(tex_fn)) {Error_Code(1101,tex_fn); return;}
          glGenTextures(1, &bomb[0][i]);
          glBindTexture(GL_TEXTURE_2D, bomb[0][i]);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_image.GetWidth(), texture_image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image.GetImage());
          texture_image.Release();
		  // send_report(tex_fn);
		  // send_report("\n");
          loading_progress();          
        }
        //Zone Map Background
        for(i=1;i<=1;i++)
          for(j=1;j<=6;j++)
            {
               sprintf(tex_fn,"map/zone%dmap%d.map",i,j);
               if(!texture_image.Load(tex_fn)) {Error_Code(1101,tex_fn); continue;}
               glGenTextures(1, &zone_bg[i][j]);
               glBindTexture(GL_TEXTURE_2D, zone_bg[i][j]);
               glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
               glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
               glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture_image.GetWidth(), texture_image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_image.GetImage());
               texture_image.Release();
               loading_progress();               
            }
          FILE *fpc;
          fpc = fopen("fpc.pc","wb");
          fwrite(&pc,sizeof(pc),1,fpc);
          fclose(fpc);
		  fpc = NULL;
     glEnable(GL_TEXTURE_2D); //Enable TextuLe
}
void Load_Maps() 
{
//Zone 1 Map 1
     int b=0,count=0;
     int i=0,j=0,level=0,zone=0;
     st_lvl lvl;
     FILE *fp=NULL;
     char lvlname[30];
     //Count Total Number Of Levels
     //For All Zone
     for(j=1;j<=3;j++)
     {
     i=0;
     do
     {
           i++;
           if(fp!=NULL) fclose(fp);
           sprintf(lvlname,"levels/zone %d/level%d.lvl",j,i);
           fp=fopen(lvlname,"rb");
     }while(fp!=NULL);
     no_of_levels[j-1]=i-1;
     }
     
     //Loading Map
     FILE *flvl;
     for(zone=0;zone<3;zone++)
     for(level=0;level<no_of_levels[zone];level++)
     {
        //Read Level
        sprintf(lvlname,"levels/zone %d/level%d.lvl",zone+1,level+1);
        flvl=fopen(lvlname,"rb");
        if(flvl==NULL) Error_Code(1101,lvlname);
        fread(&lvl,sizeof(lvl),1,flvl);
        fclose(flvl);
        //Decode Level And Store Level
        b=0;
        for(j=0;j<lvl.row;j++)
          for(i=0;i<lvl.col;i++)
            map_zone[zone][level].Map[j][i]=lvl.map[b++];
        map_zone[zone][level].col = lvl.col;
        map_zone[zone][level].row = lvl.row;
        map_zone[zone][level].width = lvl.width;
        map_zone[zone][level].height = lvl.height;
        map_zone[zone][level].No_of_brick = lvl.nob;
     } 
}
void Load_Enviroment() 
{
     glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       glFrustum(-game_scrwidth/2,game_scrwidth/2,-game_scrheight/2,game_scrheight/2,-scrnear,-scrfar);
       glViewport(0, 0, scrwidth, scrheight);
     glMatrixMode(GL_MODELVIEW);
     
     border.x1 = -game_scrwidth/2;
     border.x2 = game_scrwidth/2;
     border.y2 = -game_scrheight/2;
     border.y1 = game_scrheight/2;
     
     join_array();
}

void loading_progress()
{
       glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
       glClear (GL_COLOR_BUFFER_BIT);
       glPushMatrix();
       glLoadIdentity();
       glTranslatef((GLfloat)border.x1,(GLfloat)y,scrnear);
       for(GLfloat i=border.x1;i<=x;i=i+width)
       {
       glColor3f(1.0,0.0,0.0);
       glBegin(GL_QUADS);
          glVertex2i(0,70);
          glVertex2i(width - 5,70);
          glVertex2i(width - 5,-70);
          glVertex2i(0,-70);
       glEnd();
              glTranslatef((GLfloat)width,0.0,0.0);
       }
       glPopMatrix();
       x += width;
     if(x>border.x2)
      {
         y = y - 140;
         x = (int)border.x1;
      }
     SwapBuffers(hDC);
	 Sleep(10);
     pc++;
}
#endif
