/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <boost/array.hpp>
#include <boost/bind.hpp>
#include "../../../exception.hpp"
#include "../../../input/key_type.hpp"
#include "../../../util.hpp"
#include "../../../iconv.hpp"
#include "../input_system.hpp"
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <X11/X.h>
#ifdef USE_DGA
#include <X11/extensions/xf86dga.h>
#endif
#include <iostream>

sge::xinput::input_system::input_system(const x_window_ptr wnd)
 : wnd(wnd),
   colormap(DefaultColormap(wnd->display()->get(), wnd->screen())),
   mouse_last(),
   _black(wnd->display(), colormap),
   _no_bmp(wnd->display(), wnd->get_window()),
   _no_cursor(wnd->display(), _no_bmp.pixmap(), _black.color()),
#ifdef USE_DGA
   _dga_guard(wnd->display(), wnd->screen()),
   use_dga(true)
#else
   use_dga(false)
#endif
{
#ifdef USE_DGA
	int flags;
	if(XF86DGAQueryDirectVideo(wnd->display()->get(),wnd->screen(),&flags)==false)
		throw exception("XF86DGAQueryDirectVideo() failed");
	if(flags & XF86DGADirectMouse)
	{
		std::cerr << "You compiled spacegameengine with use_dga=1 but DGA Mouse is not supported by your system! Maybe you are missing libXxf86dga or a proper video driver? Disabling dga.";
		use_dga = false;
	}
#endif
	if(!use_dga)
	{
		Window root_return,
		       child_return;
		int root_x_return,
		    root_y_return,
		    win_x_return,
		    win_y_return;
		unsigned mask_return;

		XQueryPointer(wnd->display()->get(), wnd->get_window(), &root_return, &child_return, &root_x_return, &root_y_return, &win_x_return, &win_y_return, &mask_return);
		mouse_last.x() = win_x_return;
		mouse_last.y() = win_y_return;
	}
	
	wnd->register_callback(KeyPress, boost::bind(&input_system::on_key_event, this, _1));
	wnd->register_callback(KeyRelease, boost::bind(&input_system::on_key_event, this, _1));
	wnd->register_callback(ButtonPress, boost::bind(&input_system::on_button_event, this, _1));
	wnd->register_callback(ButtonRelease, boost::bind(&input_system::on_button_event, this, _1));
	wnd->register_callback(MotionNotify, boost::bind(&input_system::on_motion_event, this, _1));
	wnd->register_callback(EnterNotify, boost::bind(&input_system::on_acquire, this, _1));
	wnd->register_callback(LeaveNotify, boost::bind(&input_system::on_release, this, _1));
	wnd->register_callback(FocusIn, boost::bind(&input_system::on_acquire, this, _1));
	wnd->register_callback(FocusOut, boost::bind(&input_system::on_release, this, _1));
	wnd->register_callback(MapNotify, boost::bind(&input_system::on_acquire, this, _1));
	wnd->register_callback(UnmapNotify, boost::bind(&input_system::on_release, this, _1));

	x11tosge[NoSymbol] = KC_None;
	x11tosge[XK_BackSpace] = KC_BACK;
	x11tosge[XK_Tab] = KC_TAB;
	x11tosge[XK_Return] = KC_RETURN;
	x11tosge[XK_Pause] = KC_PAUSE;
	x11tosge[XK_Scroll_Lock] = KC_SCROLL;
	x11tosge[XK_Escape] = KC_ESC;
	x11tosge[XK_Delete] = KC_DEL;

	x11tosge[XK_Home] = KC_HOME;
	x11tosge[XK_Left] = KC_LEFT;
	x11tosge[XK_Up]   = KC_UP;
	x11tosge[XK_Right] = KC_RIGHT;
	x11tosge[XK_Down] = KC_DOWN;
	//XK_Prior
	x11tosge[XK_Page_Up] = KC_PGUP;
	//XK_Next
	x11tosge[XK_Page_Down] = KC_PGDN;
	x11tosge[XK_End] = KC_END;
	x11tosge[XK_Begin] = KC_HOME;

	//#define XK_Select                        0xff60  /* Select, mark */
	//#define XK_Print                         0xff61
	//#define XK_Execute                       0xff62  /* Execute, run, do */
	x11tosge[XK_Insert] = KC_INS;
//#define XK_Undo                          0xff65
//#define XK_Redo                          0xff66  /* Redo, again */
//#define XK_Menu                          0xff67
//#define XK_Find                          0xff68  /* Find, search */
//#define XK_Cancel                        0xff69  /* Cancel, stop, abort, exit */
//#define XK_Help                          0xff6a  /* Help */
//#define XK_Break                         0xff6b
//#define XK_Mode_switch                   0xff7e  /* Character set switch */
//#define XK_script_switch                 0xff7e  /* Alias for mode_switch */
//#define XK_Num_Lock                      0xff7f

//	x11tosge[XK_KP_Space] = KC_SPACE;
//	x11tosge[XK_KP_Tab];
//	x11tosge[XK_KP_Enter] = KC_ENTER;
/*	x11tosge[XK_KP_F1];
	x11tosge[XK_KP_F2];
	x11tosge[XK_KP_F3];
	x11tosge[XK_KP_F4];
	x11tosge[XK_KP_Home] = KC_NUM_HOME;
	x11tosge[XK_KP_Left] = KC_NUM_LEFT;
	x11tosge[XK_KP_Up] = KC_NUM_UP;
#define XK_KP_Right                      0xff98
#define XK_KP_Down                       0xff99
#define XK_KP_Prior                      0xff9a
#define XK_KP_Page_Up                    0xff9a
#define XK_KP_Next                       0xff9b
#define XK_KP_Page_Down                  0xff9b
#define XK_KP_End                        0xff9c
#define XK_KP_Begin                      0xff9d
#define XK_KP_Insert                     0xff9e
#define XK_KP_Delete                     0xff9f
#define XK_KP_Equal                      0xffbd/
#define XK_KP_Multiply                   0xffaa
#define XK_KP_Add                        0xffab
#define XK_KP_Separator                  0xffac
#define XK_KP_Subtract                   0xffad
#define XK_KP_Decimal                    0xffae
#define XK_KP_Divide                     0xffaf

#define XK_KP_0                          0xffb0
#define XK_KP_1                          0xffb1
#define XK_KP_2                          0xffb2
#define XK_KP_3                          0xffb3
#define XK_KP_4                          0xffb4
#define XK_KP_5                          0xffb5
#define XK_KP_6                          0xffb6
#define XK_KP_7                          0xffb7
#define XK_KP_8                          0xffb8
#define XK_KP_9                          0xffb9*/

	x11tosge[XK_F1] = KC_F1;
	x11tosge[XK_F2] = KC_F2;
	x11tosge[XK_F3] = KC_F3;
	x11tosge[XK_F4] = KC_F4;
	x11tosge[XK_F5] = KC_F5;
	x11tosge[XK_F6] = KC_F6;
	x11tosge[XK_F7] = KC_F7;
	x11tosge[XK_F8] = KC_F8;
	x11tosge[XK_F9] = KC_F9;
	x11tosge[XK_F10] = KC_F10;
	x11tosge[XK_F11] = KC_F11;
	x11tosge[XK_F12] = KC_F12;
//#define XK_L1                            0xffc8
/*
#define XK_L2                            0xffc9
#define XK_F13                           0xffca
#define XK_L3                            0xffca
#define XK_F14                           0xffcb
#define XK_L4                            0xffcb
#define XK_F15                           0xffcc
#define XK_L5                            0xffcc
#define XK_F16                           0xffcd
#define XK_L6                            0xffcd
#define XK_F17                           0xffce
#define XK_L7                            0xffce
#define XK_F18                           0xffcf
#define XK_L8                            0xffcf
#define XK_F19                           0xffd0
#define XK_L9                            0xffd0
#define XK_F20                           0xffd1
#define XK_L10                           0xffd1
#define XK_F21                           0xffd2
#define XK_R1                            0xffd2
#define XK_F22                           0xffd3
#define XK_R2                            0xffd3
#define XK_F23                           0xffd4
#define XK_R3                            0xffd4
#define XK_F24                           0xffd5
#define XK_R4                            0xffd5
#define XK_F25                           0xffd6
#define XK_R5                            0xffd6
#define XK_F26                           0xffd7
#define XK_R6                            0xffd7
#define XK_F27                           0xffd8
#define XK_R7                            0xffd8
#define XK_F28                           0xffd9
#define XK_R8                            0xffd9
#define XK_F29                           0xffda
#define XK_R9                            0xffda
#define XK_F30                           0xffdb
#define XK_R10                           0xffdb
#define XK_F31                           0xffdc
#define XK_R11                           0xffdc
#define XK_F32                           0xffdd
#define XK_R12                           0xffdd
#define XK_F33                           0xffde
#define XK_R13                           0xffde
#define XK_F34                           0xffdf
#define XK_R14                           0xffdf
#define XK_F35                           0xffe0
#define XK_R15                           0xffe0
*/


	x11tosge[XK_Shift_L] = KC_LSHIFT;
	x11tosge[XK_Shift_R] = KC_RSHIFT;
	x11tosge[XK_Control_L] = KC_LCTRL;
	x11tosge[XK_Control_R] = KC_RCTRL;
	//XK_Caps_Lock
	x11tosge[XK_Shift_Lock] = KC_LSHIFT; // ???

//#define XK_Meta_L                        0xffe7  /* Left meta */
//#define XK_Meta_R                        0xffe8  /* Right meta */
//#define XK_Alt_L                         0xffe9  /* Left alt */
//#define XK_Alt_R                         0xffea  /* Right alt */
//#define XK_Super_L                       0xffeb  /* Left super */
//#define XK_Super_R                       0xffec  /* Right super */
//#define XK_Hyper_L                       0xffed  /* Left hyper */
//#define XK_Hyper_R                       0xffee  /* Right hyper */
#if 0
#define XK_ISO_Lock                      0xfe01
#define XK_ISO_Level2_Latch              0xfe02
#define XK_ISO_Level3_Shift              0xfe03
#define XK_ISO_Level3_Latch              0xfe04
#define XK_ISO_Level3_Lock               0xfe05
#define XK_ISO_Level5_Shift              0xfe11
#define XK_ISO_Level5_Latch              0xfe12
#define XK_ISO_Level5_Lock               0xfe13
#define XK_ISO_Group_Shift               0xff7e  /* Alias for mode_switch */
#define XK_ISO_Group_Latch               0xfe06
#define XK_ISO_Group_Lock                0xfe07
#define XK_ISO_Next_Group                0xfe08
#define XK_ISO_Next_Group_Lock           0xfe09
#define XK_ISO_Prev_Group                0xfe0a
#define XK_ISO_Prev_Group_Lock           0xfe0b
#define XK_ISO_First_Group               0xfe0c
#define XK_ISO_First_Group_Lock          0xfe0d
#define XK_ISO_Last_Group                0xfe0e
#define XK_ISO_Last_Group_Lock           0xfe0f

#define XK_ISO_Left_Tab                  0xfe20
#define XK_ISO_Move_Line_Up              0xfe21
#define XK_ISO_Move_Line_Down            0xfe22
#define XK_ISO_Partial_Line_Up           0xfe23
#define XK_ISO_Partial_Line_Down         0xfe24
#define XK_ISO_Partial_Space_Left        0xfe25
#define XK_ISO_Partial_Space_Right       0xfe26
#define XK_ISO_Set_Margin_Left           0xfe27
#define XK_ISO_Set_Margin_Right          0xfe28
#define XK_ISO_Release_Margin_Left       0xfe29
#define XK_ISO_Release_Margin_Right      0xfe2a
#define XK_ISO_Release_Both_Margins      0xfe2b
#define XK_ISO_Fast_Cursor_Left          0xfe2c
#define XK_ISO_Fast_Cursor_Right         0xfe2d
#define XK_ISO_Fast_Cursor_Up            0xfe2e
#define XK_ISO_Fast_Cursor_Down          0xfe2f
#define XK_ISO_Continuous_Underline      0xfe30
#define XK_ISO_Discontinuous_Underline   0xfe31
#define XK_ISO_Emphasize                 0xfe32
#define XK_ISO_Center_Object             0xfe33
#define XK_ISO_Enter                     0xfe34

#define XK_dead_grave                    0xfe50
#define XK_dead_acute                    0xfe51
#define XK_dead_circumflex               0xfe52
#define XK_dead_tilde                    0xfe53
#define XK_dead_macron                   0xfe54
#define XK_dead_breve                    0xfe55
#define XK_dead_abovedot                 0xfe56
#define XK_dead_diaeresis                0xfe57
#define XK_dead_abovering                0xfe58
#define XK_dead_doubleacute              0xfe59
#define XK_dead_caron                    0xfe5a
#define XK_dead_cedilla                  0xfe5b
#define XK_dead_ogonek                   0xfe5c
#define XK_dead_iota                     0xfe5d
#define XK_dead_voiced_sound             0xfe5e
#define XK_dead_semivoiced_sound         0xfe5f
#define XK_dead_belowdot                 0xfe60
#define XK_dead_hook                     0xfe61
#define XK_dead_horn                     0xfe62
#define XK_dead_stroke                   0xfe63

#define XK_First_Virtual_Screen          0xfed0
#define XK_Prev_Virtual_Screen           0xfed1
#define XK_Next_Virtual_Screen           0xfed2
#define XK_Last_Virtual_Screen           0xfed4
#define XK_Terminate_Server              0xfed5

#define XK_AccessX_Enable                0xfe70
#define XK_AccessX_Feedback_Enable       0xfe71
#define XK_RepeatKeys_Enable             0xfe72
#define XK_SlowKeys_Enable               0xfe73
#define XK_BounceKeys_Enable             0xfe74
#define XK_StickyKeys_Enable             0xfe75
#define XK_MouseKeys_Enable              0xfe76
#define XK_MouseKeys_Accel_Enable        0xfe77
#define XK_Overlay1_Enable               0xfe78
#define XK_Overlay2_Enable               0xfe79
#define XK_AudibleBell_Enable            0xfe7a

#define XK_Pointer_Left                  0xfee0
#define XK_Pointer_Right                 0xfee1
#define XK_Pointer_Up                    0xfee2
#define XK_Pointer_Down                  0xfee3
#define XK_Pointer_UpLeft                0xfee4
#define XK_Pointer_UpRight               0xfee5
#define XK_Pointer_DownLeft              0xfee6
#define XK_Pointer_DownRight             0xfee7
#define XK_Pointer_Button_Dflt           0xfee8
#define XK_Pointer_Button1               0xfee9
#define XK_Pointer_Button2               0xfeea
#define XK_Pointer_Button3               0xfeeb
#define XK_Pointer_Button4               0xfeec
#define XK_Pointer_Button5               0xfeed
#define XK_Pointer_DblClick_Dflt         0xfeee
#define XK_Pointer_DblClick1             0xfeef
#define XK_Pointer_DblClick2             0xfef0
#define XK_Pointer_DblClick3             0xfef1
#define XK_Pointer_DblClick4             0xfef2
#define XK_Pointer_DblClick5             0xfef3
#define XK_Pointer_Drag_Dflt             0xfef4
#define XK_Pointer_Drag1                 0xfef5
#define XK_Pointer_Drag2                 0xfef6
#define XK_Pointer_Drag3                 0xfef7
#define XK_Pointer_Drag4                 0xfef8
#define XK_Pointer_Drag5                 0xfefd

#define XK_Pointer_EnableKeys            0xfef9
#define XK_Pointer_Accelerate            0xfefa
#define XK_Pointer_DfltBtnNext           0xfefb
#define XK_Pointer_DfltBtnPrev           0xfefc

#define XK_3270_Duplicate                0xfd01
#define XK_3270_FieldMark                0xfd02
#define XK_3270_Right2                   0xfd03
#define XK_3270_Left2                    0xfd04
#define XK_3270_BackTab                  0xfd05
#define XK_3270_EraseEOF                 0xfd06
#define XK_3270_EraseInput               0xfd07
#define XK_3270_Reset                    0xfd08
#define XK_3270_Quit                     0xfd09
#define XK_3270_PA1                      0xfd0a
#define XK_3270_PA2                      0xfd0b
#define XK_3270_PA3                      0xfd0c
#define XK_3270_Test                     0xfd0d
#define XK_3270_Attn                     0xfd0e
#define XK_3270_CursorBlink              0xfd0f
#define XK_3270_AltCursor                0xfd10
#define XK_3270_KeyClick                 0xfd11
#define XK_3270_Jump                     0xfd12
#define XK_3270_Ident                    0xfd13
#define XK_3270_Rule                     0xfd14
#define XK_3270_Copy                     0xfd15
#define XK_3270_Play                     0xfd16
#define XK_3270_Setup                    0xfd17
#define XK_3270_Record                   0xfd18
#define XK_3270_ChangeScreen             0xfd19
#define XK_3270_DeleteWord               0xfd1a
#define XK_3270_ExSelect                 0xfd1b
#define XK_3270_CursorSelect             0xfd1c
#define XK_3270_PrintScreen              0xfd1d
#define XK_3270_Enter                    0xfd1e
#endif

	x11tosge[XK_space] = KC_SPACE;
#if 0
#define XK_exclam                        0x0021  /* U+0021 EXCLAMATION MARK */
#define XK_quotedbl                      0x0022  /* U+0022 QUOTATION MARK */
#define XK_numbersign                    0x0023  /* U+0023 NUMBER SIGN */
#define XK_dollar                        0x0024  /* U+0024 DOLLAR SIGN */
#define XK_percent                       0x0025  /* U+0025 PERCENT SIGN */
#define XK_ampersand                     0x0026  /* U+0026 AMPERSAND */
#define XK_apostrophe                    0x0027  /* U+0027 APOSTROPHE */
#define XK_quoteright                    0x0027  /* deprecated */
#define XK_parenleft                     0x0028  /* U+0028 LEFT PARENTHESIS */
#define XK_parenright                    0x0029  /* U+0029 RIGHT PARENTHESIS */
#define XK_asterisk                      0x002a  /* U+002A ASTERISK */
#define XK_plus                          0x002b  /* U+002B PLUS SIGN */
#define XK_comma                         0x002c  /* U+002C COMMA */
#define XK_minus                         0x002d  /* U+002D HYPHEN-MINUS */
#define XK_period                        0x002e  /* U+002E FULL STOP */
#define XK_slash                         0x002f  /* U+002F SOLIDUS */
#define XK_0                             0x0030  /* U+0030 DIGIT ZERO */
#define XK_1                             0x0031  /* U+0031 DIGIT ONE */
#define XK_2                             0x0032  /* U+0032 DIGIT TWO */
#define XK_3                             0x0033  /* U+0033 DIGIT THREE */
#define XK_4                             0x0034  /* U+0034 DIGIT FOUR */
#define XK_5                             0x0035  /* U+0035 DIGIT FIVE */
#define XK_6                             0x0036  /* U+0036 DIGIT SIX */
#define XK_7                             0x0037  /* U+0037 DIGIT SEVEN */
#define XK_8                             0x0038  /* U+0038 DIGIT EIGHT */
#define XK_9                             0x0039  /* U+0039 DIGIT NINE */
#define XK_colon                         0x003a  /* U+003A COLON */
#define XK_semicolon                     0x003b  /* U+003B SEMICOLON */
#define XK_less                          0x003c  /* U+003C LESS-THAN SIGN */
#define XK_equal                         0x003d  /* U+003D EQUALS SIGN */
#define XK_greater                       0x003e  /* U+003E GREATER-THAN SIGN */
#define XK_question                      0x003f  /* U+003F QUESTION MARK */
#define XK_at                            0x0040  /* U+0040 COMMERCIAL AT */
#define XK_A                             0x0041  /* U+0041 LATIN CAPITAL LETTER A */
#define XK_B                             0x0042  /* U+0042 LATIN CAPITAL LETTER B */
#define XK_C                             0x0043  /* U+0043 LATIN CAPITAL LETTER C */
#define XK_D                             0x0044  /* U+0044 LATIN CAPITAL LETTER D */
#define XK_E                             0x0045  /* U+0045 LATIN CAPITAL LETTER E */
#define XK_F                             0x0046  /* U+0046 LATIN CAPITAL LETTER F */
#define XK_G                             0x0047  /* U+0047 LATIN CAPITAL LETTER G */
#define XK_H                             0x0048  /* U+0048 LATIN CAPITAL LETTER H */
#define XK_I                             0x0049  /* U+0049 LATIN CAPITAL LETTER I */
#define XK_J                             0x004a  /* U+004A LATIN CAPITAL LETTER J */
#define XK_K                             0x004b  /* U+004B LATIN CAPITAL LETTER K */
#define XK_L                             0x004c  /* U+004C LATIN CAPITAL LETTER L */
#define XK_M                             0x004d  /* U+004D LATIN CAPITAL LETTER M */
#define XK_N                             0x004e  /* U+004E LATIN CAPITAL LETTER N */
#define XK_O                             0x004f  /* U+004F LATIN CAPITAL LETTER O */
#define XK_P                             0x0050  /* U+0050 LATIN CAPITAL LETTER P */
#define XK_Q                             0x0051  /* U+0051 LATIN CAPITAL LETTER Q */
#define XK_R                             0x0052  /* U+0052 LATIN CAPITAL LETTER R */
#define XK_S                             0x0053  /* U+0053 LATIN CAPITAL LETTER S */
#define XK_T                             0x0054  /* U+0054 LATIN CAPITAL LETTER T */
#define XK_U                             0x0055  /* U+0055 LATIN CAPITAL LETTER U */
#define XK_V                             0x0056  /* U+0056 LATIN CAPITAL LETTER V */
#define XK_W                             0x0057  /* U+0057 LATIN CAPITAL LETTER W */
#define XK_X                             0x0058  /* U+0058 LATIN CAPITAL LETTER X */
#define XK_Y                             0x0059  /* U+0059 LATIN CAPITAL LETTER Y */
#define XK_Z                             0x005a  /* U+005A LATIN CAPITAL LETTER Z */
#define XK_bracketleft                   0x005b  /* U+005B LEFT SQUARE BRACKET */
#define XK_backslash                     0x005c  /* U+005C REVERSE SOLIDUS */
#define XK_bracketright                  0x005d  /* U+005D RIGHT SQUARE BRACKET */
#define XK_asciicircum                   0x005e  /* U+005E CIRCUMFLEX ACCENT */
#define XK_underscore                    0x005f  /* U+005F LOW LINE */
#define XK_grave                         0x0060  /* U+0060 GRAVE ACCENT */
#define XK_quoteleft                     0x0060  /* deprecated */
#define XK_a                             0x0061  /* U+0061 LATIN SMALL LETTER A */
#define XK_b                             0x0062  /* U+0062 LATIN SMALL LETTER B */
#define XK_c                             0x0063  /* U+0063 LATIN SMALL LETTER C */
#define XK_d                             0x0064  /* U+0064 LATIN SMALL LETTER D */
#define XK_e                             0x0065  /* U+0065 LATIN SMALL LETTER E */
#define XK_f                             0x0066  /* U+0066 LATIN SMALL LETTER F */
#define XK_g                             0x0067  /* U+0067 LATIN SMALL LETTER G */
#define XK_h                             0x0068  /* U+0068 LATIN SMALL LETTER H */
#define XK_i                             0x0069  /* U+0069 LATIN SMALL LETTER I */
#define XK_j                             0x006a  /* U+006A LATIN SMALL LETTER J */
#define XK_k                             0x006b  /* U+006B LATIN SMALL LETTER K */
#define XK_l                             0x006c  /* U+006C LATIN SMALL LETTER L */
#define XK_m                             0x006d  /* U+006D LATIN SMALL LETTER M */
#define XK_n                             0x006e  /* U+006E LATIN SMALL LETTER N */
#define XK_o                             0x006f  /* U+006F LATIN SMALL LETTER O */
#define XK_p                             0x0070  /* U+0070 LATIN SMALL LETTER P */
#define XK_q                             0x0071  /* U+0071 LATIN SMALL LETTER Q */
#define XK_r                             0x0072  /* U+0072 LATIN SMALL LETTER R */
#define XK_s                             0x0073  /* U+0073 LATIN SMALL LETTER S */
#define XK_t                             0x0074  /* U+0074 LATIN SMALL LETTER T */
#define XK_u                             0x0075  /* U+0075 LATIN SMALL LETTER U */
#define XK_v                             0x0076  /* U+0076 LATIN SMALL LETTER V */
#define XK_w                             0x0077  /* U+0077 LATIN SMALL LETTER W */
#define XK_x                             0x0078  /* U+0078 LATIN SMALL LETTER X */
#define XK_y                             0x0079  /* U+0079 LATIN SMALL LETTER Y */
#define XK_z                             0x007a  /* U+007A LATIN SMALL LETTER Z */
#define XK_braceleft                     0x007b  /* U+007B LEFT CURLY BRACKET */
#define XK_bar                           0x007c  /* U+007C VERTICAL LINE */
#define XK_braceright                    0x007d  /* U+007D RIGHT CURLY BRACKET */
#define XK_asciitilde                    0x007e  /* U+007E TILDE */
#endif
}

