#include "stdio.h"
#include "displayutils.h"
#include "celutils.h"
#include "controlpad.h"
#include "event.h"

// Screen Constants
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define CURRENT_SCREEN sc->sc_CurrentScreen
#define CURRENT_SCREEN_ITEMS sc->sc_ScreenItems[CURRENT_SCREEN]
#define CURRENT_SCREEN_BITMAPS sc->sc_Bitmaps[CURRENT_SCREEN]

// Bitwise Constants
#define FRACBITS_16 16
#define FRACBITS_20 20

// Velocity Constants
#define PLAYER_VEL_16 (4 << FRACBITS_16)
#define BULLET_VEL_16 (8 << FRACBITS_16)

#define MAX_BULLETS 100

ScreenContext *sc;

CCB *player_ccb;
CCB *bullets[MAX_BULLETS];

ControlPadEventData eventData;

Item sport;
Item vbl;

ubyte *bg;

uint32 previousButtons;
uint32 buttons;

int current_bullet_counter;

// Initialize everything.
void init()
{
    OpenGraphicsFolio();

    sc = (ScreenContext *)AllocMem(sizeof(ScreenContext), MEMTYPE_ANY);

    CreateBasicDisplay(sc, DI_TYPE_DEFAULT, 2);

    CURRENT_SCREEN = 0;

    sport = GetVRAMIOReq();
    vbl = GetVBLIOReq();

    bg = (ubyte *)LoadImage("Graphics/bg", NULL, NULL, sc);

    player_ccb = LoadCel("Graphics/sun", MEMTYPE_CEL);

    // Move the cel to the center of the screen;
    player_ccb->ccb_XPos = 144 << FRACBITS_16;
    player_ccb->ccb_YPos = 104 << FRACBITS_16;
    // Makes it so there is only one cel in the list.
    // ccb->ccb_Flags |= CCB_LAST;

    InitEventUtility(1, 0, LC_Observer);
}

int main(int argc, char *argv[])
{
    // Initialize all the things.
    init();

    while (TRUE)
    {
        /* Update */

        /* Input */

        GetControlPad(1, FALSE, &eventData);

        buttons = eventData.cped_ButtonBits;

        if (buttons & ControlLeft)
        {
            player_ccb->ccb_XPos -= PLAYER_VEL_16;

            if (buttons & ControlUp)
            {
                player_ccb->ccb_YPos -= PLAYER_VEL_16;
            }
            else if (buttons & ControlDown)
            {
                player_ccb->ccb_YPos += PLAYER_VEL_16;
            }

            if (buttons & ControlA)
            {
                if (current_bullet_counter <= MAX_BULLETS)
                {
                    bullets[current_bullet_counter] = LoadCel("Graphics/bullet", MEMTYPE_CEL);

                    bullets[current_bullet_counter]->ccb_XPos = player_ccb->ccb_XPos;
                    bullets[current_bullet_counter]->ccb_YPos = player_ccb->ccb_YPos;

                    current_bullet_counter++;
                }
                else
                {
                    current_bullet_counter = 0;
                }
            }
        }
        else if (buttons & ControlRight)
        {
            player_ccb->ccb_XPos += PLAYER_VEL_16;

            if (buttons & ControlUp)
            {
                player_ccb->ccb_YPos -= PLAYER_VEL_16;
            }
            else if (buttons & ControlDown)
            {
                player_ccb->ccb_YPos += PLAYER_VEL_16;
            }

            if (buttons & ControlA)
            {
                if (current_bullet_counter <= MAX_BULLETS)
                {
                    bullets[current_bullet_counter] = LoadCel("Graphics/bullet", MEMTYPE_CEL);

                    bullets[current_bullet_counter]->ccb_XPos = player_ccb->ccb_XPos;
                    bullets[current_bullet_counter]->ccb_YPos = player_ccb->ccb_YPos;

                    current_bullet_counter++;
                }
                else
                {
                    current_bullet_counter = 0;
                }
            }
        }

        else if (buttons & ControlUp)
        {
            player_ccb->ccb_YPos -= PLAYER_VEL_16;

            if (buttons & ControlLeft)
            {
                player_ccb->ccb_XPos -= PLAYER_VEL_16;
            }
            else if (buttons & ControlRight)
            {
                player_ccb->ccb_XPos += PLAYER_VEL_16;
            }

            if (buttons & ControlA)
            {
                if (current_bullet_counter <= MAX_BULLETS)
                {
                    bullets[current_bullet_counter] = LoadCel("Graphics/bullet", MEMTYPE_CEL);

                    bullets[current_bullet_counter]->ccb_XPos = player_ccb->ccb_XPos;
                    bullets[current_bullet_counter]->ccb_YPos = player_ccb->ccb_YPos;

                    current_bullet_counter++;
                }
                else
                {
                    current_bullet_counter = 0;
                }
            }
        }
        else if (buttons & ControlDown)
        {
            player_ccb->ccb_YPos += PLAYER_VEL_16;

            if (buttons & ControlLeft)
            {
                player_ccb->ccb_XPos -= PLAYER_VEL_16;
            }
            else if (buttons & ControlRight)
            {
                player_ccb->ccb_XPos += PLAYER_VEL_16;
            }

            if (buttons & ControlA)
            {
                if (current_bullet_counter <= MAX_BULLETS)
                {
                    bullets[current_bullet_counter] = LoadCel("Graphics/bullet", MEMTYPE_CEL);

                    bullets[current_bullet_counter]->ccb_XPos = player_ccb->ccb_XPos;
                    bullets[current_bullet_counter]->ccb_YPos = player_ccb->ccb_YPos;

                    current_bullet_counter++;
                }
                else
                {
                    current_bullet_counter = 0;
                }
            }
        }
        else if (buttons & ControlA)
        {
            if (current_bullet_counter <= MAX_BULLETS)
            {
                bullets[current_bullet_counter] = LoadCel("Graphics/bullet", MEMTYPE_CEL);

                bullets[current_bullet_counter]->ccb_XPos = player_ccb->ccb_XPos;
                bullets[current_bullet_counter]->ccb_YPos = player_ccb->ccb_YPos;

                current_bullet_counter++;
            }
            else
            {
                current_bullet_counter = 0;
            }

            if (buttons & ControlA)
            {
                if (current_bullet_counter <= MAX_BULLETS)
                {
                    bullets[current_bullet_counter] = LoadCel("Graphics/bullet", MEMTYPE_CEL);

                    bullets[current_bullet_counter]->ccb_XPos = player_ccb->ccb_XPos;
                    bullets[current_bullet_counter]->ccb_YPos = player_ccb->ccb_YPos;

                    current_bullet_counter++;
                }
                else
                {
                    current_bullet_counter = 0;
                }
            }
        }

        /* Draw */

        // Set the background to our bitmap.
        CopyVRAMPages(sport, CURRENT_SCREEN_BITMAPS->bm_Buffer, bg, sc->sc_NumBitmapPages, -1);

        // Draws the Sun.
        DrawCels(sc->sc_BitmapItems[CURRENT_SCREEN], player_ccb);

        for (int j = 0; j < MAX_BULLETS; j++)
        {
            DrawCels(sc->sc_BitmapItems[CURRENT_SCREEN], bullets[j]);

            bullets[j]->ccb_XPos += BULLET_VEL_16;
        }

        // Display to the screen.
        DisplayScreen(CURRENT_SCREEN_ITEMS, 0);

        // Flip the screen
        CURRENT_SCREEN = 1 - CURRENT_SCREEN;

        // Wait for VBlank.
        WaitVBL(vbl, 1);

        previousButtons = buttons;
    }

    return 0;
}