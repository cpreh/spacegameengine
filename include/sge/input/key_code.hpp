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


#ifndef SGE_INPUT_KEY_CODE_HPP_INCLUDED
#define SGE_INPUT_KEY_CODE_HPP_INCLUDED

namespace sge
{
namespace input
{

namespace kc
{

enum type {
	input_type_mask          = 0xf000U,
	input_keyid_mask         = 0x0fffU,

	input_type_keyboard      = 0x1000U,
	input_type_mouse_key     = 0x2000U,
	input_type_mouse_axis    = 0x3000U,
	input_type_joystick_key  = 0x4000U,
	input_type_joystick_axis = 0x5000U,

	none                     = 0x0000U,



	////////////////////////////////////////////////////////////////////////////
	// Keyboard codes
	//

	key_escape               = input_type_keyboard,
	key_return,
	key_lshift,
	key_rshift,
	key_tab,
	key_backspace,
	key_lctrl,
	key_rctrl,
	key_alt,
	key_altgr,
	key_space,
	key_insert,
	key_home,
	key_pageup,
	key_delete,
	key_end,
	key_pagedown,
	key_left,
	key_right,
	key_up,
	key_down,
	key_a,
	key_b,
	key_c,
	key_d,
	key_e,
	key_f,
	key_g,
	key_h,
	key_i,
	key_j,
	key_k,
	key_l,
	key_m,
	key_n,
	key_o,
	key_p,
	key_q,
	key_r,
	key_s,
	key_t,
	key_u,
	key_v,
	key_w,
	key_x,
	key_y,
	key_z,
	key_0,
	key_1,
	key_2,
	key_3,
	key_4,
	key_5,
	key_6,
	key_7,
	key_8,
	key_9,
	key_f1,
	key_f2,
	key_f3,
	key_f4,
	key_f5,
	key_f6,
	key_f7,
	key_f8,
	key_f9,
	key_f10,
	key_f11,
	key_f12,
	key_f13,
	key_f14,
	key_f15,
	key_comma,
	key_colon,
//	key_DECIMAL,
	key_apostrophe,
	key_backslash,
	key_grave,
	key_substract,
	key_lbracket,
	key_rbracket,
	key_semicolon,
	key_slash,
	key_underline,
	key_print,
	key_scroll,
	key_pause,
	key_lwin,
	key_rwin,
	key_num0,
	key_num1,
	key_num2,
	key_num3,
	key_num4,
	key_num5,
	key_num6,
	key_num7,
	key_num8,
	key_num9,
	key_numcomma,
	key_numenter,
	key_numlock,
	key_add,
	key_minus,
	key_multiply,
	key_divide,
//	key_apps,
//	key_at,
//	key_ax,
	key_equals,
	key_kana,
	key_kanji,
	key_next,
//	key_noconvert,
	key_numequals,
	key_period,
//	key_power,
//	key_prior,
//	key_sleep,
//	key_stop,
//	key_sysrq,
//	key_unlabeled,
	key_yen,
	X_NUM_KEY_KEYS,
	num_key_keys = X_NUM_KEY_KEYS & input_keyid_mask,



	////////////////////////////////////////////////////////////////////////////
	// Mouse button codes
	//

	mouse_l                  = input_type_mouse_key,
	mouse_m,
	mouse_r,
	X_NUM_MOUSE_KEYS,
	num_mouse_keys = X_NUM_MOUSE_KEYS & input_keyid_mask,



	////////////////////////////////////////////////////////////////////////////
	// Mouse axis codes
	//

	mouse_x_axis             = input_type_mouse_axis,
	mouse_y_axis,
	mouse_z_axis,
	X_NUM_MOUSE_AXIS,
	num_mouse_axis = X_NUM_MOUSE_AXIS & input_keyid_mask,



	////////////////////////////////////////////////////////////////////////////
	// Joystick button codes
	//

	X_NUM_JOYSTICK_KEYS      = input_type_joystick_key,
	num_joystick_keys = X_NUM_JOYSTICK_KEYS & input_keyid_mask,



	////////////////////////////////////////////////////////////////////////////
	// Joystick axis codes
	//

	X_NUM_JOYSTICK_AXIS      = input_type_joystick_axis,
	num_joystick_axis = X_NUM_JOYSTICK_AXIS & input_keyid_mask,

	num_total_keys = num_key_keys + num_mouse_keys + num_mouse_axis + num_joystick_keys + num_joystick_axis
};

}

typedef kc::type key_code;

}
}

#endif