sge::xinput::input_system::~input_system()
{
	if(wnd->fullscreen())
		XUngrabKeyboard(wnd->display()->get(), CurrentTime);
	XUngrabPointer(wnd->display()->get(), CurrentTime);
}

boost::signals::connection sge::xinput::input_system::register_callback(const callback& c)
{
	return sig.connect(c);
}

boost::signals::connection sge::xinput::input_system::register_repeat_callback(const repeat_callback& c)
{
	return repeat_sig.connect(c);
}

void sge::xinput::input_system::dispatch()
{
}

sge::window_ptr sge::xinput::input_system::get_window() const
{
	return wnd;
}

void sge::xinput::input_system::grab()
{
	grab_pointer();
	if(wnd->fullscreen())
		grab_keyboard();
	XSync(wnd->display()->get(), False);
}

void sge::xinput::input_system::grab_pointer()
{
	for(;;)
		if(handle_grab(XGrabPointer(wnd->display()->get(), wnd->get_window(), True, PointerMotionMask | ButtonPressMask | ButtonReleaseMask, GrabModeAsync, GrabModeAsync, wnd->get_window(), _no_cursor.cursor(), CurrentTime)))
			return;
}

void sge::xinput::input_system::grab_keyboard()
{
	for(;;)
		if(handle_grab(XGrabKeyboard(wnd->display()->get(), wnd->get_window(), True, GrabModeAsync, GrabModeAsync, CurrentTime)))
			return;
}

