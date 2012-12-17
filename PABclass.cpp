//PABclass.cpp
//Code Added By Vaibhaw Raj, 110101266
//Created On Sept 16, 2012
//Code Added On Sept 18, 2012
//Code Added On Sept 21, 2012
//Code Added On Sept 22, 2012
//Code Added On Sept 29, 2012
//Code Added On Oct 2, 2012
//Code Added On Oct 25, 2012    //Updated Brick Single Link List To Brick Multiple Link List
                                //Updated Level Loading Mechanisim
//Code Added On Oct 26, 2012    //Fire Arms Attached
                                //Alien Bots Added
//Code Added On Dec 09, 2012    //Music And Sound Effect
#ifndef PABclass_CPP
#define PABclass_CPP


void cl_level::Init_Brick(st_brick_type *temp)
{
    temp->row = 0;
    temp->col = 0;
    temp->x = 0;
    temp->y = 0;
    temp->z = scrnear;
    temp->height = 50;
    temp->width = 150;
    temp->type = 1;
    temp->anim = 0;   //for static or animation code
    temp->ny = 6;     //inertial accelaration for brick pos movement
    temp->frame = 0;
    temp->power_type = 0;
    temp->strength = 3; 
    temp->release_power = 0;
	temp->color[0] = 0.2f;
	temp->color[1] = 0.2f;
	temp->color[2] = 0.2f;
    temp->next = NULL;
    temp->prev = NULL;
    temp->u1 = NULL;
    temp->u2 = NULL;
    temp->d1 = NULL;
    temp->d2 = NULL;
    temp->p1 = NULL;
    temp->p2 = NULL;
    temp->n1 = NULL;
    temp->n2 = NULL;
    temp->bot = NULL;
}

void cl_level::Load_Map(st_map_type *map)
{
     int i=0,j=0;
	 GLfloat x_start=0, y_start=0, x_pos=0,y_pos=0,map_height,avail_space;
     st_brick_type *n_brick, *ptr, *tptr;
     Release(Start);
     timer = 0;
     //Specifying Play Area 
     border.x2 = (game_scrwidth/2) - 300;
     x_pos = (GLfloat)(-((map->width)*(map->col))/2 - 150);
     map_height = (GLfloat)((map->row) * (map->height));
     avail_space = game_scrheight/2;
     y_pos = (avail_space - map_height) / 2;
     y_pos = map_height + y_pos;
     x_start = x_pos;
     y_start = y_pos;
     //Creating Bricks
	 ptr = NULL;
     for(i=0;i<map->row;i++)
        {
        for(j=0;j<map->col;j++)
          {
            if(map->Map[i][j]!=' ' && map->Map[i][j]!='\n')
            {
                if(brick_avail == NULL)
                     Error_Code(1102);
                n_brick = brick_avail;
                brick_avail = n_brick->next;
                n_brick->next = NULL;
                Init_Brick(n_brick);
                n_brick->row = i;
                n_brick->col = j;
                n_brick->x = x_pos + j*map->width;
                n_brick->y = y_pos - i*map->height;
                n_brick->oy = y_pos - i*map->height;
                n_brick->ox = x_pos + j*map->width;
                n_brick->height = (GLfloat) map->height;
                n_brick->width = (GLfloat) map->width;
          		switch(rand()%4)
				{
				   case 0: n_brick->color[0]=n_brick->color[1]=n_brick->color[2]=1.0f;//Actual
					   break;
				   case 1: n_brick->color[0] = 1.0f; break;
				   case 2: n_brick->color[1] = 1.0f; break;
				   case 3: n_brick->color[2] = 1.0f; break;
				}
        
                switch(map->Map[i][j])
                {
                   case 's':
                   case 'S':
                        n_brick->type = 1;//(int)map->Map[i][j];
                        break;
                   case 't':
                   case 'T':
                        n_brick->type = 2;
                        n_brick->strength = 1;
                          n_brick->color[0]=n_brick->color[1]=n_brick->color[2]=1.0f;//Actual
                        break;
                   case 'l':
                   case 'L':
                        n_brick->type = 3;
                        n_brick->strength = 1;
                        n_brick->color[0]=n_brick->color[1]=n_brick->color[2]=1.0f;//Actual
                        break;
                   default:
                        n_brick->type = 1;
                }
                n_brick->text = brick_texture[n_brick->type][0];
		        if (Start == NULL)
                   Start = n_brick;
                else
                   ptr->next = n_brick;
                n_brick->prev = ptr;
                ptr = n_brick;
                }            
            }
        }
     ptr = Start;
     while(ptr!=NULL)
     {
                                          
        //For Up
        tptr=NULL;
        if(ptr->col-1 >= 0)
           {
              tptr=Start;
              while(tptr!=NULL)
              {
                 if((tptr->col == ptr->col-1) && (tptr->row == ptr->row)) break;
                 tptr = tptr->next;
              }
              ptr->p1 = tptr;
              if(tptr!=NULL) tptr->n1 = ptr;
           }
        if(ptr->col-2 >= 0)
           {
              tptr=Start;
              while(tptr!=NULL)
              {
                 if((tptr->col == ptr->col-2) && (tptr->row == ptr->row)) break;
                 tptr = tptr->next;
              }
              ptr->p2 = tptr;
              if(tptr!=NULL) tptr->n2 = ptr;
           }
        if(ptr->row-1 >= 0)
           {
              tptr=Start;
              while(tptr!=NULL)
              {
                 if((tptr->row == ptr->row-1) && (tptr->col == ptr->col)) break;
                 tptr = tptr->next;
              }
              ptr->u1 = tptr;
              if(tptr!=NULL) tptr->d1 = ptr;
           }
        if(ptr->row-2 >= 0)
           {
              tptr=Start;
              while(tptr!=NULL)
              {
                 if((tptr->row == ptr->row-2) && (tptr->col == ptr->col)) break;
                 tptr = tptr->next;
              }
              ptr->u2 = tptr;
              if(tptr!=NULL) tptr->d2 = ptr;
           }
        ptr = ptr->next;
     } 
     brick_start = Start;
     //Ploting Bricks
     Plot_Map();
}

void cl_level::Release(st_brick_type *temp)
{
     st_brick_type *ptr,*pptr;
     if(temp!=NULL)
       {
         ptr = temp;
         while(ptr!=NULL)
         {
            pptr = ptr->next;
            ptr->next = brick_avail;
            brick_avail = ptr;
            ptr = pptr;
         }
         temp=NULL;
       }
     Start = NULL;
     brick_start = NULL;
}

void cl_level::Plot_Map()
{
     st_brick_type *ptr,*pptr;
     ptr = Start;
     pptr = NULL;
     if(disable_text==1)
     {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     }
     glPushMatrix();
       glLoadIdentity();
       switch(int_cur_map/6)
       {
          case 1:
             glColor3f(0.0,1.0,0.0);
             break;
          case 0:
             glColor3f(1.0,1.0,1.0);
             break;
          case 2:
             glColor3f(1.0,0.0,0.0);
             break;
          case 3:
             glColor3f(0.0,0.0,1.0);
             break;
          case 4:
             glColor3f(1.0,0.0,1.0);
             break;
          case 5:
             glColor3f(1.0,1.0,0.0);
             break;
          case 6:
             glColor3f(0.0,1.0,1.0);
             break;
          default:
             glColor3f(0.0,0.5,1.0);
             break;
       }
       glBindTexture(GL_TEXTURE_2D, zone_bg[int_cur_zone+1][(int_cur_map%6)+1]);
       glTranslatef((GLfloat)-game_scrwidth/2,(GLfloat)game_scrheight/2,scrnear);
       glBegin(GL_QUADS);
          glTexCoord2i(0,1);  glVertex2f(0,0);
          glTexCoord2i(1,1);  glVertex2f(game_scrwidth,0);
          glTexCoord2i(1,0);  glVertex2f(game_scrwidth,(-1)*game_scrheight);
          glTexCoord2i(0,0);  glVertex2f(0,(-1)*game_scrheight);
       glEnd();
     glPopMatrix();
     while(ptr!=NULL)
         {
           if(ptr->strength == 0)
             {
                if(ptr->type==1)
                   brickHit(4);
                st_brick_type *tptr;
                tptr = ptr->u1; if(tptr!=NULL)tptr->d1=NULL;
                tptr = ptr->u2; if(tptr!=NULL)tptr->d2=NULL;
                tptr = ptr->p1; if(tptr!=NULL)tptr->n1=NULL;
                tptr = ptr->p2; if(tptr!=NULL)tptr->n2=NULL;    
                tptr = ptr->next; if(tptr!=NULL) tptr->prev = ptr->prev;          
                if(pptr==NULL)
                   {
                      Start = ptr->next;;
                      ptr->next = brick_avail;
                      brick_avail = ptr;
					  ptr=Start;
                      brick_start=Start;
                      continue;
                   }
                else
                   {
                      pptr->next = ptr->next;
                      ptr->next = brick_avail;
                      brick_avail = ptr;
                      ptr = pptr->next;
                      continue;
                   }
             }
		   Animate(ptr);
           Draw_Brick(ptr);
           pptr = ptr;
           ptr = ptr->next;
         }
     glDisable(GL_TEXTURE_2D);
     glDisable(GL_BLEND);
     timer++;
}

