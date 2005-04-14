/*
 * BRLTTY - A background process providing access to the console screen (when in
 *          text mode) for a blind person using a refreshable braille display.
 *
 * Copyright (C) 1995-2005 by The BRLTTY Team. All rights reserved.
 *
 * BRLTTY comes with ABSOLUTELY NO WARRANTY.
 *
 * This is free software, placed under the terms of the
 * GNU General Public License, as published by the Free Software
 * Foundation.  Please see the file COPYING for details.
 *
 * Web Page: http://mielke.cc/brltty/
 *
 * This software is maintained by Dave Mielke <dave@mielke.cc>.
 */

#ifndef BRLTTY_INCLUDED_SCR
#define BRLTTY_INCLUDED_SCR

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* scr.h - C header file for the screen reading library
 */

/* mode argument for readScreen() */
typedef enum {
  SCR_TEXT,		/* get screen text */
  SCR_ATTRIB		/* get screen attributes */
} ScreenMode;

/* disp argument for selectDisplay() */
#define LIVE_SCRN 0		/* read the physical screen */
#define FROZ_SCRN 1		/* read frozen screen image */
#define HELP_SCRN 2		/* read help screen */

typedef struct {
  short rows, cols;	/* screen dimentions */
  short posx, posy;	/* cursor position */
  short no;		      /* screen number */
} ScreenDescription;

typedef struct {
  short left, top;	/* top-left corner (offset from 0) */
  short width, height;	/* dimensions */
} ScreenBox;
extern int validateScreenBox (const ScreenBox *box, int columns, int rows);

#define SCR_KEY_MOD_META 0X100
typedef enum {
  SCR_KEY_ENTER = 0X200,
  SCR_KEY_TAB,
  SCR_KEY_BACKSPACE,
  SCR_KEY_ESCAPE,
  SCR_KEY_CURSOR_LEFT,
  SCR_KEY_CURSOR_RIGHT,
  SCR_KEY_CURSOR_UP,
  SCR_KEY_CURSOR_DOWN,
  SCR_KEY_PAGE_UP,
  SCR_KEY_PAGE_DOWN,
  SCR_KEY_HOME,
  SCR_KEY_END,
  SCR_KEY_INSERT,
  SCR_KEY_DELETE,
  SCR_KEY_FUNCTION
} ScreenKey;

/* Routines which apply to all screens. */
extern void initializeAllScreens (const char *identifier, const char *driverDirectory);		/* close screen reading */
extern void closeAllScreens (void);		/* close screen reading */
extern int selectDisplay (int);		/* select display page */

/* Routines which apply to the current screen. */
extern void describeScreen (ScreenDescription *);		/* get screen status */
extern unsigned char *readScreen (short, short, short, short, unsigned char *, ScreenMode);
extern int insertKey (ScreenKey);
extern int insertCharacters (const char *, int);
extern int insertString (const char *);
extern int routeCursor (int, int, int);
extern int setPointer (int, int);
extern int getPointer (int *, int *);
extern int selectVirtualTerminal (int);
extern int switchVirtualTerminal (int);
extern int currentVirtualTerminal (void);
extern int executeScreenCommand (int);

/* Routines which apply to the live screen. */
extern const char *const *getScreenParameters (void);			/* initialise screen reading functions */
extern int openLiveScreen (char **parameters);			/* initialise screen reading functions */

/* Routines which apply to the routing screen.
 * An extra `thread' for the cursor routing subprocess.
 * This is needed because the forked subprocess shares its parent's
 * file descriptors.  A readScreen equivalent is not needed.
 */
extern int openRoutingScreen (void);
extern void describeRoutingScreen (ScreenDescription *);
extern void closeRoutingScreen (void);

/* Routines which apply to the help screen. */
extern int openHelpScreen (const char *);
extern void closeHelpScreen (void);
extern void setHelpPageNumber (short);
extern short getHelpPageNumber (void);
extern short getHelpPageCount (void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BRLTTY_INCLUDED_SCR */
