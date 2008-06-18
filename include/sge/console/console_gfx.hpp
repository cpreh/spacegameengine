#ifndef CONSOLE_GFX_HPP_INCLUDED
#define CONSOLE_GFX_HPP_INCLUDED

// c++
#include <deque>
#include <cstddef>

// sge
#include "../font/font.hpp"
#include "../renderer/device.hpp"
#include "../input/system.hpp"
#include "../scoped_connection.hpp"
#include "../sprite/system.hpp"
#include "../sprite/object.hpp"
#include "../time/timer.hpp"
#include "../string.hpp"
#include "../export.hpp"
#include "console.hpp"

namespace sge
{
namespace con
{

class console_gfx
{
	public:
	SGE_SYMBOL console_gfx(
		const renderer::device_ptr,
		const virtual_texture_ptr,
		const font::font_ptr,
		const input::system_ptr,
		const sprite::point&,
		const sprite::dim&);
	SGE_SYMBOL void key_callback(const input::key_pair &);
	SGE_SYMBOL void key_action(const input::key_type &);
	SGE_SYMBOL void draw();
	SGE_SYMBOL space_unit change_cursor_rate(
		const space_unit &n,
		const space_unit &);
	SGE_SYMBOL void toggle(); 
	SGE_SYMBOL bool active() const;
	SGE_SYMBOL void print(const string &);
	SGE_SYMBOL void clear(const arg_list &);
	SGE_SYMBOL void dump(const arg_list &);

	private:
	void tabcomplete(string &);

	typedef std::deque<string> history_container;

	const renderer::device_ptr rend;
	const font::font_ptr fn;
	scoped_connection ic,irc;
	sprite::system ss;
	sprite::object bg;
	bool active_;

	// input and history stuff
	time::timer cursor_timer;
	action_var<space_unit>::type cursor_rate;
	bool cursor_active;
	string::value_type cursor_char;
	string il;
	string::size_type cursor_pos;
	history_container history;
	history_container input_history;
	history_container::iterator history_pos;
	history_container::iterator input_history_pos;
	std::size_t history_size;
};

}
}

#endif