void cl_level::Animate(st_brick_type *ptr)
{
     if((ptr->strength != 0) && (ptr->strength != -1)) 
       {
         if(ptr->type == 1) ptr->text = brick_texture[ptr->type][3 - ptr->strength];
         if(ptr->type == 2 || ptr->type == 3) ptr->text = brick_texture[ptr->type][ptr->frame];
       }
     switch(ptr->anim)
     {
        case 0:
          if(ptr->type == 2 && timer%20==0) ptr->frame=(ptr->frame+1)%3;
          if(ptr->type == 3 && timer%20==0) ptr->frame=(ptr->frame+1)%3;
          break;
        case -1:  //Left
           ptr->ny -= 2;
           ptr->x=ptr->x + ptr->ny;
           if(ptr->x <= ptr->ox)
              {
                 ptr->x=ptr->ox;
                 ptr->anim=0;
                 ptr->ny=6;
              }
           break;  
        case 1:   //Right
           ptr->ny -= 2;
           ptr->x=ptr->x - ptr->ny;
           if(ptr->x >= ptr->ox)
              {
                 ptr->x=ptr->ox;
                 ptr->anim=0;
                 ptr->ny=6;
              }
           break;  
        case 2:   //Top
           ptr->ny -= 2;
           ptr->y=ptr->y - ptr->ny;
           if(ptr->y >= ptr->oy)
              {
                 ptr->y=ptr->oy;
                 ptr->anim=0;
                 ptr->ny=6;
              }
           break;  
        case 3:   //Bottom
           ptr->ny -= 2;
           ptr->y=ptr->y + ptr->ny;
           if(ptr->y <= ptr->oy)
              {
                 ptr->y=ptr->oy;
                 ptr->anim=0;
                 ptr->ny=6;
              }
         break;  
         case -4:
            if(ptr->type == 1)ptr->text = brick_texture[ptr->type][ptr->frame++];
            if(timer%2==0 && ptr->type == 2)ptr->text = brick_texture[ptr->type][ptr->frame++];
            if(timer%2==0 && ptr->type == 3)ptr->text = brick_texture[ptr->type][ptr->frame++];
            if(ptr->type == 1)
            {
            ptr->x -= 10;
            ptr->y += 10;
            ptr->height += 20;
            ptr->width += 20; 
            }
            if(ptr->type==3 && timer%2 == 0)
            {
            ptr->x -= 5;
            ptr->y += 5;
            ptr->height += 10;
            ptr->width += 10; 
            }
            if(ptr->type == 1 && ptr->frame == 6) {ptr->strength = 0;ptr->frame = 0;}
            if(ptr->type == 2 && ptr->frame == 6) {ptr->strength = 0;ptr->frame = 0;}
            if(ptr->type == 3 && ptr->frame == 6) {ptr->strength = 0;ptr->frame = 0;}
         break;
     } 
}
void cl_level::Draw_Brick(st_brick_type *ptr)
{
     glPushMatrix();
       
       glLoadIdentity();
       glTranslatef((GLfloat)ptr->x, (GLfloat)ptr->y, (GLfloat)ptr->z);
       glBindTexture(GL_TEXTURE_2D, ptr->text);
       glBegin (GL_QUADS); 
       glColor3fv(ptr->color);
               glTexCoord2f(0,0);               glVertex3f(0,0,0);
               glTexCoord2f(0,1);               glVertex3f(0,-(ptr->height),0);
               glTexCoord2f(1,1);               glVertex3f((ptr->width),-(ptr->height),0);
               glTexCoord2f(1,0);               glVertex3f((ptr->width),0,0);
       glEnd();
       glColor3f(1.0,1.0,1.0);
     glPopMatrix();
}

void cl_paddle::Plot_Paddle()
{
     if(paddle.olength > paddle.length) {paddle.length+=4; paddle.x -= 2;}
     if(paddle.olength+5 < paddle.length) {paddle.length-=4; paddle.x += 2; }
     if(tx!=Mouse.X)
     {
       tx = Mouse.X - tx;
       paddle.x += tx;
       tx = Mouse.X;
     }
     if(paddle.x < border.x1) paddle.x=border.x1;     
     if((paddle.x + paddle.length)>border.x2)
        paddle.x = border.x2 - paddle.length;   

     Draw_Paddle();
}
void cl_paddle::Plot_Elec()
{
     int var=0;
     if(paddle.magnet == 1) return;
     GLfloat col=0;
     glPushMatrix();
               glLoadIdentity();
               col=(GLfloat)((rand()%10))/((GLfloat)10);
               glColor3f(col,col,col);
               glTranslated(paddle.x+5, paddle.y - paddle.width + 38, scrnear);
               glBegin (GL_LINE_STRIP);
                 for(int i=0;i <= paddle.length - 13;)
                     {
                       glVertex2i(i , var - 6);
                       var = (rand()%10);
                       i=i + rand()%5;
                     }
                 glVertex2f(paddle.length - 9 ,-6);
               glEnd();           
               glColor3f(1.0,1.0,1.0);
       glPopMatrix();
}
void cl_paddle::Draw_Paddle()
{
     glPushMatrix();
       glColor3f(0.0,0.0,1.0);
       glLoadIdentity();
       if(disable_text==1)
             {
              glEnable(GL_TEXTURE_2D);
              glEnable(GL_BLEND);
              glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
             }
       switch(paddle.type)
       {
         case 1:
         default:
             //Paddle
             glPushMatrix();
               glLoadIdentity();
               glBindTexture(GL_TEXTURE_2D, pdl);
               glColor3f(1.0,1.0,1.0);
               glTranslated(paddle.x, paddle.y - paddle.width + 8, scrnear);
               glBegin (GL_QUADS);
                 glTexCoord2i(0,1); glVertex2f(0,0);
                 glTexCoord2i(0,0); glVertex2f(0, -8);
                 glTexCoord2i(1,0); glVertex2f(paddle.length, -8);
                 glTexCoord2i(1,1); glVertex2f(paddle.length,0);
               glEnd();           
             glPopMatrix();
             //Paddle Left
             glPushMatrix();
               glLoadIdentity();
               glBindTexture(GL_TEXTURE_2D, pl);
               glColor3f(1.0,1.0,1.0);
               glTranslatef((GLfloat)(paddle.x - 10), (GLfloat)(paddle.y - paddle.width + 39), scrnear);
               glBegin (GL_QUADS);
                 glTexCoord2i(0,1); glVertex2i(0,0);
                 glTexCoord2i(0,0); glVertex2i(0, -84);
                 glTexCoord2i(1,0); glVertex2i(30, -84);
                 glTexCoord2i(1,1); glVertex2i(30,0);
               glEnd();           
             glPopMatrix();
             //Paddle Right
             glPushMatrix();
               glLoadIdentity();
               glBindTexture(GL_TEXTURE_2D, pr);
               glColor3f(1.0,1.0,1.0);
               glTranslatef((GLfloat)paddle.x + (GLfloat)paddle.length - 20, (GLfloat)paddle.y - (GLfloat)paddle.width + 39, scrnear);
               glBegin (GL_QUADS);
                 glTexCoord2i(0,1); glVertex2i(0,0);
                 glTexCoord2i(0,0); glVertex2i(0, -84);
                 glTexCoord2i(1,0); glVertex2i(30, -84);
                 glTexCoord2i(1,1); glVertex2i(30,0);
               glEnd();           
             glPopMatrix();
       }
       glPushMatrix();
           glLoadIdentity();
           glTranslatef((GLfloat)paddle.x + (GLfloat)((paddle.length - 92)/2), (GLfloat)paddle.y - (GLfloat)paddle.width, scrnear);
           glBindTexture(GL_TEXTURE_2D, ph);
           glColor3f(1.0, 1.0, 1.0);
           glBegin (GL_QUADS);
               glTexCoord2i(0,1); glVertex2i(0,0);
               glTexCoord2i(0,0); glVertex2i(0, -75);
               glTexCoord2i(1,0); glVertex2i(92, -75);
               glTexCoord2i(1,1); glVertex2i(92,0);
           glEnd();
       glPopMatrix();
       glColor3f(1.0,1.0,1.0);
     glPopMatrix();
     glDisable(GL_TEXTURE_2D);
     glDisable(GL_BLEND);
}

