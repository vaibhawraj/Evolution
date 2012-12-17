//PABfont.cpp
//Code Added On Nov 5, 2012
#ifndef PABfont_CPP
#define PABfont_CPP

//Font Handling




class cl_PABfont
{
	private:
		GLuint tex;
		GLfloat width;
		GLfloat height;
	public:
		void puttext(const char *str, GLfloat x, GLfloat y,GLfloat twidth, GLfloat theight,GLfloat);   //2d Positioning with fixed width
		void puttext(const char *str, GLfloat x, GLfloat y,GLfloat z,GLfloat twidth, GLfloat theight,GLfloat,int);  //3d Positioning with fixed width
		void drawtext(const char *str, GLfloat twidth, GLfloat theight,GLfloat);
        void puttext(const char *str, GLfloat x, GLfloat y,GLfloat twidth, GLfloat theight,GLfloat,GLfloat); //2d Positioning with fixed spacing
        void puttext(const char *str, GLfloat x, GLfloat y, GLfloat z,GLfloat twidth, GLfloat theight,GLfloat,GLfloat,int); //3d Positioning with fixed spacing
		void drawtext(const char *str, GLfloat twidth, GLfloat theight,GLfloat,GLfloat);
		cl_PABfont()
		{
			width = 30.0f/2190.0f;
			height = 40.0f;
		}
}PABfont;
void cl_PABfont::puttext(const char *str,GLfloat x, GLfloat y, GLfloat twidth, GLfloat theight, GLfloat spacing)
{
	glPushMatrix();
 	   glLoadIdentity();
	   glTranslatef(x, y, scrnear);
	   drawtext(str, twidth, theight, spacing);
	glPopMatrix();
}
void cl_PABfont::puttext(const char *str,GLfloat x, GLfloat y, GLfloat z,GLfloat twidth, GLfloat theight, GLfloat spacing,int s)
{
	glPushMatrix();
 	   glLoadIdentity();
	   glTranslatef(x, y, scrnear + z);
	   drawtext(str, twidth, theight, spacing);
	glPopMatrix();
}
void cl_PABfont::drawtext(const char *str, GLfloat twidth, GLfloat theight,GLfloat spacing) 
{
	GLfloat x_pos=0, y_pos=0,tx_pos=0,char_width,char_height;
	int len,i,shift;
	len = strlen(str);
	if(len==0) return;
	char_width = twidth/(GLfloat)len;
	char_height = theight;
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, PABfontface);
	for(i=0;i<len;i++)
	{
	   shift = 0;
	   shift = (int)str[i] - 48;
	   if((int)str[i]>=65) shift--;
	   if((int)str[i]>(int)'Z') shift--;
	   if((int)str[i]==(int)'-') shift=12;
	   tx_pos = (GLfloat)((shift*31) - ((shift/5) + 1))/2250.0f;
	   if((int)str[i]!=32)
	   {
       glBegin (GL_QUADS); 
               glTexCoord2f(tx_pos,1);					glVertex2f(x_pos,0);
               glTexCoord2f(tx_pos+width,1);			glVertex2f(x_pos + char_width,0);
               glTexCoord2f(tx_pos+width,0);			glVertex2f(x_pos + char_width,-char_height);
               glTexCoord2f(tx_pos,0);				    glVertex2f(x_pos,-char_height);
       glEnd();
	   }
	   x_pos += (char_width - spacing);
	}
	glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    
}

void cl_PABfont::puttext(const char *str,GLfloat x, GLfloat y, GLfloat twidth, GLfloat theight, GLfloat spacing,GLfloat f_len)
{
	glPushMatrix();
 	   glLoadIdentity();
	   glTranslatef(x, y, scrnear);
	   drawtext(str, twidth, theight, spacing, f_len);
	glPopMatrix();
}
void cl_PABfont::puttext(const char *str,GLfloat x, GLfloat y, GLfloat z,GLfloat twidth, GLfloat theight, GLfloat spacing,GLfloat f_len,int s)
{
	glPushMatrix();
 	   glLoadIdentity();
	   glTranslatef(x, y, scrnear + z);
	   drawtext(str, twidth, theight, spacing, f_len);
	glPopMatrix();
}
void cl_PABfont::drawtext(const char *str, GLfloat twidth, GLfloat theight,GLfloat spacing, GLfloat f_len) 
{
	GLfloat x_pos=0, y_pos=0,tx_pos=0,char_width,char_height;
	int len,i,shift;
	len = strlen(str);
	if(len==0) return;
	char_width = twidth;
	char_height = theight;
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, PABfontface);
	for(i=0;i<len;i++)
	{
	   shift = 0;
	   shift = (int)str[i] - 48;
	   if((int)str[i]>=65) shift--;
	   if((int)str[i]>(int)'Z') shift--;
	   if((int)str[i]==(int)'-') shift=12;
	   tx_pos = (GLfloat)((shift*31) - ((shift/5) + 1))/2250.0f;
	   if((int)str[i]!=32)
	   {
       glBegin (GL_QUADS); 
               glTexCoord2f(tx_pos,1);					glVertex2f(x_pos,0);
               glTexCoord2f(tx_pos+width,1);			glVertex2f(x_pos + char_width,0);
               glTexCoord2f(tx_pos+width,0);			glVertex2f(x_pos + char_width,-char_height);
               glTexCoord2f(tx_pos,0);				    glVertex2f(x_pos,-char_height);
       glEnd();
	   }
	   x_pos += (char_width - spacing);
	}
	glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);    
}

#endif
