// C
#include <cstdio>

// C++
#include <iostream>
#include <fstream>

// Boost
#include <boost/bind.hpp>
#include <boost/utility.hpp>

// SGE
#include "../../texture/handler.hpp"
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
		output_line(iconv("Error: No variable given, use ") + instance().prefix() + args[0] + iconv(" <variable name>"));
		return;
	}

	singleton::var_container &vars = instance().vars();
	if (vars.find(args[1]) == vars.end())
	{
		output_line(iconv("Error: Couldn't find variable \"") +args[1] + iconv("\"!"));
		return;
	}

	output_line(args[1] + iconv("=\"") + vars[args[1]]->get_string() + iconv("\""));
}

void sge::con::console_gfx::fn_set(const arg_list &args)
{
	if (args.size() < 3)
	{
		output_line(iconv("Error: No variable or value given, use ") + instance().prefix() + args[0] + iconv(" <variable name> <value>"));
		return;
	}

	singleton::var_container &vars = instance().vars();
	if (vars.find(args[1]) == vars.end())
	{
		output_line(iconv("Error: Couldn't find variable \"") + args[1] + iconv("\"!"));
		return;
	}

	vars[args[1]]->set_string(args[2]);
	output_line(args[1] + iconv("=\"") + vars[args[1]]->get_string() + iconv("\""));
}

void sge::con::console_gfx::fn_funclist(const arg_list &args)
{
	singleton::func_container &funcs = instance().funcs();

	string search_string;
	if (args.size() > 1)
		search_string = args[1];

	if (funcs.size() == 0)
	{
		output_line(iconv("No functions have been defined yet."));
		return;
	}

	output_line(iconv("***Functions begin"));
	for (singleton::func_container::const_iterator i = funcs.begin(); i != funcs.end(); ++i)
	{
		if (i->first.find(search_string) != string::npos)
			output_line(i->first);
	}
	output_line(iconv("***Functions end"));
}

void sge::con::console_gfx::fn_list(const arg_list &args)
{
	singleton::var_container &vars = instance().vars();

	string search_string;
	if (args.size() > 1)
		search_string = args[1];

	if (vars.size() == 0)
	{
		output_line(iconv("No console variables defined yet."));
		return;
	}

	output_line(iconv("***Variables begin"));
	for (singleton::var_container::const_iterator i = vars.begin(); i != vars.end(); ++i)
	{
		if (i->first.find(search_string) != string::npos)
			output_line(i->first + iconv("=\"") + i->second->get_string() + iconv("\""));
	}
	output_line(iconv("***Variables end"));
}

void sge::con::console_gfx::fn_clear(const arg_list &/*args*/)
{
	history.clear();
}

void sge::con::console_gfx::fn_dump(const arg_list &args)
{
	if (args.size() < 2 || args[1].empty())
	{
		output_line(iconv("No file specified, use ") + instance().prefix() + args[0] + iconv(" <filename>"));
		return;
	}

	if (args[1] == iconv("stdout"))
	{
		for (history_container::const_iterator i = history.begin(); i != history.end(); ++i)
			std::cout << iconv(*i) << '\n';
		return;
	}

	std::ofstream file(iconv(args[1]).c_str());
	if (!file.is_open())
	{
		output_line(iconv("Couldn't open file \"") + args[1] + iconv("\" for writing"));
		return;
	}

	for (history_container::const_iterator i = history.begin(); i != history.end(); ++i)
		file << iconv(*i) << "\n";
}

void sge::con::console_gfx::fn_chat(const string &s)
{
	std::cout << iconv(s) << "\n";
}

void sge::con::console_gfx::output_line(const string &s)
{
	if (history.size() == history_limit)
		history.pop_front();
	history.push_back(s); 
}

void sge::con::console_gfx::key_callback(const key_pair &k)
{
	if (keys[KC_LCTRL])
		output_line(iconv("char_code = ") + k.first.char_code);

	if (k.second)
		key_action(k.first);
}