void cl_paddle::Init_Paddle()
{
     paddle.length = 200;
     paddle.olength = paddle.length;
     paddle.x = Mouse.X;
     paddle.y = (100-(game_scrheight/2));
     paddle.type = 1;
     paddle.width = 25;
     paddle.magnet = 0;
     tx=Mouse.X;
}

void cl_ball::Init_Ball()
{
     int i=0;
     tail_len=10;
     delay = 0;
     ball.x = paddle.x + ((paddle.x + paddle.length)/2);
     ball.radius = 15;
     ball.y = paddle.y - paddle.width + 10 + ball.radius ;// + ball.radius;
     ball.maxspeed = 13;
     ball.dx = (-1) * ball.maxspeed;
     ball.dy = ball.maxspeed;
     ball.type = 1;
     ball.rz = 0;
     ball.cz = 0;
     ball.stick = 1;
     ball.stpos = paddle.length/2;
     for(i=0;i<tail_len;i++)
        tail_queue[i] = ball; 
     snd_ball_up();
}

void cl_ball::Plot_Ball()
{
     int i=0;
     if(ball.stick == 1)
        ball.x = paddle.x + ball.stpos;
     else
       {
          ball.x = ball.x + ball.dx;
          ball.y = ball.y + ball.dy;
          Detect_Collision();
       }
     delay=delay+1;
     if(delay>=1) delay=0;
     if(delay==0)
       {
       for(i=tail_len-1;i>0;i--)
          tail_queue[i] = tail_queue[i-1];
        tail_queue[0] = ball;
       }
     Draw_Tail();
     if(disable_text==1)
     {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     }
     ball.rz += ball.cz; //rotating
     Draw_Ball();
     glDisable(GL_BLEND);
     glDisable(GL_TEXTURE_2D);
}

void cl_ball::Draw_Ball()
{
     GLUquadric *nObj;
     nObj = gluNewQuadric();
     glPushMatrix();
        glLoadIdentity();
        glTranslatef((GLfloat)ball.x, (GLfloat)ball.y, scrnear);
        glRotatef((GLfloat)ball.rz,0.0,0.0,1.0);
        glColor3f(1.0,1.0,1.0);
        glBindTexture(GL_TEXTURE_2D, ball_text_A); 
        glBegin(GL_QUADS);
                          glTexCoord2f(0,1);        glVertex2f(-ball.radius,ball.radius);  
                          glTexCoord2f(0,0);        glVertex2f(-ball.radius,-ball.radius);
                          glTexCoord2f(1,0);        glVertex2f(ball.radius,-ball.radius);
                          glTexCoord2f(1,1);        glVertex2f(ball.radius,ball.radius);
        glEnd();
        glDisable(GL_BLEND); 
     glPopMatrix();
}

void cl_ball::Draw_Tail()
{
     int i ;
     float diff=1.0f;
     float j=0.0, dj = 1.0f/((float)tail_len);
     GLUquadric *nObj;
     diff = (float)(ball.radius / (tail_len));
     for(i=0;i<tail_len;i++)
     {
     nObj = gluNewQuadric();
     glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     glPushMatrix();
        glLoadIdentity();
        glTranslatef(tail_queue[i].x, tail_queue[i].y, scrnear);
        glColor4f((1.0f - j), (1.0f - j)/2 , 0.0f,0.3f);
        gluDisk(nObj, 0, ball.radius - ((i+1)*diff), 60, 1);
        glColor4f((1.0f - j), (1.0f - j)/2 , j/5,0.5f);
        gluDisk(nObj, 0, (ball.radius - ((i+1)*diff))/1.5, 60, 1);
        glColor4f((1.0f - j), (1.0f - j)/2 , j/2,0.8f);
        gluDisk(nObj, 0, (ball.radius - ((i+1)*diff))/2.0, 60, 1);
        glColor4f((1.0f - j), (1.0f - j)/2 , j,1.0f);
        gluDisk(nObj, 0, (ball.radius - ((i+1)*diff))/2.5, 60, 1);
        j=j+dj;
     glPopMatrix();
     glDisable(GL_BLEND);
     }
}

void cl_ball::Detect_Collision()
{
     GLfloat tmpx,tmpy;
     tmpx=ball.dx;
     tmpy=ball.dy;
     if(ball.stick == 1) return;
     GLfloat left = (-1)*ball.maxspeed, right = ball.maxspeed;
     st_brick_type *ptr=NULL;
  //   st_bot_type *btemp=NULL;
     //detect boundary
     if( ((ball.x - ball.radius) <= border.x1 && ball.dx<0) || (ball.x + ball.radius >= border.x2 && ball.dx>0)) ball.dx *= -1;
     if( ball.y + ball.radius >= border.y1 && (ball.dy>0) ) ball.dy *= -1;
	 if( ball.y <= border.y2 ) 
        {
                if(timer==0)
                  {
                    no_of_ball--;
                    if(no_of_ball<=0)
                       Fn_Game_Over();
                  }
                timer++;
                if(timer>=40) 
                     Init_Ball();
        }  //Game Over
     else timer = 0;
     //paddle detect     
     if( ball.x >= paddle.x && ball.x <= (paddle.x + paddle.length))
            if((ball.y - ball.radius <= paddle.y) && (ball.y + ball.radius >= paddle.y) ) 
              {
                 if(ball.dy < 0) ball.dy *= -1;  
                 ball.dx = (int)((float)(right - left) * (float)((float)(ball.x - paddle.x)/(float)paddle.length)) + left;
                 ball.cz = (int)((float)(right - left) * (float)((float)(ball.x - paddle.x)/(float)paddle.length)) + left;
                 ball.cz *=  5;
                 if(paddle.magnet==1)
                   {
                       ball.stick = 1;
                       ball.stpos = ball.x - paddle.x;
                       paddle.magnet = 0;
                   }
              }
     if( ball.y - ball.radius <= (paddle.y - paddle.width + 38) && ball.y >= (paddle.y - paddle.width - 38))
           {
             if((ball.x + ball.radius >= paddle.x && ball.x <= paddle.x))
                if(ball.dx>0) ball.dx *= (-1);
             if((ball.x - ball.radius <= paddle.x + paddle.length) && (ball.x >= paddle.x + paddle.length))
              if(ball.dx<0) ball.dx *= (-1);
           }
     //brick collision
     ptr = brick_start;
     int collision = 0;
     while(ptr!=NULL)
     {
         //Collision Condition
         collision = -111;
         if(ptr->anim != -4)
         {
         if(ball.dy>0)  //Ball is going up
         {
             if(ball.dx>=0)  //Ball is moving right   CASE I
                {
                   //Collie from left or bottom
                   //FOR LEFT
                   if(ball.y >= (ptr->y - ptr->height) && ball.y <= (ptr->y)) 
                      {
                             if((ball.x + ball.radius) >= ptr->x && ball.x - ball.radius <= ptr->x ) //LEFT COLLISION
                                {
                                   Add_Power(ptr);
                                   if(!(ptr->type == 1 && ptr->strength == 1)&& !(ptr->type == 3)) 
                                       ball.dx *= (-1);
                                   collision = -1; //from left
                                }
                      }
                }
             else    //Ball is moving Left   CASE II
                {
                      if(ball.y >= (ptr->y - ptr->height) && ball.y <= (ptr->y)) 
                      {
                             if((ball.x - ball.radius) <= (ptr->x + ptr->width) && (ball.x + ball.radius) >= (ptr->x + ptr->width) ) //RIGHT COLLISION
                                {
                                   Add_Power(ptr);
                                   if(!(ptr->type == 1 && ptr->strength == 1) && !(ptr->type == 3))                                
                                   ball.dx *= (-1);
                                   collision = 1; //from right
                                }
                      }
                }
             //FOR BOTTOM  CASE III
                   if(ball.x >= ptr->x && ball.x <=(ptr->x + ptr->width))
                      {
                            if((ball.y + ball.radius) >= (ptr->y - ptr->height) && (ball.y - ball.radius) <= (ptr->y - ptr->height) ) //BOTTOM COLLISION
                                {
                                   Add_Power(ptr);
                                   if(!(ptr->type == 1 && ptr->strength == 1) && !(ptr->type == 3))
                                   ball.dy *= (-1);
                                   collision = 3;
                                }
                      }
         }
         else  //Ball is going up
         {
             if(ball.dx>=0)  //Ball is moving right   CASE I
                {
                   //Collie from left or bottom
                   //FOR LEFT
                   if(ball.y - ball.radius <= (ptr->y) && (ball.y + ball.radius) >= (ptr->y)) 
                      {
                             if((ball.x + ball.radius) >= ptr->x && (ball.x - ball.radius) <= ptr->x ) //LEFT COLLISION
                                {
                                   Add_Power(ptr);
                                   if(!(ptr->type == 1 && ptr->strength == 1)&& !(ptr->type == 3))
                                   ball.dx *= (-1);
                                   collision = -1;
                                }
                      }
                }
             else    //Ball is moving Left   CASE II
                {
                      if(ball.y - ball.radius <= (ptr->y) && (ball.y + ball.radius)>= (ptr->y)) 
                      {
                             if((ball.x - ball.radius) <= (ptr->x + ptr->width) && (ball.x + ball.radius) >= (ptr->x + ptr->width) ) //RIGHT COLLISION
                                {
                                   Add_Power(ptr);
                                   if(!(ptr->type == 1 && ptr->strength == 1)&& !(ptr->type == 3))
                                   ball.dx *= (-1);
                                   collision = 1;
                                }
                      }
                }
             //FOR TOP  CASE III
                   if(ball.x >= ptr->x && ball.x <=(ptr->x + ptr->width))
                      {
                            if((ball.y - ball.radius) <= (ptr->y) && (ball.y + ball.radius) >= (ptr->y) ) //TOP COLLISION
                                {
                                   Add_Power(ptr);
                                   if(!(ptr->type == 1 && ptr->strength == 1) && !(ptr->type == 3))                                       
                                   ball.dy *= (-1);
                                   collision = 2;
                                }
                      }
         }
         //End of Collision Condition
         if(collision != -111)
           {
               brickHit(ptr->type);
			   update(50 * ptr->strength,ptr->x + (ptr->width/2),ptr->y);
               ptr->anim = collision;
               ptr->frame = 0;
               ptr->strength--;
               if(ptr->strength==0) 
                 {
                   ptr->strength=-1; //-1 for no deletion
                   ptr->anim = -4;  //-4 is for no collision
                   ptr->frame = 3;
                 }
                
           }
         }
         ptr = ptr->next;
     }
     if(tmpx!=ball.dx || tmpy!=ball.dy)
     {
         snd_ball_hit();
     }
}

