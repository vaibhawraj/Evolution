//Level Editor
#include<stdio.h>
#include<conio.h>
#include<strings.h>
struct lvl_header
{
       int nob;
       char col;
       char row;
       char width;
       char height;
       char map[700];  //20 * 50
};
int main()
{
    char fname[20];
    char outfname[20];
    char ch;
    struct lvl_header st_l;
    int i=0;
    FILE *fp;
    printf("Enter File Name :: ");
    scanf("%s",fname);
    sprintf(outfname,"%s.txt",fname);
    if((fp=fopen(outfname,"r"))==NULL)
       {
          printf("\nFile Doesn't Exists. Terminating");
          getch();
          return 1;
       }
    while((ch=getc(fp))!=EOF)
       st_l.map[i++]=ch;
    if(i>500) {printf("Text is out of space. Max Limit is 500.");getch();return 0;}
    i=0;
    while(st_l.map[i++]!='\n');
    st_l.col = i;
    st_l.row = 0;
    st_l.nob = 0;
    st_l.width = 50;
    st_l.height = 20;
    i=0;
    while(st_l.map[i++]!='\0') {if(st_l.map[i]=='\n') st_l.row++;}
    for(i=0;st_l.map[i]!='\0';i++)
       if(st_l.map[i]!='\n' && st_l.map[i]!=' ') st_l.nob++;
    fclose(fp);
    if(st_l.col>22) {printf("\nCol Limit is 22.");getch();return 0;} 
     if(st_l.row>17) {printf("\nCol Limit is 17.");getch();return 0;}    
    sprintf(outfname,"%s.lvl\0",fname);
    fp=fopen(outfname,"wb");
    fwrite(&st_l,sizeof(st_l),1,fp);
    fclose(fp);
    printf("\nDone");
    printf("\nCol : %d",st_l.col);
    printf("\nRow : %d",st_l.row);
    getch();
}
