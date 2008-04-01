#ifndef CONSOLE_GFX_HPP_INCLUDED
#define CONSOLE_GFX_HPP_INCLUDED

// c++
#include <deque>
#include <cstddef>

// sge
#include "../font/font.hpp"
#include "../renderer/renderer.hpp"
#include "../input/input_system.hpp"
#include "../input/key_mod_tracker.hpp"
#include "../scoped_connection.hpp"
#include "../sprite/system.hpp"
#include "../sprite/object.hpp"
#include "../string.hpp"
#include "../timer.hpp"
#include "../export.hpp"
#include "console.hpp"

namespace sge
{
namespace con
{

struct console_gfx
{
	typedef sge::string string_type;
	typedef string_type::value_type char_type;
	typedef std::deque<string_type> history_container;

	const renderer_ptr rend;
	const font_ptr fn;
	sge::scoped_connection ic,irc;
	sge::key_mod_tracker mod;
	sge::sprite::system ss;
	sge::sprite::object bg;
	bool active_;

	// input and history stuff
	sge::timer cursor_timer;
	sge::con::action_var<sge::timer::interval_type>::type cursor_rate;
	bool cursor_active;
	char_type cursor_char;
	string_type il;
	string_type::size_type cursor_pos;
	history_container history;
	history_container input_history;
	history_container::iterator history_pos;
	history_container::iterator input_history_pos;
	std::size_t history_size;

	SGE_SYMBOL console_gfx(
		const renderer_ptr,
		const virtual_texture_ptr,
		const font_ptr,
		const input_system_ptr,
		const sprite::point&,
		const sprite::dim&);
	SGE_SYMBOL void key_callback(const key_pair &);
	SGE_SYMBOL void key_action(const key_type &);
	SGE_SYMBOL void draw();
	SGE_SYMBOL timer::interval_type change_cursor_rate(
		const timer::interval_type &n,
		const timer::interval_type &);
	SGE_SYMBOL void toggle(); 
	SGE_SYMBOL bool active() const;
	SGE_SYMBOL void print(const string_type &);
	SGE_SYMBOL void clear(const arg_list &);
	SGE_SYMBOL void dump(const arg_list &);
};

}
}

#endif