void cl_sb::Init(int zo,int ma)
{
     width = 300;
     height = game_scrheight;
     x = (game_scrwidth/2) - width;
     y = (game_scrheight/2);
     zone=zo;
     map=ma;
	 s_len = 0;
	 top = -1;
	 timer = 0;
	 b_thumb[0][0].x= x + (width-210.0f);
	 b_thumb[0][0].y = 320;
	 b_thumb[0][0].rx = 0;
	 b_thumb[0][0].cx = 5;
	 b_thumb[0][0].depth = scrnear;
	 b_thumb[0][0].front_tex = thumb;
	 b_thumb[0][0].height = 210.0f / 3.0f;
	 b_thumb[0][0].width = 210.0f / 3.0f;
	 b_thumb[0][0].triger = 0;
	 b_thumb[0][0].owidth = b_thumb[0][0].width;
	 b_thumb[0][0].oheight = b_thumb[0][0].height;
	 b_thumb[0][0].t_height = 1.0f/3.0f;
	 b_thumb[0][0].t_width = 1.0f/3.0f;
	 b_thumb[0][0].t_x = 0.0f;
	 b_thumb[0][0].t_y = 1.0f;
	 b_thumb[0][0].timer = 0;
	 for(int i=0;i<3;i++)
	 {
		 for(int j=0;j<3;j++)
		 {
			 if(i==0 && j==0) continue;
			 b_thumb[i][j] = b_thumb[0][0];
			 b_thumb[i][j].x = b_thumb[0][0].x + j*b_thumb[0][0].width;
			 b_thumb[i][j].y = b_thumb[0][0].y - i*b_thumb[0][0].height;
			 b_thumb[i][j].t_x = j * b_thumb[0][0].t_width;
	         b_thumb[i][j].t_y = 1.0f - (i * b_thumb[0][0].t_height);
		 }
	 }
}

void cl_sb::Plot_SB()
{
     Draw_SB();
	 if(score - oscore > 1000)
	 {
       if(oscore<score-199) oscore+=199;
	   else if (oscore>score+199) oscore += -199;
	   else oscore = score;
     }
     else if(score - oscore > 500)
	 {
       if(oscore<score-39) oscore+=39;
	   else if (oscore>score+39) oscore += -39;
	   else oscore = score;
     }
     else
     {
       if(oscore<score-9) oscore+=9;
	   else if (oscore>score+9) oscore += -9;
	   else oscore = score;
     }
	 Draw_Score();
	 Draw_Score_Instants();
	 if(timer++ % 200 == 0) b_thumb[0][0].triger = 1;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{
	         Draw_Thumb(b_thumb[i][j]);
			 if(b_thumb[i][j].triger == 1)
				 {
					b_thumb[i][j].timer ++;
					if(b_thumb[i][j].timer % 10 == 0)
							 {if(j+1 == 3) 
								 {if(i<2) b_thumb[i+1][0].triger = 1;}
							 else b_thumb[i][j+1].triger = 1;}
					if(b_thumb[i][j].timer % 2 == 0) {
						if(b_thumb[i][j].timer < 20)
						   {
						   b_thumb[i][j].width -= 4;
						   b_thumb[i][j].height -= 4;
					       }
						else
							{
						   b_thumb[i][j].width += 4;
						   b_thumb[i][j].height += 4;
						   }
						if(b_thumb[i][j].height >= b_thumb[i][j].oheight && b_thumb[i][j].width >= b_thumb[i][j].owidth) 
						  {
							  b_thumb[i][j].height = b_thumb[i][j].oheight;
							  b_thumb[i][j].width = b_thumb[i][j].owidth;
							  b_thumb[i][j].timer = 0;
							  b_thumb[i][j].triger = 0;
						  }
						}
			     }
			 else b_thumb[i][j].timer = 0;
		}
}
void cl_sb::Draw_Thumb(st_box_type &box) 
{
	 if(disable_text==1)
     {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     }
     glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, thumb);
        glColor3f(1.0,1.0,1.0);
        glTranslatef(box.x, box.y, box.depth);
        glBegin(GL_QUADS);
		glTexCoord2f(box.t_x, box.t_y);  glVertex2f(-box.width/2, box.height/2);
           glTexCoord2f(box.t_x + box.t_width, box.t_y);  glVertex2f(+box.width/2, box.height/2);
		   glTexCoord2f(box.t_x + box.t_width, box.t_y - box.t_height);  glVertex2f(+box.width/2, -box.height/2);
           glTexCoord2f(box.t_x, box.t_y - box.t_height);  glVertex2f(-box.width/2, -box.height/2);
        glEnd();
     glPopMatrix();
     glDisable(GL_TEXTURE_2D);
     glDisable(GL_BLEND);
}
void cl_sb::Draw_Score_Instants()
{
    int i=0; 
	char str[40];
	if(disable_text==1)
     {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     }
	 for(i=0;i<=top;i++)
	 {
	 sprintf(str,"%d\0",obj_instant[i].score);
     glPushMatrix();
	    GLfloat temp_len;
		temp_len = (GLfloat)strlen(str);
        glColor4fv(obj_instant[i].color);
        PABfont.puttext(str,obj_instant[i].x - ((temp_len*30 - (temp_len - 1)*5)/2),obj_instant[i].y,30,20,5,1);
     glPopMatrix();
	    obj_instant[i].timer++;
		obj_instant[i].y += 2;
		obj_instant[i].color[3] -= 0.0200f;
	 }
     glDisable(GL_TEXTURE_2D);
     glDisable(GL_BLEND);
	 for(i=0;i<=top;i++)
	 {
		 if(obj_instant[i].timer >= 60)
		 {
			 for(int j=i;j<top;j++)
				 obj_instant[j] = obj_instant[j+1];
			 if(top>-1) top--;
		 }
	 }
}
void cl_sb::pass(int sc,GLfloat x, GLfloat y)
{
	if(score+sc >=0) score += sc;
	else score = 0;
	if(top<100) top++;
	obj_instant[top].x = x;
	obj_instant[top].y = y;
	obj_instant[top].score = sc;
	obj_instant[top].timer = 0;
	obj_instant[top].color[0]=(sc < 0)?1.0f:0.0f;
	obj_instant[top].color[1]=(sc >= 0)?1.0f:0.0f;
	obj_instant[top].color[2] = 0.0f;
	obj_instant[top].color[3] = 1.0f;
}

