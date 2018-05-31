#include <directfb.h>
	
/* DirectFB interfaces */
IDirectFB *dfb;
IDirectFBSurface *primary;	
IDirectFBImageProvider *provider;

/* describes size, pixel format and capabilities of a surface*/
DFBSurfaceDescription dsc;

int main( int argc, char *argv[] )
{
	/* initalize DirectFB and pass arguments */
	DirectFBInit( &argc, &argv );

	/* create the super interface */
	DirectFBCreate( &dfb );
    	
	/* set cooperative level to DFSCL_FULLSCREEN for exclusive access to the primary layer */
	dfb->SetCooperativeLevel( dfb, DFSCL_FULLSCREEN );
	/* get the primary surface, i.e. the surface of the primary layer we have exclusive access to */
	memset( &dsc, 0, sizeof(DFBSurfaceDescription) );
	dsc.flags = DSDESC_CAPS; /* only the caps field of the description is valid. height, width and pixelformat are not set, since the resolution and pixel are determined by the current video mode */
	dsc.caps = DSCAPS_PRIMARY; /* we want the primary surface (the whole screen) */
	
	// Since we are in fullscreen mode no new surface will be created, the whole screen will be made accessible through a IDirectFBSurface 
	dfb->CreateSurface( dfb, &dsc, &primary );

	/* create the image provider that will load the image */
	dfb->CreateImageProvider( dfb, "test.png", &provider );

	/* render the image to the screen */
	provider->RenderTo( provider, primary, NULL );

	/* release the image provider, it is no longer necessary */
	provider->Release( provider );
	sleep (5);

	/* clean up */
	primary->Release( primary );
	dfb->Release( dfb );
}


