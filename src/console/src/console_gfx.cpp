// C
#include <cstdio>

// C++
#include <iostream>
#include <fstream>
#include <locale>

// Boost
#include <boost/bind.hpp>
#include <boost/utility.hpp>

// SGE
#include "../../renderer/transform.hpp"
#include "../../renderer/scoped_lock.hpp"
#include "../../sprite/helper.hpp"
#include "../../iconv.hpp"
#include "../console_gfx.hpp"

namespace
{

template<typename StringType,typename IteratorType>
StringType join(IteratorType begin,IteratorType end)
{
	if (begin == end)
		return StringType();

	StringType s;
	--end;
	for (; begin != end; ++begin)
		s += (*begin) + static_cast<typename StringType::value_type>('\n');
	s += *begin;
	return s;
}

}

void sge::con::console_gfx::fn_get(const arg_list &args)
{
	if (args.size() < 2)
	{
		output_line(sge::string(L"Error: No variable given, use ") + instance().prefix() + args[0] + L" <variable name>");
		return;
	}

	singleton::var_container &vars = instance().vars();
	if (vars.find(args[1]) == vars.end())
	{
		output_line(L"Error: Couldn't find variable \"" + args[1] + L"\"!");
		return;
	}

	output_line(args[1] + L"=\"" + vars[args[1]]->get_string() + L"\"");
}

void sge::con::console_gfx::fn_set(const arg_list &args)
{
	if (args.size() < 3)
	{
		output_line(L"Error: No variable or value given, use " + instance().prefix() + args[0] + L" <variable name> <value>");
		return;
	}

	singleton::var_container &vars = instance().vars();
	if (vars.find(args[1]) == vars.end())
	{
		output_line(L"Error: Couldn't find variable \"" + args[1] + L"\"!");
		return;
	}

	vars[args[1]]->set_string(args[2]);
	output_line(args[1] + L"=\"" + vars[args[1]]->get_string() + L"\"");
}

void sge::con::console_gfx::fn_funclist(const arg_list &args)
{
	singleton::func_container &funcs = instance().funcs();

	string search_string;
	if (args.size() > 1)
		search_string = args[1];

	if (funcs.size() == 0)
	{
		output_line(L"No functions have been defined yet.");
		return;
	}

	output_line(L"***Functions begin");
	for (singleton::func_container::const_iterator i = funcs.begin(); i != funcs.end(); ++i)
	{
		if (i->first.find(search_string) != string::npos)
			output_line(i->first);
	}
	output_line(L"***Functions end");
}

void sge::con::console_gfx::fn_list(const arg_list &args)
{
	singleton::var_container &vars = instance().vars();

	string search_string;
	if (args.size() > 1)
		search_string = args[1];

	if (vars.size() == 0)
	{
		output_line(L"No console variables defined yet.");
		return;
	}

	output_line(L"***Variables begin");
	for (singleton::var_container::const_iterator i = vars.begin(); i != vars.end(); ++i)
	{
		if (i->first.find(search_string) != string::npos)
			output_line(i->first + L"=\"" + i->second->get_string() + L"\"");
	}
	output_line(L"***Variables end");
}

void sge::con::console_gfx::fn_clear(const arg_list &/*args*/)
{
	history.clear();
}

void sge::con::console_gfx::fn_dump(const arg_list &args)
{
	if (args.size() < 2 || args[1].empty())
	{
		output_line(L"No file specified, use " + instance().prefix() + args[0] + L" <filename>");
		return;
	}

	if (args[1] == L"stdout")
	{
		for (history_container::const_iterator i = history.begin(); i != history.end(); ++i)
			std::wcout << *i << L'\n';
		return;
	}

	// FIXME: Hier ist sge::string -> std::string noetig
	/*std::ofstream file(iconv(args[1]).c_str());
	if (!file.is_open())
	{
		output_line(iconv("Couldn't open file \"") + args[1] + iconv("\" for writing"));
		return;
	}

	for (history_container::const_iterator i = history.begin(); i != history.end(); ++i)
		file << iconv(*i) << "\n";
	*/
}