bool sge::xinput::input_system::handle_grab(const int r) const
{
	switch(r) {
	case GrabSuccess:
		return true;
	case GrabFrozen:
		throw exception("x11: Grab frozen!");
	case GrabNotViewable:
	case AlreadyGrabbed:
		break;
	case GrabInvalidTime:
		throw exception("x11: GrabInvalidTime");
	}

	sleep(100);
	return false;
}

void sge::xinput::input_system::on_motion_event(const XEvent& xev)
{
	if(use_dga)
		dga_motion(xev);
	else
		warped_motion(xev);
}

void sge::xinput::input_system::on_key_event(const XEvent& xev)
{
	// check for repeated key (thanks to SDL)
	if(xev.type == KeyRelease
	   && xev.type == KeyRelease && XPending(wnd->display()->get()))
	{
		XEvent peek;
		XPeekEvent(wnd->display()->get(), &peek);
		if(peek.type == KeyPress &&
		   peek.xkey.keycode == xev.xkey.keycode &&
		   (peek.xkey.time - xev.xkey.time) < 2)
		{
			XNextEvent(wnd->display()->get(), &peek);
			repeat_sig(create_key_type(xev));
			return;
		}
	}
	
	sig(key_pair(create_key_type(xev), xev.type == KeyRelease ? 0 : 1));
}

