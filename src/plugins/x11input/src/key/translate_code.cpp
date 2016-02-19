/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/input/key/code.hpp>
#include <sge/x11input/key/translate_code.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcppt/config/external_end.hpp>


sge::input::key::code
sge::x11input::key::translate_code(
	KeySym const _sym
)
{
	switch(
		_sym
	)
	{
	case NoSymbol:
		return sge::input::key::code::unlabeled;
	case XK_BackSpace:
		return sge::input::key::code::backspace;
	case XK_Tab:
		return sge::input::key::code::tab;
	case XK_Return:
		return sge::input::key::code::return_;
	case XK_Pause:
		return sge::input::key::code::pause;
	case XK_Scroll_Lock:
		return sge::input::key::code::scroll;
	case XK_Escape:
		return sge::input::key::code::escape;
	case XK_Delete:
		return sge::input::key::code::delete_;
	case XK_Home:
		return sge::input::key::code::home;
	case XK_Left:
		return sge::input::key::code::left;
	case XK_Up:
		return sge::input::key::code::up;
	case XK_Right:
		return sge::input::key::code::right;
	case XK_Down:
		return sge::input::key::code::down;
//	case XK_Prior:
//	case XK_Next:
	case XK_Page_Up:
		return sge::input::key::code::pageup;
	case XK_Page_Down:
		return sge::input::key::code::pagedown;
	case XK_End:
		return sge::input::key::code::end;
//	case XK_Begin:
	//#define XK_Select            0xff60 /* Select:
	case XK_Print:
		return sge::input::key::code::sysrq;
	//#define XK_Execute            0xff62 /* Execute:
	case XK_Insert:
		return sge::input::key::code::insert;
//#define XK_Undo             0xff65
//#define XK_Redo             0xff66 /* Redo:
//		return again */
//#define XK_Menu             0xff67
//#define XK_Find             0xff68 /* Find:
//		return search */
//#define XK_Cancel            0xff69 /* Cancel:
//		return stop:
//#define XK_Help             0xff6a /* Help */
//#define XK_Break             0xff6b
//#define XK_Mode_switch          0xff7e /* Character set switch */
//#define XK_script_switch         0xff7e /* Alias for mode_switch */
	case XK_Num_Lock:
		return sge::input::key::code::num_lock;

//	case XK_KP_Space:
//	case XK_KP_Tab];
	case XK_KP_Enter:
		return sge::input::key::code::num_enter;
/*	case XK_KP_F1];
	case XK_KP_F2];
	case XK_KP_F3];
	case XK_KP_F4];
	case XK_KP_Home:
		return sge::input::key::code::NUM_HOME;
	case XK_KP_Left:
		return sge::input::key::code::NUM_LEFT;
	case XK_KP_Up:
		return sge::input::key::code::NUM_UP;
#define XK_KP_Right           0xff98
#define XK_KP_Down            0xff99
#define XK_KP_Prior           0xff9a
#define XK_KP_Page_Up          0xff9a
#define XK_KP_Next            0xff9b
#define XK_KP_Page_Down         0xff9b
#define XK_KP_End            0xff9c
#define XK_KP_Begin           0xff9d
#define XK_KP_Insert           0xff9e
#define XK_KP_Delete           0xff9f
*/
	case XK_KP_Equal:
		return sge::input::key::code::num_equals;
/*
#define XK_KP_Multiply          0xffaa
#define XK_KP_Add            0xffab
#define XK_KP_Separator         0xffac
#define XK_KP_Subtract          0xffad
#define XK_KP_Decimal          0xffae
#define XK_KP_Divide           0xffaf
*/
	case XK_KP_0:
		return sge::input::key::code::num_0;
	case XK_KP_1:
		return sge::input::key::code::num_1;
	case XK_KP_2:
		return sge::input::key::code::num_2;
	case XK_KP_3:
		return sge::input::key::code::num_3;
	case XK_KP_4:
		return sge::input::key::code::num_4;
	case XK_KP_5:
		return sge::input::key::code::num_5;
	case XK_KP_6:
		return sge::input::key::code::num_6;
	case XK_KP_7:
		return sge::input::key::code::num_7;
	case XK_KP_8:
		return sge::input::key::code::num_8;
	case XK_KP_9:
		return sge::input::key::code::num_9;
	case XK_F1:
		return sge::input::key::code::f1;
	case XK_F2:
		return sge::input::key::code::f2;
	case XK_F3:
		return sge::input::key::code::f3;
	case XK_F4:
		return sge::input::key::code::f4;
	case XK_F5:
		return sge::input::key::code::f5;
	case XK_F6:
		return sge::input::key::code::f6;
	case XK_F7:
		return sge::input::key::code::f7;
	case XK_F8:
		return sge::input::key::code::f8;
	case XK_F9:
		return sge::input::key::code::f9;
	case XK_F10:
		return sge::input::key::code::f10;
	case XK_F11:
		return sge::input::key::code::f11;
	case XK_F12:
		return sge::input::key::code::f12;
	case XK_F13:
		return sge::input::key::code::f13;
	case XK_F14:
		return sge::input::key::code::f14;
	case XK_F15:
		return sge::input::key::code::f15;
//#define XK_L1              0xffc8
/*
#define XK_L2              0xffc9
#define XK_L3              0xffca
#define XK_L4              0xffcb
#define XK_L5              0xffcc
#define XK_F16              0xffcd
#define XK_L6              0xffcd
#define XK_F17              0xffce
#define XK_L7              0xffce
#define XK_F18              0xffcf
#define XK_L8              0xffcf
#define XK_F19              0xffd0
#define XK_L9              0xffd0
#define XK_F20              0xffd1
#define XK_L10              0xffd1
#define XK_F21              0xffd2
#define XK_R1              0xffd2
#define XK_F22              0xffd3
#define XK_R2              0xffd3
#define XK_F23              0xffd4
#define XK_R3              0xffd4
#define XK_F24              0xffd5
#define XK_R4              0xffd5
#define XK_F25              0xffd6
#define XK_R5              0xffd6
#define XK_F26              0xffd7
#define XK_R6              0xffd7
#define XK_F27              0xffd8
#define XK_R7              0xffd8
#define XK_F28              0xffd9
#define XK_R8              0xffd9
#define XK_F29              0xffda
#define XK_R9              0xffda
#define XK_F30              0xffdb
#define XK_R10              0xffdb
#define XK_F31              0xffdc
#define XK_R11              0xffdc
#define XK_F32              0xffdd
#define XK_R12              0xffdd
#define XK_F33              0xffde
#define XK_R13              0xffde
#define XK_F34              0xffdf
#define XK_R14              0xffdf
#define XK_F35              0xffe0
#define XK_R15              0xffe0
*/


	case XK_Shift_L:
		return sge::input::key::code::left_shift;
	case XK_Shift_R:
		return sge::input::key::code::right_shift;
	case XK_Control_L:
		return sge::input::key::code::left_control;
	case XK_Control_R:
		return sge::input::key::code::right_control;
	case XK_Caps_Lock:
		return sge::input::key::code::capital;
//	case XK_Shift_Lock:
//		return sge::input::key::code::LSHIFT; // ???

//#define XK_Meta_L            0xffe7 /* Left meta */
//#define XK_Meta_R            0xffe8 /* Right meta */
//#define XK_Alt_L             0xffe9 /* Left alt */
//#define XK_Alt_R             0xffea /* Right alt */
	case XK_Alt_L:
		return sge::input::key::code::left_alt;
	case XK_Alt_R:
		return sge::input::key::code::right_alt;
	case XK_Super_L:
		return sge::input::key::code::left_win;
	case XK_Super_R:
		return sge::input::key::code::right_win;
//#define XK_Hyper_L            0xffed /* Left hyper */
//#define XK_Hyper_R            0xffee /* Right hyper */
#if 0
#define XK_ISO_Lock           0xfe01
#define XK_ISO_Level2_Latch       0xfe02
#define XK_ISO_Level3_Shift       0xfe03
#define XK_ISO_Level3_Latch       0xfe04
#define XK_ISO_Level3_Lock        0xfe05
#define XK_ISO_Level5_Shift       0xfe11
#define XK_ISO_Level5_Latch       0xfe12
#define XK_ISO_Level5_Lock        0xfe13
#define XK_ISO_Group_Shift        0xff7e /* Alias for mode_switch */
#define XK_ISO_Group_Latch        0xfe06
#define XK_ISO_Group_Lock        0xfe07
#define XK_ISO_Next_Group        0xfe08
#define XK_ISO_Next_Group_Lock      0xfe09
#define XK_ISO_Prev_Group        0xfe0a
#define XK_ISO_Prev_Group_Lock      0xfe0b
#define XK_ISO_First_Group        0xfe0c
#define XK_ISO_First_Group_Lock     0xfe0d
#define XK_ISO_Last_Group        0xfe0e
#define XK_ISO_Last_Group_Lock      0xfe0f

#define XK_ISO_Left_Tab         0xfe20
#define XK_ISO_Move_Line_Up       0xfe21
#define XK_ISO_Move_Line_Down      0xfe22
#define XK_ISO_Partial_Line_Up      0xfe23
#define XK_ISO_Partial_Line_Down     0xfe24
#define XK_ISO_Partial_Space_Left    0xfe25
#define XK_ISO_Partial_Space_Right    0xfe26
#define XK_ISO_Set_Margin_Left      0xfe27
#define XK_ISO_Set_Margin_Right     0xfe28
#define XK_ISO_Release_Margin_Left    0xfe29
#define XK_ISO_Release_Margin_Right   0xfe2a
#define XK_ISO_Release_Both_Margins   0xfe2b
#define XK_ISO_Fast_Cursor_Left     0xfe2c
#define XK_ISO_Fast_Cursor_Right     0xfe2d
#define XK_ISO_Fast_Cursor_Up      0xfe2e
#define XK_ISO_Fast_Cursor_Down     0xfe2f
#define XK_ISO_Continuous_Underline   0xfe30
#define XK_ISO_Discontinuous_Underline  0xfe31
#define XK_ISO_Emphasize         0xfe32
#define XK_ISO_Center_Object       0xfe33
#define XK_ISO_Enter           0xfe34

#define XK_dead_grave          0xfe50
#define XK_dead_acute          0xfe51
#define XK_dead_circumflex        0xfe52
#define XK_dead_tilde          0xfe53
#define XK_dead_macron          0xfe54
#define XK_dead_breve          0xfe55
#define XK_dead_abovedot         0xfe56
#define XK_dead_diaeresis        0xfe57
#define XK_dead_abovering        0xfe58
#define XK_dead_doubleacute       0xfe59
#define XK_dead_caron          0xfe5a
#define XK_dead_cedilla         0xfe5b
#define XK_dead_ogonek          0xfe5c
#define XK_dead_iota           0xfe5d
#define XK_dead_voiced_sound       0xfe5e
#define XK_dead_semivoiced_sound     0xfe5f
#define XK_dead_belowdot         0xfe60
#define XK_dead_hook           0xfe61
#define XK_dead_horn           0xfe62
#define XK_dead_stroke          0xfe63

#define XK_First_Virtual_Screen     0xfed0
#define XK_Prev_Virtual_Screen      0xfed1
#define XK_Next_Virtual_Screen      0xfed2
#define XK_Last_Virtual_Screen      0xfed4
#define XK_Terminate_Server       0xfed5

#define XK_AccessX_Enable        0xfe70
#define XK_AccessX_Feedback_Enable    0xfe71
#define XK_RepeatKeys_Enable       0xfe72
#define XK_SlowKeys_Enable        0xfe73
#define XK_BounceKeys_Enable       0xfe74
#define XK_StickyKeys_Enable       0xfe75
#define XK_MouseKeys_Enable       0xfe76
#define XK_MouseKeys_Accel_Enable    0xfe77
#define XK_Overlay1_Enable        0xfe78
#define XK_Overlay2_Enable        0xfe79
#define XK_AudibleBell_Enable      0xfe7a

#define XK_Pointer_Left         0xfee0
#define XK_Pointer_Right         0xfee1
#define XK_Pointer_Up          0xfee2
#define XK_Pointer_Down         0xfee3
#define XK_Pointer_UpLeft        0xfee4
#define XK_Pointer_UpRight        0xfee5
#define XK_Pointer_DownLeft       0xfee6
#define XK_Pointer_DownRight       0xfee7
#define XK_Pointer_Button_Dflt      0xfee8
#define XK_Pointer_Button1        0xfee9
#define XK_Pointer_Button2        0xfeea
#define XK_Pointer_Button3        0xfeeb
#define XK_Pointer_Button4        0xfeec
#define XK_Pointer_Button5        0xfeed
#define XK_Pointer_DblClick_Dflt     0xfeee
#define XK_Pointer_DblClick1       0xfeef
#define XK_Pointer_DblClick2       0xfef0
#define XK_Pointer_DblClick3       0xfef1
#define XK_Pointer_DblClick4       0xfef2
#define XK_Pointer_DblClick5       0xfef3
#define XK_Pointer_Drag_Dflt       0xfef4
#define XK_Pointer_Drag1         0xfef5
#define XK_Pointer_Drag2         0xfef6
#define XK_Pointer_Drag3         0xfef7
#define XK_Pointer_Drag4         0xfef8
#define XK_Pointer_Drag5         0xfefd

#define XK_Pointer_EnableKeys      0xfef9
#define XK_Pointer_Accelerate      0xfefa
#define XK_Pointer_DfltBtnNext      0xfefb
#define XK_Pointer_DfltBtnPrev      0xfefc

#define XK_3270_Duplicate        0xfd01
#define XK_3270_FieldMark        0xfd02
#define XK_3270_Right2          0xfd03
#define XK_3270_Left2          0xfd04
#define XK_3270_BackTab         0xfd05
#define XK_3270_EraseEOF         0xfd06
#define XK_3270_EraseInput        0xfd07
#define XK_3270_Reset          0xfd08
#define XK_3270_Quit           0xfd09
#define XK_3270_PA1           0xfd0a
#define XK_3270_PA2           0xfd0b
#define XK_3270_PA3           0xfd0c
#define XK_3270_Test           0xfd0d
#define XK_3270_Attn           0xfd0e
#define XK_3270_CursorBlink       0xfd0f
#define XK_3270_AltCursor        0xfd10
#define XK_3270_KeyClick         0xfd11
#define XK_3270_Jump           0xfd12
#define XK_3270_Ident          0xfd13
#define XK_3270_Rule           0xfd14
#define XK_3270_Copy           0xfd15
#define XK_3270_Play           0xfd16
#define XK_3270_Setup          0xfd17
#define XK_3270_Record          0xfd18
#define XK_3270_ChangeScreen       0xfd19
#define XK_3270_DeleteWord        0xfd1a
#define XK_3270_ExSelect         0xfd1b
#define XK_3270_CursorSelect       0xfd1c
#define XK_3270_PrintScreen       0xfd1d
#define XK_3270_Enter          0xfd1e
#endif

	case XK_space:
		return sge::input::key::code::space;
#if 0
#define XK_exclam            0x0021 /* U+0021 EXCLAMATION MARK */
#define XK_quotedbl           0x0022 /* U+0022 QUOTATION MARK */
#define XK_numbersign          0x0023 /* U+0023 NUMBER SIGN */
#define XK_dollar            0x0024 /* U+0024 DOLLAR SIGN */
#define XK_percent            0x0025 /* U+0025 PERCENT SIGN */
#define XK_ampersand           0x0026 /* U+0026 AMPERSAND */
#define XK_apostrophe          0x0027 /* U+0027 APOSTROPHE */
#define XK_quoteright          0x0027 /* deprecated */
#define XK_parenleft           0x0028 /* U+0028 LEFT PARENTHESIS */
#define XK_parenright          0x0029 /* U+0029 RIGHT PARENTHESIS */
#define XK_asterisk           0x002a /* U+002A ASTERISK */
#endif
	case XK_plus:
		return sge::input::key::code::add;
	case XK_comma:
		return sge::input::key::code::comma;
	case XK_minus:
		return sge::input::key::code::minus;
	case XK_period:
		return sge::input::key::code::period;
	case XK_slash:
		return sge::input::key::code::slash;
	case XK_0:
		return sge::input::key::code::_0;
	case XK_1:
		return sge::input::key::code::_1;
	case XK_2:
		return sge::input::key::code::_2;
	case XK_3:
		return sge::input::key::code::_3;
	case XK_4:
		return sge::input::key::code::_4;
	case XK_5:
		return sge::input::key::code::_5;
	case XK_6:
		return sge::input::key::code::_6;
	case XK_7:
		return sge::input::key::code::_7;
	case XK_8:
		return sge::input::key::code::_8;
	case XK_9:
		return sge::input::key::code::_9;
#if 0
#define XK_colon             0x003a /* U+003A COLON */
#define XK_semicolon           0x003b /* U+003B SEMICOLON */
#define XK_less             0x003c /* U+003C LESS-THAN SIGN */
#define XK_greater            0x003e /* U+003E GREATER-THAN SIGN */
#define XK_question           0x003f /* U+003F QUESTION MARK */
#define XK_at              0x0040 /* U+0040 COMMERCIAL AT */
#endif
	case XK_equal:
		return sge::input::key::code::equals;
	case XK_A:
		return sge::input::key::code::a;
	case XK_B:
		return sge::input::key::code::b;
	case XK_C:
		return sge::input::key::code::c;
	case XK_D:
		return sge::input::key::code::d;
	case XK_E:
		return sge::input::key::code::e;
	case XK_F:
		return sge::input::key::code::f;
	case XK_G:
		return sge::input::key::code::g;
	case XK_H:
		return sge::input::key::code::h;
	case XK_I:
		return sge::input::key::code::i;
	case XK_J:
		return sge::input::key::code::j;
	case XK_K:
		return sge::input::key::code::k;
	case XK_L:
		return sge::input::key::code::l;
	case XK_M:
		return sge::input::key::code::m;
	case XK_N:
		return sge::input::key::code::n;
	case XK_O:
		return sge::input::key::code::o;
	case XK_P:
		return sge::input::key::code::p;
	case XK_Q:
		return sge::input::key::code::q;
	case XK_R:
		return sge::input::key::code::r;
	case XK_S:
		return sge::input::key::code::s;
	case XK_T:
		return sge::input::key::code::t;
	case XK_U:
		return sge::input::key::code::u;
	case XK_V:
		return sge::input::key::code::v;
	case XK_W:
		return sge::input::key::code::w;
	case XK_X:
		return sge::input::key::code::x;
	case XK_Y:
		return sge::input::key::code::y;
	case XK_Z:
		return sge::input::key::code::z;

	case XK_bracketleft:
		return sge::input::key::code::left_bracket;
	case XK_backslash:
		return sge::input::key::code::backslash;
	case XK_bracketright:
		return sge::input::key::code::right_bracket;
	case XK_asciicircum:
		return sge::input::key::code::circumflex;
	case XK_underscore:
		return sge::input::key::code::underline;
	case XK_grave:
		return sge::input::key::code::grave;
//#define XK_quoteleft           0x0060 /* deprecated */

	case XK_a:
		return sge::input::key::code::a;
	case XK_b:
		return sge::input::key::code::b;
	case XK_c:
		return sge::input::key::code::c;
	case XK_d:
		return sge::input::key::code::d;
	case XK_e:
		return sge::input::key::code::e;
	case XK_f:
		return sge::input::key::code::f;
	case XK_g:
		return sge::input::key::code::g;
	case XK_h:
		return sge::input::key::code::h;
	case XK_i:
		return sge::input::key::code::i;
	case XK_j:
		return sge::input::key::code::j;
	case XK_k:
		return sge::input::key::code::k;
	case XK_l:
		return sge::input::key::code::l;
	case XK_m:
		return sge::input::key::code::m;
	case XK_n:
		return sge::input::key::code::n;
	case XK_o:
		return sge::input::key::code::o;
	case XK_p:
		return sge::input::key::code::p;
	case XK_q:
		return sge::input::key::code::q;
	case XK_r:
		return sge::input::key::code::r;
	case XK_s:
		return sge::input::key::code::s;
	case XK_t:
		return sge::input::key::code::t;
	case XK_u:
		return sge::input::key::code::u;
	case XK_v:
		return sge::input::key::code::v;
	case XK_w:
		return sge::input::key::code::w;
	case XK_x:
		return sge::input::key::code::x;
	case XK_y:
		return sge::input::key::code::y;
	case XK_z:
		return sge::input::key::code::z;
	}

	return sge::input::key::code::unknown;
#if 0
#define XK_braceleft                     0x007b  /* U+007B LEFT CURLY BRACKET */
#define XK_bar                           0x007c  /* U+007C VERTICAL LINE */
#define XK_braceright                    0x007d  /* U+007D RIGHT CURLY BRACKET */
#define XK_asciitilde                    0x007e  /* U+007E TILDE */
#endif
}
