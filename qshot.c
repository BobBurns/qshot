#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <giblib/giblib.h>

Display *disp = NULL;
Visual *vis = NULL;
Screen *scr = NULL;
Colormap cm;
int depth;
Window root = 0;

int main (int argc, char **argv)
{
  Imlib_Load_Error err;

  char outfile[255];
  char *of = outfile;
  char timebuff[255];
  char *tb = timebuff;
  char infile[255];
  char *in = infile;
  time_t t;
  time (&t);
  struct tm *tm;
  tm = localtime (&t);
  strftime(tb, 255, "%Y-%m-%d-%H%M%S_", tm);
  if (argc == 2) {
    strncpy (in, argv[1], 255);
  } else {
    printf("usage: %s <filename>\n", argv[0]);
    return -1;
  }


  strncat (tb, in, 255);
  sprintf(of, "/tmp/%s", tb);
  /* initx */
  disp = XOpenDisplay (NULL);
  if (!disp)
    gib_eprintf ("Error. Not running X11. Exiting...");

  scr = ScreenOfDisplay (disp, DefaultScreen (disp));
  vis = DefaultVisual (disp, XScreenNumberOfScreen (scr));
  depth = DefaultDepth (disp, XScreenNumberOfScreen (scr));
  cm = DefaultColormap (disp, XScreenNumberOfScreen (scr));
  root = RootWindow (disp, XScreenNumberOfScreen (scr));

  imlib_context_set_display (disp);
  imlib_context_set_visual (vis);
  imlib_context_set_colormap (cm);
  imlib_context_set_color_modifier (NULL);
  imlib_context_set_operation (IMLIB_OP_COPY);

  /*  */
  

  Imlib_Image image = NULL;

  XBell (disp, 0);

  image = gib_imlib_create_image_from_drawable(root, 0, 0, 0, scr->width, scr->height, 1);

    
  if (!image) {
    gib_eprintf("no image created");
  }

  time (&t);

  tm = localtime (&t);

  imlib_context_set_image (image);
  imlib_image_attach_data_value ("quality", NULL, 75, NULL);

//  filename_im = im_printf (outfile, tm, NULL, NULL, im);
  gib_imlib_save_image_with_error_return (image, of, &err);
  if (err)
    gib_eprintf ("Saving to file %s failed\n", of);
    
  printf("%s\n", of);
  return 0;

}
