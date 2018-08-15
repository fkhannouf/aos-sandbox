/******************************* INCLUDES *************************************/

#include <intuition/gadgetclass.h>
#include <classes/window.h>
#include <reaction/reaction_macros.h>
#include <libraries/gadtools.h>
#include <gadgets/checkbox.h>

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>
#include <proto/window.h>
#include <proto/layout.h>
#include <proto/button.h>
#include <proto/checkbox.h>

#include <memory>

#include <UICheckBox.h>
#include <UIButton.h>
#include <UIGroup.h>


#define MENU_ID_Quit       FULLMENUNUM(0,0,NOSUB)

#define GAD_ID_Help        1
#define GAD_ID_Quit        2

#define PROGNAME "ToDo"
#define VERSIONR "0.00"
#define PROGDATE "11.08.2018"
#define COPYRIGT "Copyright (c) Aug.2018"
#define AUTORNAM "by Frédéric Khannouf"

static const char *version = "\0$VER: " PROGNAME " " VERSIONR " (" PROGDATE ") - " COPYRIGT " " AUTORNAM "\n";

Object        *gb_WindowObj;
struct Window *gb_Win;
struct Gadget *gb_MainLayout;
struct Gadget *gb_ButtonGad;
struct Gadget *gb_CheckboxGad;

struct NewMenu gb_MenuDescribe[] =
{
  { NM_TITLE, "Project",   NULL, 0, 0, NULL },
  { NM_ITEM,  "Quit",      NULL, 0, 0, NULL },

  { NM_END, NULL, NULL, 0, 0, NULL }
};

struct HintInfo gb_HintInfo[] =
{
 	{ GAD_ID_Help, -1, "Activate/Deactive BubbleHelp Tips", 0 },
 	{ GAD_ID_Quit, -1, "Quit Program", 0 },
 	{ -1, -1, NULL, 0 }
};

/******************************************************************************/

int main()
{
	UICheckBox* checkBox = new UICheckBox((UICheckBoxProps){
		ID : GAD_ID_Help,
		RelVerify : TRUE,
		Text : "Bubble_Help Active"
	});

	UIButton* button = new UIButton((UIButtonProps){
		ID : GAD_ID_Quit,
		RelVerify : TRUE,
		Text : "_Quit"
	});

	UIGroup* verticalGroup = new UIGroup((UIGroupProps){
		Orientation : LAYOUT_ORIENT_VERT,
		SpaceOuter : TRUE,
		SpaceInner : TRUE
	});

	verticalGroup.addMember(button);

	//CheckBox *checkBox = new CheckBox();

  /* create a Checkbox Gadget */
  if (gb_CheckboxGad = checkBox->gadget())
  {
    /* create the Button */
    if(gb_ButtonGad = button->gadget())
    {
      /* create the Window Object */
      if((gb_WindowObj = (Object *) IIntuition->NewObject(IWindow->WINDOW_GetClass(),NULL,
        WA_IDCMP,             IDCMP_GADGETUP | IDCMP_CLOSEWINDOW | IDCMP_MENUPICK,
        WA_SizeGadget,        TRUE,
        WA_DepthGadget,       TRUE,
        WA_DragBar,           TRUE,
        WA_CloseGadget,       TRUE,
        WA_Activate,          TRUE,
        WA_Title,             "Example with ReAction gadgets and window class",
        WINDOW_Position,      WPOS_CENTERSCREEN,
        WINDOW_NewMenu,       gb_MenuDescribe,
        WINDOW_HintInfo,      gb_HintInfo,
        WINDOW_GadgetHelp,    FALSE,

        /* create the Layout Object and include it into the Window */
        WINDOW_ParentGroup,   gb_MainLayout = (struct Gadget *)
                          IIntuition->NewObject(ILayout->LAYOUT_GetClass(),NULL,
          LAYOUT_Orientation,  LAYOUT_ORIENT_VERT,
          LAYOUT_SpaceOuter,   TRUE,
          LAYOUT_SpaceInner,   TRUE,
          LAYOUT_AddChild,     gb_CheckboxGad,
          LAYOUT_AddChild,     gb_ButtonGad,
          TAG_DONE),
        TAG_DONE)))
      {
        /* open the Window */
        if((gb_Win = RA_OpenWindow(gb_WindowObj)))
        {
          /* query the Signal Bit of the Window */
          ULONG winsig;
          IIntuition->GetAttr(WINDOW_SigMask,gb_WindowObj,&winsig);

          BOOL laufen = TRUE;
          while(laufen)
          {
            ULONG result, code, val;

            /* wait till either Button or Close Icon are clicked */
            const ULONG sigs = IExec->Wait(winsig | SIGBREAKF_CTRL_C);

            /* process the received Messages */
            while((result = RA_HandleInput(gb_WindowObj,&code)) != WMHI_LASTMSG)
            {
              /* mask out the Messages part */
              switch(result & WMHI_CLASSMASK)
              {
                /* process the Gadget Messages */
                case WMHI_GADGETUP:
                     switch(result & WMHI_GADGETMASK)
                     {
                       case GAD_ID_Help:
                            IIntuition->GetAttr(CHECKBOX_Checked,
                                                (Object*)gb_CheckboxGad,
                                                (ULONG*)&val);
                            IIntuition->SetAttrs(gb_WindowObj,
                                                 WINDOW_GadgetHelp, val,
                                                 TAG_DONE);
                            break;

                       case GAD_ID_Quit:
                            laufen = FALSE;
                            break;
                     }
                     break;

                /* query the Window Close Icon */
                case WMHI_CLOSEWINDOW:
                     laufen = FALSE;
                     break;

                /* query the Menu Selection */
                case WMHI_MENUPICK:
                     switch(result & WMHI_MENUMASK)
                     {
                       case MENU_ID_Quit:
                            laufen = FALSE;
                            break;
                     }
                     break;
              }
            }

            /* query if CTRL-C received from the Shell */
            if(sigs & SIGBREAKF_CTRL_C) laufen = FALSE;
          }

          /* close the Window */
          RA_CloseWindow(gb_WindowObj);
        }
      }
    }

    /* release Window Object, dump also Layout and Gadget Objects */
    IIntuition->DisposeObject(gb_WindowObj);
  }

  return 0;
}
