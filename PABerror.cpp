//PABerror.cpp
//Code Added On Sept 28, 2012

#ifndef PABerror_CPP
#define PABerror_CPP

void Error_Code(int eCode,char str[])
{
     char eMsg[200];
     switch(eCode)
     {
        case 1101:
             DestroyWindow (hWnd);
             sprintf(eMsg,"1101: Unable To Load Texture \"%s\". Terminating",str);
             MessageBox(NULL, eMsg, NULL, MB_OK);
             Shutdown();
             break;
        case 1102:
             DestroyWindow (hWnd);
             sprintf(eMsg,"1102: Insufficient Memory Space");
             MessageBox(NULL, eMsg, NULL, MB_OK);
             Shutdown();
             break;
     }
}

int send_report(char str[],char fname[])
{
    FILE *fp;
    fp=fopen(fname,"a");
    if(fp==NULL) return -1;
    fprintf(fp,"%s",str);
    fclose(fp);
    return 1;
}
#endif