void cl_sb::Draw_Score()
{
	 char str[100];
	 if(disable_text==1)
     {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     }
	 sprintf(str,"Score %d",oscore);
	 if(s_len == 0) s_len = strlen(str);
     glPushMatrix();
      //  glBindTexture(GL_TEXTURE_2D, sb_bg);
        glColor3f(0.0,0.0,0.0);
      //  glTranslatef(550, 100, -1.0);
        PABfont.puttext(str,450,100,25,50,11,1);
	sprintf(str,"Level %d",int_cur_map + 1);
		PABfont.puttext(str,450,20,25,50,8,1);
    sprintf(str,"Zone %d",int_cur_zone + 1);
		PABfont.puttext(str,450,-60,25,50,8,1);
    sprintf(str,"Ball %d",no_of_ball);
		PABfont.puttext(str,450,-140,25,50,8,1);
		glPopMatrix();
     glDisable(GL_TEXTURE_2D);
     glDisable(GL_BLEND);
}

void cl_sb::Draw_SB()
{
     if(disable_text==1)
     {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     }
     glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, sb_bg);
        glColor3f(1.0,1.0,1.0);
        glTranslatef(x, y, scrnear);
        glBegin(GL_QUADS);
           glTexCoord2f(0, 0);  glVertex2f(0, 0);
           glTexCoord2f(1, 0);  glVertex2f(width, 0);
           glTexCoord2f(1, 1);  glVertex2f(width, (-1) * height);
           glTexCoord2f(0, 1);  glVertex2f(0, (-1) * height);
        glEnd();
	glDisable(GL_TEXTURE_2D);
     glPushMatrix();
     glLoadIdentity();
	 glTranslatef(x, 0, scrnear);
	 glColor4f(0.3,0.7,0.3,0.6);
	    glBegin(GL_QUADS);
			  glVertex2f(50, 100);
			  glVertex2f(270, 120);
              glVertex2f(270, -320);
              glVertex2f(45, -300);
        glEnd();
	glPopMatrix();
	 glPopMatrix();
	 glDisable(GL_BLEND);
}

//Documentation For Power
/*
                0 - Nothing
                1 - Expand
                2 - Shrink
                3 - Kill
                4 - Magnet
                5 - Speedy
                6 - Breaker
                7 - Arms
*/
void cl_power::Init()
{
     int i=0, brick_no;
     brick_no = map_zone[int_cur_zone][int_cur_map].No_of_brick;
     Release(Start);
     Start=NULL;
     no_type = 8;
     no_power[1] = 3 ; //Expand
     no_power[2] = 2 ; //Shrink
     no_power[3] = 2 ; //Kill
     no_power[4] = 10; //Magnet
     no_power[5] = 2 ; //Speedy
     no_power[6] = 2 ; //Breaker
     no_power[7] = 2 ; //Arms
     gun_bullet.Init();
}
void cl_power::Load_Power()
{
     int type=0;//, i,flag;
     st_brick_type *ptr;
     ptr=brick_start;
     if(ptr == NULL) return;
     Release(Start);
     while(ptr!=NULL)
        {
            type=rand()%(2*no_type);
            if(type < no_type && type != 0)
               {
                    int j_count=0;
                    for(int j=type; j_count<7; j++,j_count++)
                    {
                    if(j==no_type) j=1;
                    if(no_power[j] > 0)
                     {
                      ptr->power_type = j;
                      no_power[j]--;
                      break;
                     }
                    }
               }
            ptr->release_power = 1;
            ptr = ptr->next;
        }
}
void cl_power::Release(st_power_type *temp)
{
     st_power_type *ptr,*pptr;
     if(temp!=NULL)
       {
         ptr = temp;
         while(ptr!=NULL)
         {
            pptr=ptr;
            ptr=ptr->next;
            pptr->next = power_avail;
            power_avail = pptr;
         }
         temp=NULL;
       }
     Start = NULL;
     power_start = NULL;
}
void cl_power::Draw_Power(st_power_type *temp)
{
     glPushMatrix();
       glColor3f(1.0,1.0,1.0);
       glLoadIdentity();
       glTranslatef(temp->x, temp->y, scrnear);
       glRotatef(temp->rz,0.0 ,0.0, 1.0);
       glBindTexture(GL_TEXTURE_2D, temp->text);
       glBegin (GL_QUADS); 
               glColor3f(1.0,1.0,1.0);
               glTexCoord2f(0,0);               glVertex2f(-(temp->width)/2,-(temp->height)/2);
               glTexCoord2f(0,1);               glVertex2f(-(temp->width)/2,(temp->height)/2);
               glTexCoord2f(1,1);               glVertex2f((temp->width)/2,(temp->height)/2);
               glTexCoord2f(1,0);               glVertex2f((temp->width)/2,-(temp->height)/2);
       glEnd();
       glColor3f(1.0,1.0,1.0);
     glPopMatrix();
}

void cl_power::Plot_Power()
{
     st_power_type *ptr,*pptr;
     if(disable_text==1)
     {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     }
     ptr=Start;
     pptr=NULL;
     while(ptr!=NULL)
     {
        if(ptr->enable == 0)
             {
                if(pptr==NULL)
                   {
                      Start = ptr->next;
                      ptr->next = power_avail;
                      power_avail = ptr;
                      ptr=Start;
                      power_start=Start;
                      continue;
                   }
                else
                   {
                      pptr->next = ptr->next;
                      ptr->next = power_avail;
                      power_avail = ptr;
                      ptr = pptr->next;
                      continue;
                   }
             }
          
        Animate(ptr);
        Detect_Collision(ptr);
        Draw_Power(ptr);
        pptr=ptr;
        ptr=ptr->next;
     }
     glDisable(GL_TEXTURE_2D);
     glDisable(GL_BLEND);
     gun_bullet.Plot_Weapon();
}
void cl_power::Animate(st_power_type *ptr)
{
     ptr->rz += ptr->cz;
     ptr->x += ptr->dx;
     ptr->y += ptr->dy;
     if(ptr->dy > -6) ptr->dy += ptr->ay;
     else if(ptr->dy < -6) ptr->dy = -6;
     if(ptr->height < ptr->oheight) ptr->height += ptr->cheight; 
     else ptr->height = ptr->oheight;
     if(ptr->width < ptr->owidth) ptr->width += ptr->cwidth; 
     else ptr->width = ptr->owidth;
}         
void cl_power::Detect_Collision(st_power_type *temp)
{
     int collision = 0;
     if(temp->enable == 1)
      {
          if(temp->y + (temp->height/2) < border.y2) //Boundry Condition
             temp->enable = 0;
          if(temp->x - (temp->width/2) < border.x1)
             temp->dx = (temp->dx<0)?(-1)*temp->dx:temp->dx;
          if(temp->x + (temp->width/2) > border.x2) 
             temp->dx = (temp->dx>0)?(-1)*temp->dx:temp->dx;
             
             
          //Paddle
          //paddle detect     
          if( temp->x >= paddle.x && temp->x <= (paddle.x + paddle.length))
            if((temp->y - (temp->height/2) <= paddle.y) && (temp->y >= paddle.y) ) 
              {
                  temp->enable = 0;
                  collision = 1;
              }
          if( temp->y - (temp->width/2) <= (paddle.y - paddle.width + 38) && temp->y >= (paddle.y - paddle.width - 38))
           {
             if(((temp->x + (temp->width/2) >= paddle.x && temp->x <= paddle.x)) || ((temp->x - (temp->width/2) <= paddle.x + paddle.length) && (temp->x >= paddle.x + paddle.length)))
              {
                  temp->enable = 0;
                  collision = 1;
              } 
           }
           if(collision==1)
           {
               snd_power();
               switch(temp->type)
                    {
                       case 1:
                          paddle.olength += 80;
						  update(200, temp->x + (temp->width/2), temp->y);
                          break;
                       case 2:
                          paddle.olength -= 60;
                          if(paddle.olength < 150) paddle.olength = 150;
						  update(-125, temp->x + (temp->width/2), temp->y);
                          break;
                       case 3:
                          gun_bullet.enable = 0;
                          gun_bullet.recoily = border.y2;
						  update(-5000, temp->x + (temp->width/2), temp->y);
                          break;   //default
                       case 4:
                          paddle.magnet = 1;
						  update(100, temp->x + (temp->width/2), temp->y);
                          break;
                       case 5:
                          ball.maxspeed += (ball.maxspeed/5);
                          if(ball.maxspeed > (2*ball.radius)) ball.maxspeed = (GLint)(ball.radius-2.0);
                          ball.dy = (ball.dy<0)?(-1)* ball.maxspeed:ball.maxspeed;
                          if(ball.dx < 0) ball.dx -= ball.dx/3;
                          else if(ball.dx > 0) ball.dx += ball.dx/3;
						  update(150, temp->x + (temp->width/2), temp->y);
                          break;
                       case 6:
                          ball.maxspeed -= (ball.maxspeed/3);
                          if(ball.maxspeed < 8) ball.maxspeed = 8;
                          ball.dy = (ball.dy<0)?(-1)* ball.maxspeed:ball.maxspeed;
                          if(ball.dx < 0) ball.dx -= ball.dx/3;
                          else if(ball.dx > 0) ball.dx += ball.dx/3;
						  update(-150, temp->x + (temp->width/2), temp->y);
                          break;
                       case 7:
                          if(gun_bullet.enable!=1)
                          {
                             gun_bullet.enable = 1;
                             gun_bullet.recoily = border.y2 + 96;
                          }
			
                          break;
                          
                    }
           }
          
      }
}