sge::key_type sge::xinput::input_system::create_key_type(const XEvent& xev)
{
	XComposeStatus state;
	KeySym ks;
	boost::array<char,32> keybuf;

	const int num_chars = XLookupString(const_cast<XKeyEvent*>(reinterpret_cast<const XKeyEvent*>(&xev)), keybuf.c_array(), keybuf.size(), &ks, &state);
	const char code = keybuf[0];

	if(num_chars > 1)
	{
		std::cerr << "stub: character '" << code << "' in XLookupString has " << num_chars << " bytes!\n";
		return key_type();
	}

	return key_type(get_key_name(ks), get_key_code(ks), code);
}

void sge::xinput::input_system::on_button_event(const XEvent& xev)
{
	sig(key_pair(mouse_key(xev.xbutton.button), xev.type == ButtonRelease ? 0 : 1));
}

void sge::xinput::input_system::on_release(const XEvent&)
{
	enable_dga(false);
	XUngrabPointer(wnd->display()->get(), CurrentTime);
}

void sge::xinput::input_system::on_acquire(const XEvent&)
{
	grab();
	enable_dga(true);
}

void sge::xinput::input_system::enable_dga(const bool 
#ifdef USE_DGA
		enable
#endif
)
{
#ifdef USE_DGA
	if(!use_dga)
		return;
	_dga_guard.enable(enable);
#endif
}

