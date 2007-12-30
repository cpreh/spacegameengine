#ifndef CONSOLE_GFX_HPP_INCLUDED
#define CONSOLE_GFX_HPP_INCLUDED

// c++
#include <deque>

// sge
#include <sge/renderer/font.hpp>
#include <sge/renderer/renderer.hpp>
#include <sge/input/input_system.hpp>
#include <sge/input/key_mod_tracker.hpp>
#include <sge/scoped_connection.hpp>
#include <sge/sprite/system.hpp>
#include <sge/sprite/sprite.hpp>
#include <sge/string.hpp>
#include <sge/timer.hpp>
#include <sge/console/console.hpp>

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
	sge::sprite_system ss;
	sge::sprite bg;
	bool active_;

	// input and history stuff
	sge::con::action_var<sge::timer::interval_type>::type cursor_rate;
	sge::timer cursor_timer;
	bool cursor_active;
	char_type cursor_char;
	string_type il;
	string_type::size_type cursor_pos;
	history_container history;
	history_container input_history;
	history_container::iterator history_pos;
	history_container::iterator input_history_pos;
	std::size_t history_size;

	console_gfx(const renderer_ptr,const virtual_texture_ptr,const font_ptr,const input_system_ptr,const sprite_point&,const sprite_dim&);
	void key_callback(const key_pair &);
	void key_action(const key_type &);
	void draw();
	timer::interval_type change_cursor_rate(const timer::interval_type &n,const timer::interval_type &) { cursor_timer.interval(n); return n; }
	void toggle() { active_ = !active_; }
	bool active() const { return active_; }
	void print(const string_type &);
	void clear(const arg_list &);
	void dump(const arg_list &);
};

}
}

#endif
