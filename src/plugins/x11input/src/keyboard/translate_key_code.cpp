/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/x11input/keyboard/translate_key_code.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/keysym.h>
#include <boost/assign/list_of.hpp>
#include <map>
#include <fcppt/config/external_end.hpp>

namespace
{

typedef std::map<
	KeySym,
	sge::input::keyboard::key_code::type
> x11_to_sge_map;

x11_to_sge_map const x11_to_sge = boost::assign::map_list_of
	(NoSymbol, sge::input::keyboard::key_code::unknown)
	(XK_BackSpace, sge::input::keyboard::key_code::backspace)
	(XK_Tab, sge::input::keyboard::key_code::tab)
	(XK_Return, sge::input::keyboard::key_code::return_)
	(XK_Pause, sge::input::keyboard::key_code::pause)
	(XK_Scroll_Lock, sge::input::keyboard::key_code::scroll)
	(XK_Escape, sge::input::keyboard::key_code::escape)
	(XK_Delete, sge::input::keyboard::key_code::delete_)

	(XK_Home, sge::input::keyboard::key_code::home)
	(XK_Left, sge::input::keyboard::key_code::left)
	(XK_Up, sge::input::keyboard::key_code::up)
	(XK_Right, sge::input::keyboard::key_code::right)
	(XK_Down, sge::input::keyboard::key_code::down)
	//XK_Prior
	(XK_Page_Up, sge::input::keyboard::key_code::pageup)
	//XK_Next
	(XK_Page_Down, sge::input::keyboard::key_code::pagedown)
	(XK_End, sge::input::keyboard::key_code::end)
//	(XK_Begin, sge::input::keyboard::key_code::home)

	//#define XK_Select                        0xff60  /* Select, mark */
	(XK_Print, sge::input::keyboard::key_code::print)
	//#define XK_Execute                       0xff62  /* Execute, run, do */
	(XK_Insert, sge::input::keyboard::key_code::insert)
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

//	(XK_KP_Space, sge::input::keyboard::key_code::SPACE)
//	(XK_KP_Tab])
//	(XK_KP_Enter, sge::input::keyboard::key_code::ENTER)
/*	(XK_KP_F1])
	(XK_KP_F2])
	(XK_KP_F3])
	(XK_KP_F4])
	(XK_KP_Home, sge::input::keyboard::key_code::NUM_HOME)
	(XK_KP_Left, sge::input::keyboard::key_code::NUM_LEFT)
	(XK_KP_Up, sge::input::keyboard::key_code::NUM_UP)
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

	(XK_F1, sge::input::keyboard::key_code::f1)
	(XK_F2, sge::input::keyboard::key_code::f2)
	(XK_F3, sge::input::keyboard::key_code::f3)
	(XK_F4, sge::input::keyboard::key_code::f4)
	(XK_F5, sge::input::keyboard::key_code::f5)
	(XK_F6, sge::input::keyboard::key_code::f6)
	(XK_F7, sge::input::keyboard::key_code::f7)
	(XK_F8, sge::input::keyboard::key_code::f8)
	(XK_F9, sge::input::keyboard::key_code::f9)
	(XK_F10, sge::input::keyboard::key_code::f10)
	(XK_F11, sge::input::keyboard::key_code::f11)
	(XK_F12, sge::input::keyboard::key_code::f12)
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


	(XK_Shift_L, sge::input::keyboard::key_code::lshift)
	(XK_Shift_R, sge::input::keyboard::key_code::rshift)
	(XK_Control_L, sge::input::keyboard::key_code::lctrl)
	(XK_Control_R, sge::input::keyboard::key_code::rctrl)
	//XK_Caps_Lock
//	(XK_Shift_Lock, sge::input::keyboard::key_code::LSHIFT) // ???

//#define XK_Meta_L                        0xffe7  /* Left meta */
//#define XK_Meta_R                        0xffe8  /* Right meta */
#define XK_Alt_L                         0xffe9  /* Left alt */
#define XK_Alt_R                         0xffea  /* Right alt */
	(XK_Alt_L, sge::input::keyboard::key_code::alt)
	(XK_Alt_R, sge::input::keyboard::key_code::altgr)
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

