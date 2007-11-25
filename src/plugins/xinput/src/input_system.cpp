/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
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
#include "../pointer.hpp"
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
		mouse_last = get_mouse_pos(wnd->display(), wnd);
	
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

	x11tosge[NoSymbol] = kc::none;
	x11tosge[XK_BackSpace] = kc::key_backspace;
	x11tosge[XK_Tab] = kc::key_tab;
	x11tosge[XK_Return] = kc::key_return;
	x11tosge[XK_Pause] = kc::key_pause;
	x11tosge[XK_Scroll_Lock] = kc::key_scroll;
	x11tosge[XK_Escape] = kc::key_escape;
	x11tosge[XK_Delete] = kc::key_delete;

	x11tosge[XK_Home] = kc::key_home;
	x11tosge[XK_Left] = kc::key_left;
	x11tosge[XK_Up]   = kc::key_up;
	x11tosge[XK_Right] = kc::key_right;
	x11tosge[XK_Down] = kc::key_down;
	//XK_Prior
	x11tosge[XK_Page_Up] = kc::key_pageup;
	//XK_Next
	x11tosge[XK_Page_Down] = kc::key_pagedown;
	x11tosge[XK_End] = kc::key_end;
//	x11tosge[XK_Begin] = kc::key_home;

	//#define XK_Select                        0xff60  /* Select, mark */
	//#define XK_Print                         0xff61
	//#define XK_Execute                       0xff62  /* Execute, run, do */
	x11tosge[XK_Insert] = kc::key_insert;
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

//	x11tosge[XK_KP_Space] = kc::key_SPACE;
//	x11tosge[XK_KP_Tab];
//	x11tosge[XK_KP_Enter] = kc::key_ENTER;
/*	x11tosge[XK_KP_F1];
	x11tosge[XK_KP_F2];
	x11tosge[XK_KP_F3];
	x11tosge[XK_KP_F4];
	x11tosge[XK_KP_Home] = kc::key_NUM_HOME;
	x11tosge[XK_KP_Left] = kc::key_NUM_LEFT;
	x11tosge[XK_KP_Up] = kc::key_NUM_UP;
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

	x11tosge[XK_F1] = kc::key_f1;
	x11tosge[XK_F2] = kc::key_f2;
	x11tosge[XK_F3] = kc::key_f3;
	x11tosge[XK_F4] = kc::key_f4;
	x11tosge[XK_F5] = kc::key_f5;
	x11tosge[XK_F6] = kc::key_f6;
	x11tosge[XK_F7] = kc::key_f7;
	x11tosge[XK_F8] = kc::key_f8;
	x11tosge[XK_F9] = kc::key_f9;
	x11tosge[XK_F10] = kc::key_f10;
	x11tosge[XK_F11] = kc::key_f11;
	x11tosge[XK_F12] = kc::key_f12;
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


	x11tosge[XK_Shift_L] = kc::key_lshift;
	x11tosge[XK_Shift_R] = kc::key_rshift;
	x11tosge[XK_Control_L] = kc::key_lctrl;
	x11tosge[XK_Control_R] = kc::key_rctrl;
	//XK_Caps_Lock
//	x11tosge[XK_Shift_Lock] = kc::key_LSHIFT; // ???

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

	x11tosge[XK_space] = kc::key_space;
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
#endif
	x11tosge[XK_0] = kc::key_0;
	x11tosge[XK_1] = kc::key_1;
	x11tosge[XK_2] = kc::key_2;
	x11tosge[XK_3] = kc::key_3;
	x11tosge[XK_4] = kc::key_4;
	x11tosge[XK_5] = kc::key_5;
	x11tosge[XK_6] = kc::key_6;
	x11tosge[XK_7] = kc::key_7;
	x11tosge[XK_8] = kc::key_8;
	x11tosge[XK_9] = kc::key_9;
#if 0
#define XK_colon                         0x003a  /* U+003A COLON */
#define XK_semicolon                     0x003b  /* U+003B SEMICOLON */
#define XK_less                          0x003c  /* U+003C LESS-THAN SIGN */
#define XK_equal                         0x003d  /* U+003D EQUALS SIGN */
#define XK_greater                       0x003e  /* U+003E GREATER-THAN SIGN */
#define XK_question                      0x003f  /* U+003F QUESTION MARK */
#define XK_at                            0x0040  /* U+0040 COMMERCIAL AT */
#endif
	x11tosge[XK_A] = kc::key_a;
	x11tosge[XK_B] = kc::key_b;
	x11tosge[XK_C] = kc::key_c;
	x11tosge[XK_D] = kc::key_d;
	x11tosge[XK_E] = kc::key_e;
	x11tosge[XK_F] = kc::key_f;
	x11tosge[XK_G] = kc::key_g;
	x11tosge[XK_H] = kc::key_h;
	x11tosge[XK_I] = kc::key_i;
	x11tosge[XK_J] = kc::key_j;
	x11tosge[XK_K] = kc::key_k;
	x11tosge[XK_L] = kc::key_l;
	x11tosge[XK_M] = kc::key_m;
	x11tosge[XK_N] = kc::key_n;
	x11tosge[XK_O] = kc::key_o;
	x11tosge[XK_P] = kc::key_p;
	x11tosge[XK_Q] = kc::key_q;
	x11tosge[XK_R] = kc::key_r;
	x11tosge[XK_S] = kc::key_s;
	x11tosge[XK_T] = kc::key_t;
	x11tosge[XK_U] = kc::key_u;
	x11tosge[XK_V] = kc::key_v;
	x11tosge[XK_W] = kc::key_w;
	x11tosge[XK_X] = kc::key_x;
	x11tosge[XK_Y] = kc::key_y;
	x11tosge[XK_Z] = kc::key_z;

	x11tosge[XK_bracketleft] = kc::key_lbracket;
	x11tosge[XK_backslash] = kc::key_backslash;
	x11tosge[XK_bracketright] = kc::key_rbracket;