void sge::con::console_gfx::fn_chat(const string &s)
{
	std::wcout << s << L"\n";
}

void sge::con::console_gfx::output_line(const string &s)
{
	if (history.size() == history_limit)
		history.pop_front();
	history.push_back(s); 
}

void sge::con::console_gfx::key_callback(const key_pair &k)
{
	if (!active_)
		return;

	/*
	if (keys[kc::key_lctrl])
		output_line(L"char_code = " + k.first.char_code);
	*/

	if (!k.zero())
		key_action(k.key());
}

// TODO: Die Kommandohistorie etwas schöner machen, vielleicht auf
// input_line verzichten
void sge::con::console_gfx::key_action(const key_type &k)
{
	if (!active_)
		return;

	switch(k.code()) 
	{
		case kc::key_backspace:
			if (cursor_position > 0)
			{
				input_line.erase(input_line.begin() + cursor_position - 1);
				cursor_position--;
			}
		break;
		case kc::key_delete:
			if (input_line.length() > 0 && cursor_position < input_line.size())
				input_line.erase(input_line.begin() + cursor_position);
		break;
		case kc::key_home:
			cursor_position = 0;
		break;
		case kc::key_end:
			cursor_position = input_line.size();
		break;
		case kc::key_right:
			cursor_position = std::min(std::size_t(cursor_position + 1),input_line.size());
		break;
		case kc::key_left:
			if (cursor_position > 0) --cursor_position;
		break;
		case kc::key_up:
			if (command_history.size() == 0)
				break;
	
			if (command_history_pos >= int(command_history.size() - 1))
				break;
	
			input_line = *boost::next(command_history.begin(),++command_history_pos);
			cursor_position = input_line.size();
		break;
		case kc::key_down:
			if (command_history.size() == 0 || command_history_pos < 0)
				break;
	
			// Sonderfall für unterste Zeile
			if (command_history_pos == 0)
			{
				command_history_pos = -1;
				cursor_position =     0;
				input_line.clear();
				break;
			}
	
			input_line = *boost::prior(command_history.begin(),--command_history_pos);
			cursor_position = input_line.size();
		break;
		case kc::key_return:
			if (input_line.length() <= 0)
				break;
	
			output_line(input_line);
			try {
				instance().eval(input_line);
			} catch (const exception &e) {
				output_line(L"Error: " + iconv(e.what()));
			}
			if (command_history.size() == command_history_limit)
				command_history.pop_back();
			command_history.push_front(input_line);
			command_history_pos = -1;
			input_line.clear();
			cursor_position = 0;
		break;
		default:
			if(std::isprint(k.char_code(), std::locale()) && math::almost_zero(keys[kc::key_lctrl]))
			{
				input_line.insert(input_line.begin() + cursor_position, k.char_code());
				++cursor_position;
			}
		break;
	}


	if (k.char_code() == 'w' && !math::almost_zero(keys[kc::key_lctrl]))
	{
		output_line(L"w entered!");
		if (input_line.size() != 0)
		{
			std::size_t space_pos = input_line.rfind(' ',cursor_position);
			if (space_pos == std::string::npos)
			{
				input_line.clear();
				cursor_position = 0;
			}
			else
			{
				input_line.erase(input_line.begin() + space_pos,input_line.begin() + cursor_position);
			}
		}
	}
}