	(XK_space, sge::input::keyboard::key_code::space)
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
	(XK_0, sge::input::keyboard::key_code::_0)
	(XK_1, sge::input::keyboard::key_code::_1)
	(XK_2, sge::input::keyboard::key_code::_2)
	(XK_3, sge::input::keyboard::key_code::_3)
	(XK_4, sge::input::keyboard::key_code::_4)
	(XK_5, sge::input::keyboard::key_code::_5)
	(XK_6, sge::input::keyboard::key_code::_6)
	(XK_7, sge::input::keyboard::key_code::_7)
	(XK_8, sge::input::keyboard::key_code::_8)
	(XK_9, sge::input::keyboard::key_code::_9)
#if 0
#define XK_colon                         0x003a  /* U+003A COLON */
#define XK_semicolon                     0x003b  /* U+003B SEMICOLON */
#define XK_less                          0x003c  /* U+003C LESS-THAN SIGN */
#define XK_equal                         0x003d  /* U+003D EQUALS SIGN */
#define XK_greater                       0x003e  /* U+003E GREATER-THAN SIGN */
#define XK_question                      0x003f  /* U+003F QUESTION MARK */
#define XK_at                            0x0040  /* U+0040 COMMERCIAL AT */
#endif
	(XK_A, sge::input::keyboard::key_code::a)
	(XK_B, sge::input::keyboard::key_code::b)
	(XK_C, sge::input::keyboard::key_code::c)
	(XK_D, sge::input::keyboard::key_code::d)
	(XK_E, sge::input::keyboard::key_code::e)
	(XK_F, sge::input::keyboard::key_code::f)
	(XK_G, sge::input::keyboard::key_code::g)
	(XK_H, sge::input::keyboard::key_code::h)
	(XK_I, sge::input::keyboard::key_code::i)
	(XK_J, sge::input::keyboard::key_code::j)
	(XK_K, sge::input::keyboard::key_code::k)
	(XK_L, sge::input::keyboard::key_code::l)
	(XK_M, sge::input::keyboard::key_code::m)
	(XK_N, sge::input::keyboard::key_code::n)
	(XK_O, sge::input::keyboard::key_code::o)
	(XK_P, sge::input::keyboard::key_code::p)
	(XK_Q, sge::input::keyboard::key_code::q)
	(XK_R, sge::input::keyboard::key_code::r)
	(XK_S, sge::input::keyboard::key_code::s)
	(XK_T, sge::input::keyboard::key_code::t)
	(XK_U, sge::input::keyboard::key_code::u)
	(XK_V, sge::input::keyboard::key_code::v)
	(XK_W, sge::input::keyboard::key_code::w)
	(XK_X, sge::input::keyboard::key_code::x)
	(XK_Y, sge::input::keyboard::key_code::y)
	(XK_Z, sge::input::keyboard::key_code::z)

	(XK_bracketleft, sge::input::keyboard::key_code::lbracket)
	(XK_backslash, sge::input::keyboard::key_code::backslash)
	(XK_bracketright, sge::input::keyboard::key_code::rbracket)
//#define XK_asciicircum                   0x005e  /* U+005E CIRCUMFLEX ACCENT */
	(XK_underscore, sge::input::keyboard::key_code::underline)
	(XK_grave, sge::input::keyboard::key_code::grave)
//#define XK_quoteleft                     0x0060  /* deprecated */

	(XK_a, sge::input::keyboard::key_code::a)
	(XK_b, sge::input::keyboard::key_code::b)
	(XK_c, sge::input::keyboard::key_code::c)
	(XK_d, sge::input::keyboard::key_code::d)
	(XK_e, sge::input::keyboard::key_code::e)
	(XK_f, sge::input::keyboard::key_code::f)
	(XK_g, sge::input::keyboard::key_code::g)
	(XK_h, sge::input::keyboard::key_code::h)
	(XK_i, sge::input::keyboard::key_code::i)
	(XK_j, sge::input::keyboard::key_code::j)
	(XK_k, sge::input::keyboard::key_code::k)
	(XK_l, sge::input::keyboard::key_code::l)
	(XK_m, sge::input::keyboard::key_code::m)
	(XK_n, sge::input::keyboard::key_code::n)
	(XK_o, sge::input::keyboard::key_code::o)
	(XK_p, sge::input::keyboard::key_code::p)
	(XK_q, sge::input::keyboard::key_code::q)
	(XK_r, sge::input::keyboard::key_code::r)
	(XK_s, sge::input::keyboard::key_code::s)
	(XK_t, sge::input::keyboard::key_code::t)
	(XK_u, sge::input::keyboard::key_code::u)
	(XK_v, sge::input::keyboard::key_code::v)
	(XK_w, sge::input::keyboard::key_code::w)
	(XK_x, sge::input::keyboard::key_code::x)
	(XK_y, sge::input::keyboard::key_code::y)
	(XK_z, sge::input::keyboard::key_code::z);

#if 0
#define XK_braceleft                     0x007b  /* U+007B LEFT CURLY BRACKET */
#define XK_bar                           0x007c  /* U+007C VERTICAL LINE */
#define XK_braceright                    0x007d  /* U+007D RIGHT CURLY BRACKET */
#define XK_asciitilde                    0x007e  /* U+007E TILDE */
#endif

}

sge::input::keyboard::key_code::type
sge::x11input::keyboard::translate_key_code(
	KeySym const _sym
)
{
	x11_to_sge_map::const_iterator const it(
		x11_to_sge.find(
			_sym
		)
	);

	return
		it == x11_to_sge.end()
		?
			input::keyboard::key_code::unknown
		:
			it->second;
}