// TODO: Die Kommandohistorie etwas schöner machen, vielleicht auf
// input_line verzichten
void sge::con::console_gfx::key_action(const key_type &k)
{
	switch(k.code) 
	{
		case KC_BACK:
			if (cursor_position > 0)
			{
				input_line.erase(input_line.begin() + cursor_position - 1);
				cursor_position--;
			}
		break;
		case KC_DEL:
			if (input_line.length() > 0 && cursor_position < input_line.size())
				input_line.erase(input_line.begin() + cursor_position);
		break;
		case KC_HOME:
			cursor_position = 0;
		break;
		case KC_END:
			cursor_position = input_line.size();
		break;
		case KC_RIGHT:
			cursor_position = std::min(std::size_t(cursor_position + 1),input_line.size());
		break;
		case KC_LEFT:
			cursor_position = std::max(string::size_type(0),cursor_position - 1);
		break;
		case KC_UP:
			if (command_history.size() == 0)
				break;
	
			if (command_history_pos >= int(command_history.size() - 1))
				break;
	
			input_line = *boost::next(command_history.begin(),++command_history_pos);
			cursor_position = input_line.size();
		break;
		case KC_DOWN:
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
		case KC_RETURN:
			if (input_line.length() <= 0)
				break;
	
			output_line(input_line);
			try {
				instance().eval(input_line);
			} catch (const exception &e) {
				output_line(iconv("Error: ") + iconv(e.what()));
			}
			if (command_history.size() == command_history_limit)
				command_history.pop_back();
			command_history.push_front(input_line);
			command_history_pos = -1;
			input_line.clear();
			cursor_position = 0;
		break;
		default:
			if(std::isprint(k.char_code) && keys[KC_LCTRL] == 0)
			{
				input_line.insert(input_line.begin() + cursor_position, k.char_code);
				++cursor_position;
			}
		break;
	}


	if (k.char_code == 'w' && keys[KC_LCTRL])
	{
		output_line(iconv("w entered!"));
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
	if (cursor_blink.update())
		cursor_active = !cursor_active;

	ss.render();

	// input_line und ein Dummy, wo evtl. der Cursor hinkommt
	string edit_input_line = input_line + iconv(" ");

	// \r erstmal als Dummy
	// TODO: Hier was ordentliches machen
	if (cursor_active)
		edit_input_line[cursor_position] = '\r';

	// Eingabezeile ganz unten zeichnen
	fn.draw_text(edit_input_line, math::vector2(0,console_size.h() - fn.height()), math::dim2(console_size.w(), fn.height()), font_color, font_flags::no_multi_line | font_flags::align_left | font_flags::align_top);

	// History-Ausschnitt berechnen
	const int history_lines = int(std::min(lines_per_screen, history.size()));

	history_container::const_iterator cutout_it = history.end(),cutout_end = history.end();
	std::advance(cutout_it,-history_lines);

	const string history_string = join<string>(cutout_it, cutout_end);

	fn.draw_text(history_string, math::vector2(0,0), math::dim2(console_size.w(), console_size.h() - fn.height()), font_color, font_flags::align_left | font_flags::align_bottom | font_flags::no_line_wrap);
}

void sge::con::console_gfx::set_texture(const std::string &t)
{
	background.set_texture(t);
}

sge::con::console_gfx::console_gfx(const renderer_ptr rend,
                                   const input_system_ptr input_system,
                                   font& fn,
                                   const image_loader_handler& loader_handler,
                                   const color font_color,
                                   const std::string &background_texture) 
: rend(rend),
  console_size(1, 0.5),
  fn(fn),
  lines_per_screen(static_cast<size_type>(console_size.h() / fn.height())-1),
  input_system(input_system),
  input_connection(input_system->register_callback(boost::bind(&console_gfx::key_callback, this, _1))),
  input_repeat_connection(input_system->register_repeat_callback(boost::bind(&console_gfx::key_action, this, _1))),
  keys(input_system),
  ss(rend,loader_handler),
  background(ss,math::vector2(0,0),console_size,background_texture),
  font_color(font_color),
  cursor_active(true),
  cursor_position(0),
  cursor_blink(300),
  history_limit(500),
  command_history_limit(500),
  command_history_pos(-1)
{
	background.repeat(4);
	instance().add(iconv("get"),boost::bind(&console_gfx::fn_get,this,_1));
	instance().add(iconv("set"),boost::bind(&console_gfx::fn_set,this,_1));
	instance().add(iconv("clear"),boost::bind(&console_gfx::fn_clear,this,_1));
	instance().add(iconv("dump"),boost::bind(&console_gfx::fn_dump,this,_1));
	instance().add(iconv("varlist"),boost::bind(&console_gfx::fn_list,this,_1));
	instance().add(iconv("funclist"),boost::bind(&console_gfx::fn_funclist,this,_1));
	instance().chat_callback(boost::bind(&console_gfx::fn_chat,this,_1));
}