sge::key_type sge::xinput::input_system::mouse_key(const unsigned x11code) const
{
	switch(x11code) {
	case 1:
		return mouse1;
	case 3:
		return mouse2;
	default:
		return undefined_mouse_key;
	}
}

sge::string sge::xinput::input_system::get_key_name(const KeySym ks) const
{
	const char* const name = XKeysymToString(ks);
	return name ? iconv(name) : iconv("unknown");
}

sge::key_code sge::xinput::input_system::get_key_code(const KeySym ks) const
{
	const x11_to_sge_array::const_iterator it = x11tosge.find(ks);
	if(it == x11tosge.end())
		return KC_None;
	return it->second;
}

void sge::xinput::input_system::private_mouse_motion(const mouse_coordinate_t deltax, const mouse_coordinate_t deltay)
{
	if(deltax)
		sig(key_pair(mouse_x, space_unit(deltax) / wnd->width()));
	if(deltay)
		sig(key_pair(mouse_y, space_unit(deltay) / wnd->height()));
}

void sge::xinput::input_system::dga_motion(XEvent xevent)
{
	mouse_coordinate_t dx = xevent.xmotion.x_root,
	                   dy = xevent.xmotion.y_root;

	while(XCheckTypedEvent(wnd->display()->get(), MotionNotify, &xevent))
	{
		dx += xevent.xmotion.x_root;
		dy += xevent.xmotion.y_root;
	}

	private_mouse_motion(dx, dy);
}