void cl_weapon::Init() 
{
     st_bullet_type *ptr,*pptr;
     width = 36;
     height = 96;
     x = paddle.x + paddle.length + (width/2);
     y = border.y2;
     enable = 0;
     enable_fire = 0;
     recoily = border.y2;
     ptr = Start;
     while(ptr!=NULL)
     {
        pptr = ptr;
        ptr = ptr->next;
        pptr->next = bullet_avail;
        bullet_avail = pptr;
     }
     Start = NULL;
}
void cl_weapon::Init_Bullet(st_bullet_type *temp) 
{
     temp->x=0;
     temp->y=0;
     temp->dy=20;
     temp->width=14;
     temp->height=92;
     temp->explode=0;
     temp->text=bu[0];
     temp->frame=0;
     temp->next=NULL;
}
void cl_weapon::Draw_Bullet(st_bullet_type *temp) 
{
     if(disable_text==1)
     {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     }
     glPushMatrix();
           glLoadIdentity();
           glTranslatef(temp->x, temp->y, scrnear);
           glBindTexture(GL_TEXTURE_2D, temp->text);
           glColor3f(1.0, 1.0, 1.0);
           glBegin (GL_QUADS);
               glTexCoord2i(0,1); glVertex2f(0,0);
               glTexCoord2i(0,0); glVertex2f(0, -temp->height);
               glTexCoord2i(1,0); glVertex2f(temp->width, -temp->height);
               glTexCoord2i(1,1); glVertex2f(temp->width,0);
           glEnd();
           glColor3f(1.0, 1.0, 1.0);
       glPopMatrix();
       glDisable(GL_TEXTURE_2D);
       glDisable(GL_BLEND);
}
void cl_weapon::Draw_Weapon() 
{
     if(disable_text==1)
     {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     }
     glPushMatrix();
           glLoadIdentity();
           glTranslatef(x, y, scrnear);
           glBindTexture(GL_TEXTURE_2D, wp);
           glColor3f(1.0, 1.0, 1.0);
           glBegin (GL_QUADS);
               glTexCoord2i(0,1); glVertex2f(0,0);
               glTexCoord2i(0,0); glVertex2f(0, -height);
               glTexCoord2i(1,0); glVertex2f(width, -height);
               glTexCoord2i(1,1); glVertex2f(width,0);
           glEnd();
           glColor3f(1.0, 1.0, 1.0);
       glPopMatrix();
       glDisable(GL_TEXTURE_2D);
       glDisable(GL_BLEND);
}
void cl_weapon::Plot_Bullet() 
{
     st_bullet_type *ptr,*pptr;
     if(disable_text==1)
     {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     }
     ptr=Start;
     pptr=NULL;
     while(ptr!=NULL)
     {
         if(ptr->explode == 1)
            {
                if(pptr==NULL)
                   {
                      Start = ptr->next;
                      ptr->next = bullet_avail;
                      bullet_avail = ptr;
                      ptr=Start;
                      continue;
                   }
                else
                   {
                      pptr->next = ptr->next;
                      ptr->next = bullet_avail;
                      bullet_avail = ptr;
                      ptr = pptr->next;
                      continue;
                   }
            }
        Animate_Bullet(ptr);
        Detect_Collision(ptr);
        Draw_Bullet(ptr);
        pptr=ptr;
        ptr=ptr->next;
     }
     glDisable(GL_TEXTURE_2D);
     glDisable(GL_BLEND);
}
void cl_weapon::Plot_Weapon() 
{
     x = paddle.x + (paddle.length/2) - (width/2) - 2;
     if(Mouse.Button == 0 && enable == 1 && enable_fire == 1)
        {
         y = y - 35;
         delay=15;
              ball.stick=0;
              st_bullet_type *n_bullet,*ppt;
              if(bullet_avail!=NULL)
              { 
              n_bullet = bullet_avail;
              bullet_avail = bullet_avail->next;
              Init_Bullet(n_bullet);
              snd_fire_bullet();
              n_bullet->x = x + 12;
              n_bullet->y = y + 50;
              if (Start == NULL)
                   Start = n_bullet;
                else
                   {
                      ppt = Start;
                      while(ppt->next != NULL)
                         ppt = ppt->next;
                      ppt->next = n_bullet;
                   }
              }
         enable_fire = 0;
        }
     Plot_Bullet();
     Animate_Weapon();
     Draw_Weapon();
}
void cl_weapon::Animate_Weapon() 
{
     if(delay!=0) delay--;
     if(y != recoily) y+=(y>recoily)?-4:4;
     if(y > recoily-10 && y < recoily + 10) 
       {
        y = recoily;
        if(delay==0) enable_fire = 1;
       }
}
void cl_weapon::Animate_Bullet(st_bullet_type *temp) 
{
     temp->frame++;
     if(temp->frame == 3)
       temp->frame = 0;
     temp->text = bu[temp->frame];
     temp->y += temp->dy;
}
void cl_weapon::Detect_Collision(st_bullet_type *temp) 
{
     st_brick_type *ptr;
     ptr = brick_start;
     while(ptr!=NULL)
     {
             if(ptr->anim!=-4 && temp->explode!=1)
              {
                   if((temp->x + temp->width) >= ptr->x && temp->x <=(ptr->x + ptr->width))
                      {
                            if(temp->y >= (ptr->y - ptr->height) && temp->y - temp->height <= (ptr->y - ptr->height) ) //BOTTOM COLLISION
                                {
                                   Add_Power(ptr);
								   update(100, temp->x + (temp->width/2), temp->y);
                                   temp->explode = 1;
                                   snd_fire_bullethit();
                                   ptr->strength=-1; //-1 for no deletion
                                   ptr->anim = -4;  //-4 is for no collision
                                   ptr->frame = 3;
                                   brickHit(ptr->type);
                                   //Bot Fall
                                   if(ptr->bot != NULL)
                                   {
                                                   st_bot_type *btemp;
                                                   btemp = ptr->bot;
                                                   if(btemp->fall != 1)
                                                   {
                                                   btemp->trackno = snd_alien_scream();
                                                   btemp->brick = NULL;
                                                   ptr->bot = NULL;
                                                   btemp->dx = ball.dx / 3;
                                                   btemp->dy = 0;
                                                   btemp->cz = ball.cz / 4;
                                                   btemp->anim = 7;
                                                   btemp->bot_frame = 0;
                                                   btemp->fall = 1;
                                                   }
                                   }
                                   //End of Bot Fall
                                }
                      }
              }                      
       ptr = ptr->next;
     }
     //Bot And Bullet Collision
     st_bot_type *bptr;
     bptr = bot_start;
     while(bptr!=NULL)
     {
             if(bptr->fall == 1 && bptr->dead != 1)
              {
                   if((temp->x + temp->width) >= (bptr->x-(bptr->owidth/2)) && temp->x <=(bptr->x + (bptr->owidth/2)))
                      {
                            if(temp->y >= (bptr->y - (bptr->oheight/2)) && temp->y - temp->height <= (bptr->y + (bptr->oheight/2)) ) //BOTTOM COLLISION
                                {
                                   temp->explode = 1;
                                   snd_fire_bullethit();
                                   bptr->dead = 1;
								   update(300, temp->x + (temp->width/2), temp->y);
                                }
                      }
              }                      
       bptr = bptr->next;
     }
     //Bullet Limits
     if(temp->y - temp->height > border.y1) temp->explode = 1;
}


