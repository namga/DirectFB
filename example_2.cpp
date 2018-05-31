#include <stdio.h>
#include <directfb/directfb.h>

static IDirectFB                *dfb = NULL;
static IDirectFBDisplayLayer    *layer = NULL;
static IDirectFBSurface            *surface = NULL;
static IDirectFBEventBuffer        *events = NULL;

static int screen_width = 0;
static int screen_height = 0;

int main(int argc, char *argv[])
{
    int pitch;
    int i,j;
    int quit = 0;
    int x = 0, y = 0, old_x = 0, old_y = 0;

    DirectFBInit(&argc, &argv);
    DirectFBCreate(&dfb);

    dfb->GetDisplayLayer(dfb, DLID_PRIMARY, &layer);
    dfb->CreateInputEventBuffer(dfb, DICAPS_ALL, DFB_TRUE, &events);
    layer->SetCooperativeLevel(layer, DLSCL_EXCLUSIVE);
    layer->GetSurface(layer, &surface);

    surface->GetSize(surface, &screen_width, &screen_height);

    surface->SetColor(surface, 255, 0, 0 , 0xff);
    surface->FillRectangle(surface, 0, 0, screen_width, screen_height);

    while(!quit)
    {
        DFBEvent    evt;
        events->WaitForEvent(events);    //  response keyboard events  

        while(!quit && events->GetEvent(events, &evt) == DFB_OK)
        {
            if(evt.clazz == DFEC_INPUT)
            {
                switch(evt.input.type)
                {
                case    DIET_KEYPRESS: //  exit program clear screen  
                    if(evt.input.key_symbol == DIKS_ESCAPE) //   
                    {
                        quit = 1;
                    }
                    else     if(evt.input.key_symbol == DIKS_SMALL_C)  //  is provided with buy the current color  
                    {
                        surface->SetColor(surface, 0, 56, 0 , 0xff);//  compiled in the middle of the screen  
                        surface->FillRectangle(surface, 0, 0, screen_width, screen_height);
                    }
                    break;

                case    DIET_AXISMOTION:
                    if(evt.input.flags & DIEF_AXISREL)
                    {
                        switch(evt.input.axis)
                        {
                        case DIAI_X:
                            x+=evt.input.axisrel;
                            break;
                        case DIAI_Y:
                            y+=evt.input.axisrel;
                            break;
                        default :
                            break;
                        }//switch(evt.input.axis){

                        if(x < 0)
                        {
                            x = 0;
                        }
                        if(y < 0)
                        {
                            y = 0;
                        }
                    }

                    surface->SetColor(surface, 0, 0xff, 0, 0xff);
                    surface->DrawLine(surface, old_x, old_y, x, y);
                    old_x = x;
                    old_y = y;
                    break;

                default:
                    break;
                }//switch
            }//if
        }//while(!quit && events->GetEvent(events, &evt) == DFB_OK){
    }//while(!quit){

    surface->Release(surface);
    layer->Release(layer);
    dfb->Release(dfb);

    return 0;
}
