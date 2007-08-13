#ifndef SGE_CONSOLE_GFX_HPP_INCLUDED
#define SGE_CONSOLE_GFX_HPP_INCLUDED

// C++
#include <list>

// Boost
#include <boost/noncopyable.hpp>
#include <boost/signals/connection.hpp>

// SGE
#include "../string.hpp"
#include "../math/dim.hpp"
#include "../plugin_manager.hpp"
#include "../renderer/renderer.hpp"
#include "../renderer/font.hpp"
#include "../renderer/vertex_buffer.hpp"
#include "../renderer/index_buffer.hpp"
#include "../timer.hpp"
#include "../input/key_state_tracker.hpp"

// Eigenes
#include "console.hpp"

namespace sge
{
namespace con
{

// TODO: Die Konsole langsam heruntergleitend machen
class console_gfx : boost::noncopyable
{
	typedef std::size_t               size_type;
	renderer_ptr                      rend;
	math::dim2                        console_size;
	font&                             fn;
	size_type                         lines_per_screen;
	input_system_ptr                  input_system;
	boost::signals::scoped_connection input_connection;
	boost::signals::scoped_connection input_repeat_connection;
	key_state_tracker                 keys;
	color                             font_color;
	texture_ptr                       background_texture;

	bool                        cursor_active;
	string::size_type           cursor_position;
	timer                       cursor_blink;
	string                      input_line;
	typedef std::list<string>   history_container;
	history_container           history;
	history_container           command_history;
	size_type                   history_limit;
	size_type                   command_history_limit;
	int                         command_history_pos;
	vertex_buffer_ptr           vb;
	index_buffer_ptr            ib;

	void fn_get(const arg_list &);
	void fn_set(const arg_list &);
	void fn_clear(const arg_list &);
	void fn_dump(const arg_list &);
	void fn_list(const arg_list &);
	void fn_funclist(const arg_list &);
	void fn_chat(const string &);

	void key_action(const key_type &k);
	void key_callback(const key_pair &);
public:
	console_gfx(renderer_ptr,
	            input_system_ptr,
	            font &,
	            const color,
	            texture_ptr background_texture);

	void output_line(const string &s);
	void draw();
	void set_texture(texture_ptr t);
};

}
}

#endif // SGE_CONSOLE_HPP