//#define XK_asciicircum                   0x005e  /* U+005E CIRCUMFLEX ACCENT */
	x11tosge[XK_underscore] = kc::key_underline;
	x11tosge[XK_grave] = kc::key_grave;
//#define XK_quoteleft                     0x0060  /* deprecated */
	
	x11tosge[XK_a] = kc::key_a;
	x11tosge[XK_b] = kc::key_b;
	x11tosge[XK_c] = kc::key_c;
	x11tosge[XK_d] = kc::key_d;
	x11tosge[XK_e] = kc::key_e;
	x11tosge[XK_f] = kc::key_f;
	x11tosge[XK_g] = kc::key_g;
	x11tosge[XK_h] = kc::key_h;
	x11tosge[XK_i] = kc::key_i;
	x11tosge[XK_j] = kc::key_j;
	x11tosge[XK_k] = kc::key_k;
	x11tosge[XK_l] = kc::key_l;
	x11tosge[XK_m] = kc::key_m;
	x11tosge[XK_n] = kc::key_n;
	x11tosge[XK_o] = kc::key_o;
	x11tosge[XK_p] = kc::key_p;
	x11tosge[XK_q] = kc::key_q;
	x11tosge[XK_r] = kc::key_r;
	x11tosge[XK_s] = kc::key_s;
	x11tosge[XK_t] = kc::key_t;
	x11tosge[XK_u] = kc::key_u;
	x11tosge[XK_v] = kc::key_v;
	x11tosge[XK_w] = kc::key_w;
	x11tosge[XK_x] = kc::key_x;
	x11tosge[XK_y] = kc::key_y;
	x11tosge[XK_z] = kc::key_z;

#if 0
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

sge::callback_connection sge::xinput::input_system::register_callback(const callback& c)
{
	return sig.connect(c);
}

sge::callback_connection sge::xinput::input_system::register_repeat_callback(const repeat_callback& c)
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

sge::key_type::string sge::xinput::input_system::get_key_name(const KeySym ks) const
{
	const char* const name = XKeysymToString(ks);
	return name ? iconv(name) : iconv("unknown");
}

sge::key_code sge::xinput::input_system::get_key_code(const KeySym ks) const
{
	const x11_to_sge_array::const_iterator it = x11tosge.find(ks);
	if(it == x11tosge.end())
		return kc::none;
	return it->second;
}

void sge::xinput::input_system::private_mouse_motion(const mouse_coordinate_t deltax, const mouse_coordinate_t deltay)
{
	if(deltax)
		sig(key_pair(mouse_x, deltax));
	if(deltay)
		sig(key_pair(mouse_y, deltay));
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

const sge::key_type sge::xinput::input_system::mouse_x(iconv("mouse_x"), kc::mouse_axis_x);
const sge::key_type sge::xinput::input_system::mouse_y(iconv("mouse_y"), kc::mouse_axis_y);
const sge::key_type sge::xinput::input_system::undefined_mouse_key(iconv("undefined mouse key"));
const sge::key_type sge::xinput::input_system::mouse1(iconv("mouse_L"), kc::mouse_l);
const sge::key_type sge::xinput::input_system::mouse2(iconv("mouse_R"), kc::mouse_r);
