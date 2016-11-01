#include "watchPuppy.h"

watchPuppy::watchPuppy()
{
  timer=clock();      
}
    
void watchPuppy::feed_watchPuppy(void)
{
    timer=clock();
}

bool watchPuppy::watchPuppyAlert()
{
    return ((clock()-timer)/CLOCKS_PER_SEC)>MAX_TIME;
}