void sge::con::console_gfx::draw()
{
	if (cursor_blink.update() > 0)
		cursor_active = !cursor_active;

	rend->projection(math::matrix_orthogonal_xy());
	rend->transform(matrix_2d_to_3d());
	rend->set_texture(background_texture);
	rend->set_bool_state(sge::bool_state::enable_zbuffer,false);
	rend->render(vb,ib,0,vb->size(),indexed_primitive_type::triangle,2,0);
	rend->set_bool_state(sge::bool_state::enable_zbuffer,false);
	rend->set_bool_state(sge::bool_state::enable_culling,false);
	rend->set_bool_state(sge::bool_state::enable_alpha_blending,true);
	rend->set_draw_mode(draw_mode::fill);

	// input_line und ein Dummy, wo evtl. der Cursor hinkommt
	string edit_input_line = input_line + L" ";

	// \r erstmal als Dummy
	// TODO: Hier was ordentliches machen
	if (cursor_active)
	//	edit_input_line[cursor_position] = L'\r';
		edit_input_line[cursor_position] = cursor_char_;

	// Eingabezeile ganz unten zeichnen
	fn.draw_text(edit_input_line,sge::font_pos(0,0),sge::font_dim(sge::font_unit(rend->screen_width() * console_size.w()),sge::font_unit(rend->screen_height() * console_size.h())), font_align_h::left, font_align_v::bottom, font_flags::no_line_wrap);

	// History-Ausschnitt berechnen
	const size_type history_lines = std::min(lines_per_screen, history.size());

	history_container::const_iterator cutout_it = history.end(),cutout_end = history.end();
	std::advance(cutout_it,-static_cast<difference_type>(history_lines));

	const string history_string = join<string>(cutout_it, cutout_end);

	fn.draw_text(history_string,sge::font_pos(0,0),sge::font_dim(sge::font_unit(rend->screen_width() * console_size.w()),sge::font_unit(rend->screen_height() * console_size.h() - fn.height())), font_align_h::left, font_align_v::bottom, font_flags::no_line_wrap);
}

void sge::con::console_gfx::set_texture(texture_ptr t)
{
	background_texture = t;
}

sge::con::console_gfx::console_gfx(const renderer_ptr rend,
                                   const input_system_ptr input_system,
                                   font& fn,
                                   const color font_color,
                                   const texture_ptr background_texture) 
: rend(rend),
  console_size(1, 0.5),
  fn(fn),
  lines_per_screen(static_cast<size_type>(console_size.h() * rend->screen_height() / fn.height())-1),
  input_system(input_system),
  input_connection(input_system->register_callback(boost::bind(&console_gfx::key_callback, this, _1))),
  input_repeat_connection(input_system->register_repeat_callback(boost::bind(&console_gfx::key_action, this, _1))),
  keys(input_system),
  font_color(font_color),
  background_texture(background_texture),
  cursor_active(true),
  cursor_position(0),
  cursor_blink(300),
  cursor_char_(L'|'),
  history_limit(500),
  command_history_limit(500),
  command_history_pos(-1),
  vb(rend->create_vertex_buffer(vertex_format().add(vertex_usage::pos).add(vertex_usage::tex), 4)),
  ib(rend->create_index_buffer(6)),
  active_(false)
{
	{
		scoped_lock<vertex_buffer_ptr> _vblock(vb);
		vertex_buffer::iterator vbit = vb->begin();
		fill_sprite_vertices(vbit, math::rect(0, 0, console_size.w(), console_size.h()), math::rect(0, 0, 1, 1), 0);
	}

	{
		scoped_lock<index_buffer_ptr> _iblock(ib);
		index_buffer::iterator ibit = ib->begin();
		fill_sprite_indices(ibit, 0);
	}
	
	instance().add(L"get",boost::bind(&console_gfx::fn_get,this,_1));
	instance().add(L"set",boost::bind(&console_gfx::fn_set,this,_1));
	instance().add(L"clear",boost::bind(&console_gfx::fn_clear,this,_1));
	instance().add(L"dump",boost::bind(&console_gfx::fn_dump,this,_1));
	instance().add(L"varlist",boost::bind(&console_gfx::fn_list,this,_1));
	instance().add(L"funclist",boost::bind(&console_gfx::fn_funclist,this,_1));
	instance().chat_callback(boost::bind(&console_gfx::fn_chat,this,_1));
}