// thanks to SDL
void sge::xinput::input_system::warped_motion(XEvent xevent)
{
	const mouse_coordinate_t MOUSE_FUDGE_FACTOR = 8;

	const mouse_coordinate_t w = wnd->width(),
	                         h = wnd->height();
	mouse_coordinate_t deltax = xevent.xmotion.x - mouse_last.x(),
	                   deltay = xevent.xmotion.y - mouse_last.y();
	
	mouse_last.x() = xevent.xmotion.x;
	mouse_last.y() = xevent.xmotion.y;

	private_mouse_motion(deltax, deltay);

	if ( !((xevent.xmotion.x < MOUSE_FUDGE_FACTOR) ||
	     (xevent.xmotion.x > (w-MOUSE_FUDGE_FACTOR)) ||
	     (xevent.xmotion.y < MOUSE_FUDGE_FACTOR) ||
	     (xevent.xmotion.y > (h-MOUSE_FUDGE_FACTOR)) ))
		return;
	
	while ( XCheckTypedEvent(wnd->display()->get(), MotionNotify, &xevent) )
	{
		deltax = xevent.xmotion.x - mouse_last.x();
		deltay = xevent.xmotion.y - mouse_last.y();

		mouse_last.x() = xevent.xmotion.x;
		mouse_last.y() = xevent.xmotion.y;

		private_mouse_motion(deltax, deltay);
	}
	mouse_last.x() = w/2;
	mouse_last.y() = h/2;
	XWarpPointer(wnd->display()->get(), None, wnd->get_window(), 0, 0, 0, 0, mouse_last.x(), mouse_last.y());

	const unsigned max_loops = 10;
	for(unsigned i = 0; i < max_loops; ++i )
	{
		XMaskEvent(wnd->display()->get(), PointerMotionMask, &xevent);
		if ( (xevent.xmotion.x > mouse_last.x() - MOUSE_FUDGE_FACTOR) &&
		     (xevent.xmotion.x < mouse_last.x() + MOUSE_FUDGE_FACTOR) &&
		     (xevent.xmotion.y > mouse_last.y() - MOUSE_FUDGE_FACTOR) &&
		     (xevent.xmotion.y < mouse_last.y() + MOUSE_FUDGE_FACTOR) )
			break;

		if(i == max_loops - 1)
			std::cerr << "warning: didn't detect mouse warp motion! Try to enable dga mouse instead.\n";
	}
}

const sge::key_type sge::xinput::input_system::mouse_x(sge::iconv("mouse_x"), KC_MOUSEX);
const sge::key_type sge::xinput::input_system::mouse_y(sge::iconv("mouse_y"), KC_MOUSEY);
const sge::key_type sge::xinput::input_system::undefined_mouse_key(sge::iconv("undefined mouse key"));
const sge::key_type sge::xinput::input_system::mouse1(sge::iconv("mouse_L"), KC_MOUSEL);
const sge::key_type sge::xinput::input_system::mouse2(sge::iconv("mouse_R"), KC_MOUSER);
