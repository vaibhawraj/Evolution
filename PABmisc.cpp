//PABmisc.cpp
//Code Added On Oct 25, 2012
//Code Added On Dec 11, 2012
#ifndef PABmisc_CPP
#define PABmisc_CPP

void join_array()
{
     int i=0;
     for(i=0;i<(500-1);i++)
            ms_brick[i].next = &ms_brick[i+1];
     ms_brick[499].next = NULL;
     for(i=0;i<(5-1);i++)
            ms_bullet[i].next = &ms_bullet[i+1];
     ms_bullet[4].next = NULL;
     for(i=0;i<(20-1);i++)
            ms_bomb[i].next = &ms_bomb[i+1];
     ms_bomb[20-1].next = NULL;
     for(i=0;i<(200-1);i++)
            ms_bot[i].next = &ms_bot[i+1];
     ms_bot[200-1].next = NULL;
     for(i=0;i<(100-1);i++)
            ms_power[i].next = &ms_power[i+1];
     ms_power[100-1].next = NULL;
}


#endif