void cl_bot::Init()
{
     Release_Bomb();
     Release();
     //Frames For Zone 1 Bot
     timer = 0;
     frequency = 600 + rand()%1200;
}
void cl_bot::Init_Bot(st_bot_type *temp)
{
     temp->x = 0;
     temp->y = 0;
     temp->rz = 0;
     temp->cz = 0;
     temp->dx = 0;
     temp->dy = 0;
     temp->strength = 6;
     temp->width = 25;
     temp->owidth = 50;
     temp->height = 40;
     temp->oheight = 40;
     temp->anim = 0;
     temp->bot_frame = 0;
     temp->bomb = 0;
     temp->fall = 0;
     temp->dead = 0;
     temp->timer = 0;
     temp->change_anim_frequency = 350 + (rand() % 400);
     temp->brick = NULL;
     temp->next = NULL;
     temp->text = bot[int_cur_zone][1][0];
     temp->color[0] = 1.0;
     temp->color[1] = 1.0;
     temp->color[2] = 1.0;
     temp->trackno=-1; 
      
}
void cl_bot::Init_Bomb(st_bomb_type *temp)
{
     temp->x = 0;
     temp->y = 0;
     temp->dy = 5;
     temp->dx = 0;
     temp->rz = 0;
     temp->cz = 10;
     temp->height = 45;
     temp->width = 45;
     temp->next = NULL;
     temp->bomb_frame = 0;
     temp->explode = 0;
     temp->text = bomb[int_cur_zone][0];
}
void cl_bot::Release()
{
     st_bot_type *ptr,*pptr;
     if(Start!=NULL)
       {
         ptr = Start;
         while(ptr!=NULL)
         {
            pptr=ptr;
            ptr=ptr->next;
            pptr->next = bot_avail;
            bot_avail = pptr;
         }
         Start=NULL;
       }
     Start = NULL;
     bot_start = NULL;
}
void cl_bot::Release_Bomb()
{
     st_bomb_type *ptr,*pptr;
     if(Start_Bomb!=NULL)
       {
         ptr = Start_Bomb;
         while(ptr!=NULL)
         {
            pptr=ptr;
            ptr=ptr->next;
            pptr->next = bomb_avail;
            bomb_avail = pptr;
         }
       }
       Start_Bomb=NULL;
}
void cl_bot::Draw_Bot(st_bot_type *temp)
{
       glPushMatrix();
       glColor3fv(temp->color);
       glLoadIdentity();
       glTranslatef(temp->x, temp->y, scrnear);
       glRotatef(temp->rz,0.0 ,0.0, 1.0);
       glBindTexture(GL_TEXTURE_2D, temp->text);
       glBegin (GL_QUADS); 
               glTexCoord2f(0,0);               glVertex2f(-(temp->owidth)/2,-(temp->oheight)/2);
               glTexCoord2f(0,1);               glVertex2f(-(temp->owidth)/2,(temp->oheight)/2);
               glTexCoord2f(1,1);               glVertex2f((temp->owidth)/2,(temp->oheight)/2);
               glTexCoord2f(1,0);               glVertex2f((temp->owidth)/2,-(temp->oheight)/2);
       glEnd();
       glColor3f(1.0,1.0,1.0);
     glPopMatrix();

}
void cl_bot::Draw_Bomb(st_bomb_type *temp)
{
       glPushMatrix();
       glColor3f(1.0, 1.0, 1.0);
       glLoadIdentity();
       glTranslatef(temp->x, temp->y, scrnear);
       glRotatef(temp->rz,0.0 ,0.0, 1.0);
       glBindTexture(GL_TEXTURE_2D, temp->text);
       glBegin (GL_QUADS); 
               glColor3f(1.0,1.0,1.0);
               glTexCoord2f(0,0);               glVertex2f(-(temp->width)/2,-(temp->height)/2);
               glTexCoord2f(0,1);               glVertex2f(-(temp->width)/2,(temp->height)/2);
               glTexCoord2f(1,1);               glVertex2f((temp->width)/2,(temp->height)/2);
               glTexCoord2f(1,0);               glVertex2f((temp->width)/2,-(temp->height)/2);
       glEnd();
       glColor3f(1.0,1.0,1.0);
     glPopMatrix();
}
void cl_bot::Plot_Bot()
{
     st_bot_type *ptr,*pptr;
     if(disable_text==1)
     {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     }
     ptr=Start;
     pptr=NULL;
     while(ptr!=NULL)
     {
        if(ptr->dead == 1)
             {
                snd_alien_scream(ptr->trackno);
                if(pptr==NULL)
                   {
                      Start = ptr->next;
                      ptr->next = bot_avail;
                      bot_avail = ptr;
                      ptr=Start;
                      bot_start=Start;
                      continue;
                   }
                else
                   {
                      pptr->next = ptr->next;
                      ptr->next = bot_avail;
                      bot_avail = ptr;
                      ptr = pptr->next;
                      continue;
                   }
             }
        Animate(ptr);
        Detect_Collision(ptr);
        Draw_Bot(ptr);
        pptr=ptr;
        ptr=ptr->next;
     }
     glDisable(GL_TEXTURE_2D);
     glDisable(GL_BLEND);
     Plot_Bomb();
     //Bot Timer
     timer++;
     if(timer%frequency == 0)
     {
         Add_Bot();
         frequency = (frequency<600)?600:frequency-100;
     }
}
void cl_bot::Plot_Bomb()
{
     st_bomb_type *ptr,*pptr;
     if(disable_text==1)
     {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     }
     ptr=Start_Bomb;
     pptr=NULL;
     while(ptr!=NULL)
     {
         if(ptr->explode == 1)
            {
                if(pptr==NULL)
                   {
                      Start_Bomb = ptr->next;
                      ptr->next = bomb_avail;
                      bomb_avail = ptr;
                      ptr=Start_Bomb;
                      continue;
                   }
                else
                   {
                      pptr->next = ptr->next;
                      ptr->next = bomb_avail;
                      bomb_avail = ptr;
                      
                      ptr = pptr->next;
                      continue;
                   }
            }
        Animate_Bomb(ptr);
        Detect_Collision_Bomb(ptr);
        Draw_Bomb(ptr);
        pptr=ptr;
        ptr=ptr->next;
     }
     glDisable(GL_TEXTURE_2D);
     glDisable(GL_BLEND);
}
void cl_bot::Animate(st_bot_type *temp)
{
     temp->timer++;
     switch(temp->anim)
     {
         case 0:
              if(int_cur_zone == 0)
               {
                  if(temp->bot_frame<4) 
                     {if(temp->timer%20 == 0) temp->bot_frame++;}
                  else if(temp->timer%6==0)temp->bot_frame++;
               }
              temp->text = bot[int_cur_zone][0][temp->bot_frame];
              if(temp->bot_frame == 7)
                 {
                   temp->anim = 1;
                   snd_alien_hello();
                   temp->bot_frame = 0;
                 }
         break;
         case 1:
                   if(paddle.x + paddle.length< temp->x)
                     {
                     if(paddle.x + (2*paddle.length)< temp->x)
                          temp->bot_frame=2;
                     else
                          temp->bot_frame=1;
                     }       
                   else if(paddle.x > temp->x + temp->width)
                     {
                      if(paddle.x - paddle.length> temp->x + temp->width)
                          temp->bot_frame=4;
                      else
                          temp->bot_frame=3;
                     }
                   else
                     temp->bot_frame = 0;
              temp->text = bot[int_cur_zone][1][temp->bot_frame];
              if(temp->timer % temp->change_anim_frequency == 0)
                  {
                     switch(rand()%4)
                     {
                        case 0:
                             temp->anim = 1;
                        break;
                        case 1:
                             temp->anim = 2;
                        break;
                        case 2:
                             temp->anim = 4;
                        break;
                        case 3:
                             temp->anim = 5;
                             temp->bomb = 1;
                        break;
                     }
                    temp->bot_frame = 0;
                  }
         break;
         case 2:
              if(int_cur_zone == 0)
               { 
                     if(temp->timer%15 == 0) temp->bot_frame++;
               }
              temp->text = bot[int_cur_zone][2][temp->bot_frame];
              if(temp->bot_frame == 7)
                 {
                   temp->anim = 2;
                   temp->bot_frame = 3;
                 }
              if(!(temp->timer % temp->change_anim_frequency < 300))
                 {
                   temp->anim = 1;
                   temp->bot_frame = 0;
                 }
         break;
         case 4:
              if(int_cur_zone == 0)
               { 
                     if(temp->timer%30 == 0) temp->bot_frame++;
               }
              temp->text = bot[int_cur_zone][4][temp->bot_frame];
              if(temp->bot_frame == 7)
                 {
                   temp->anim = 4;
                   temp->bot_frame = 0;
                 }
              if(!(temp->timer % temp->change_anim_frequency < 300))
                 {
                   temp->anim = 1;
                   temp->bot_frame = 0;
                 }
         break;
         case 5:
                   if(paddle.x + paddle.length< temp->x)
                     {
                     if(paddle.x + (2*paddle.length)< temp->x)
                          temp->bot_frame=2;
                     else
                          temp->bot_frame=1;
                     }       
                   else if(paddle.x > temp->x + temp->width)
                     {
                      if(paddle.x - paddle.length> temp->x + temp->width)
                          temp->bot_frame=4;
                      else
                          temp->bot_frame=3;
                     }
                   else
                       temp->bot_frame = 0;
                   temp->text = bot[int_cur_zone][5][temp->bot_frame];
              if(temp->timer % (60 + (rand()%200)) == 0)
                  {
                     temp->anim = 1;
                     temp->text = bot[int_cur_zone][1][0];
                     temp->bomb = 0;
                     if(bomb_avail!=NULL)
                     {
                       snd_alien_firo();
                       //Add_Bomb();
                       st_bomb_type *n_bomb,*ppt;
                       n_bomb = bomb_avail;
                       bomb_avail = bomb_avail->next;
                       Init_Bomb(n_bomb);
                       n_bomb->x = temp->x;
                       n_bomb->y = temp->y - 10;
                       switch(temp->bot_frame)
                       {
                          case 1:
                          case 3:
                           n_bomb->dx = (GLfloat)(temp->bot_frame - 2) * 5;
                           break;
                          case 2:
                          case 4:
                           n_bomb->dx = (GLfloat)(temp->bot_frame - 3) * 5;
                           break;
                       }
                       if (Start_Bomb == NULL)
                         Start_Bomb = n_bomb;
                       else
                       {
                        ppt = Start_Bomb;
                        while(ppt->next != NULL)
                        ppt = ppt->next;
                        ppt->next = n_bomb;
                       }
                     }
                  }
         break;
         case 7:
              if(temp->strength == 0) temp->dead = 1;
              temp->y += temp->dy;
              temp->x += temp->dx;
              if(temp->cz < 0)
                  temp->rz += ((temp->dy<0)?temp->dy:((-1)*temp->dy));
              else
                  temp->rz += ((temp->dy<0)?((-1)*temp->dy):temp->dy);
              temp->rz += (temp->cz < 0)?-1:1;
              if(timer % 10 == 0) temp->dy= temp->dy-3;
              if(timer % 30 == 0 && temp->dx != 0) {if(temp->dx<0)temp->dx++; else temp->dx--;}
              if(timer % 4 == 0) 
                 {
                    temp->text = bot[int_cur_zone][7][temp->bot_frame];
                    temp->bot_frame++;
                    if(temp->bot_frame == 4) temp->bot_frame = 0;
                 }
         break;
     }
}
void cl_bot::Animate_Bomb(st_bomb_type *temp)
{
     temp->rz += temp->cz;
     temp->x += temp->dx;
     if(timer % 20 == 0 && temp->dx != 0) {if(temp->dx<0)temp->dx++; else temp->dx--;}
     temp->y -= temp->dy;
     temp->text = bomb[int_cur_zone][1];
}
void cl_bot::Add_Bot()
{
     int id=0,count=0;
     st_brick_type *ptr;
     st_bot_type *n_bot;
     ptr = brick_start;
     if(ptr==NULL) return;
     while(ptr!=NULL)
     {
           count++;
           ptr = ptr->next;
     }  
     id = rand() % count;
     count=0;
     ptr = brick_start;
     while((count++)<id)
     {
        if(ptr!=NULL) 
        ptr = ptr->next;
     }  
     count = id + 1;
     while(count!=id)
     {
         if(ptr== NULL)
            {ptr=brick_start; count=0;}
         if(ptr->u1 == NULL && ptr->u2 == NULL && ptr->bot == NULL && (ptr->anim != -4))
             {
               if(bot_avail!=NULL)
               {
                 n_bot = bot_avail;
                 bot_avail = bot_avail->next;
                 Init_Bot(n_bot);
                 n_bot->x = ptr->x + n_bot->owidth/2;
                 n_bot->y = ptr->y + n_bot->oheight/2;
                 n_bot->text = bot[0][0][0];
                 n_bot->brick = ptr;
                 switch(rand()%4)
                 {
                     case 0://Red
                          n_bot->color[0]=1.0f;
                          n_bot->color[1]=0.5f;
                          n_bot->color[2]=0.5f;
                          break;
                     case 1://Yellow
                          n_bot->color[0]=0.5f;
                          n_bot->color[1]=0.7f;
                          n_bot->color[2]=1.0f;
                          break;
                     case 2://Green
                          n_bot->color[0]=0.5f;
                          n_bot->color[1]=1.0f;
                          n_bot->color[2]=0.5f;
                          break;
                     case 3://White
                          n_bot->color[0]=1.0f;
                          n_bot->color[1]=1.0f;
                          n_bot->color[2]=1.0f;
                          break;
                          break;
                 }
                 ptr->bot = n_bot;
                 if(Start == NULL)
                    {
                      Start = n_bot;
                      bot_start = n_bot;
                    }
                 else
                    {
                      st_bot_type *temp;
                      temp = bot_start;
                      while(temp->next!=NULL)
                         temp = temp->next;
                      temp->next = n_bot;
                    }
                 }
               break;
             }         
         ptr = ptr->next;
         count++;
    if(ptr == NULL) {ptr=brick_start;if(count==id) break;count=0;}        
     }
}
void cl_bot::Detect_Collision(st_bot_type *temp)
{
     //Ball can hit the Bot from 3 direction
     //While Going up direction. it can hit it from left or right only
     //while going down. it can hit it from top, left or right
     int collide = -111;
     st_brick_type *tptr=temp->brick;
     //Case Left
     if(temp->fall != 1)
     {
     if(((ball.x + ball.radius) > (temp->x - (temp->width/2))) && (ball.x - ball.radius) < (temp->x - (temp->width/2)))
     {
       if((ball.y - ball.radius) < (temp->y + (temp->height/2)) && (ball.y + ball.radius) > (temp->y - (temp->height/2)))
       {
          temp->fall = 1;
          collide = 1;
       }        
     }
     //Case Right
     if(((ball.x + ball.radius) > (temp->x + (temp->width/2))) && (ball.x - ball.radius) < (temp->x + (temp->width/2)))
     {
       if((ball.y - ball.radius) < (temp->y + (temp->height/2)) && (ball.y + ball.radius) > (temp->y - (temp->height/2)))
       {
          temp->fall = 1;
          collide = 1;
       }        
     }
     //Case Top
     if((ball.y - ball.radius < (temp->y + (temp->height/2)))&&(ball.y + ball.radius > (temp->y + (temp->height/2))))
     {
       if((ball.x + ball.radius > (temp->x - (temp->width/2)))&&(ball.x - ball.radius < (temp->x + (temp->width/2))))
       {
          temp->fall = 1;
          collide = 1;
       }
     }
     }
     else
     {
     //Case Paddle Collision
     if(temp->dy<0)
     {
     if((temp->x + (temp->width/2) >= paddle.x) && (temp->x - (temp->width/2) <= (paddle.x + paddle.length)))
         {
             if((temp->y - (temp->height/2) <= paddle.y) && (temp->y + (temp->height/2) >= (paddle.y - paddle.width)))
               {
                   snd_alien_bump();
                   temp->dy *= (-1);
                   temp->dy -= 2;
                   temp->strength--;
                   temp->cz *= (-1);
                   temp->dx = ((float)(6) * (float)((float)(temp->x - paddle.x)/(float)paddle.length)) - 3;
				   update(70*(6-temp->strength), temp->x + (temp->width/2), temp->y);
               }
         }
     }
     //
     if((temp->x - (temp->owidth/2)) < border.x1) temp->dx *= ((temp->dx<0)?(-1):1);
     if((temp->x + (temp->owidth/2)) > border.x2) temp->dx *= ((temp->dx>0)?(-1):1);
  if(temp->y - (temp->height/2) < border.y2 ) temp->dead = 1;     
     }
	//Brick Shakes
	 if(tptr!=NULL) if(tptr->anim!=0) {temp->fall = 1; collide = 1;  temp->trackno = snd_alien_scream();}
     //Case Holding Bomb
     if(collide != -111)
	 {
                if(tptr!=NULL) tptr->bot = NULL;
                temp->brick = NULL;
                temp->dx = ball.dx / 3;
                temp->dy = 0;
                temp->cz = ball.cz / 4;
                temp->anim = 7;
                temp->bot_frame = 0;
                temp->trackno = snd_alien_scream();
     }
}
void cl_bot::Detect_Collision_Bomb(st_bomb_type *temp)
{
     if((temp->x + (temp->width/2) >= paddle.x) && (temp->x - (temp->width/2) <= (paddle.x + paddle.length)))
         {
             if((temp->y - (temp->height/2) <= paddle.y) && (temp->y + (temp->height/2) >= (paddle.y - paddle.width)))
               {
                   temp->explode = 1;
				   update(-1000, temp->x + (temp->width/2), temp->y);
				   snd_bot_bomb();
				   snd_alien_response();
               }
         }
     if(temp->y + (temp->height/2) < border.y2 ) temp->explode = 1;
}
#endif
