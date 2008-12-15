#include <sge/console/console_gfx.hpp>
#include <sge/console/console.hpp>
#include <sge/console/action_var_base_impl.hpp>
#include <sge/font/font.hpp>
#include <sge/input/key_pair.hpp>
#include <sge/input/system.hpp>
#include <sge/math/matrix_util.hpp>
#include <sge/math/matrix_impl.hpp>
#include <sge/time/millisecond.hpp>
#include <sge/fstream.hpp>
#include <sge/text.hpp>
#include <sge/iostream.hpp>
#include <boost/bind.hpp>
#include <boost/range.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/next_prior.hpp>
#include <boost/none.hpp>
#include <ostream>
#include <locale>
#include <set>

sge::con::console_gfx::console_gfx(
	renderer::device_ptr const rend,
	texture::part_ptr const texture,
	font::font_ptr const fn,
	input::system_ptr const is,
	sprite::point const &pos,
	sprite::dim const &size)
:
	rend(rend),
	fn(fn),
	ic(
		is->register_callback(
			boost::bind(
				&console_gfx::key_callback,
				this,
				_1))),
	irc(
		is->register_repeat_callback(
			boost::bind(
				&console_gfx::key_action,
				this,
				_1))),
	ss(rend),
	bg(
		pos,
		texture,
		size),
	active_(false),
	cursor_timer(time::millisecond(300)),
	cursor_rate(
		SGE_TEXT("console_cursor_rate"),
		boost::bind(
			&console_gfx::change_cursor_rate,
			this,
			_1),
		300),
	cursor_active(false),
	cursor_char(SGE_TEXT('_')),
	cursor_pos(0),
	history_size(0)
{
	input_history.push_front(SGE_TEXT(" "));
	input_history_pos = input_history.begin();
	history_pos = history.begin();

	add(SGE_TEXT("clear"),boost::bind(&console_gfx::clear,this,_1));
	add(SGE_TEXT("dump"),boost::bind(&console_gfx::dump,this,_1));
}

void sge::con::console_gfx::clear(const arg_list &)
{
	history.clear();
	history_pos = history.begin();
}

void sge::con::console_gfx::dump(const arg_list &args)
{
	if (args.size() == 1)
	{
		std::copy(
			history.begin(),
			history.end(),
			std::ostream_iterator<string, string::value_type>(
				cout,
				SGE_TEXT("\n")));
		print(SGE_TEXT("dumped history to stdout"));
	}
	else
	{
		ofstream file(args[1]);
		cout << args[1] << SGE_TEXT("\n");
		if (!file.is_open())
		{
			print(SGE_TEXT("error: couldn't open file \"")+args[1]+SGE_TEXT("\""));
		}
		else
		{
			std::copy(history.begin(),history.end(),std::ostream_iterator<string,string::value_type>(file, SGE_TEXT("\n")));
			print(SGE_TEXT("dumped history to \"")+args[1]+SGE_TEXT("\""));
		}
	}
}

void sge::con::console_gfx::key_callback(
	input::key_pair const &k)
{
	if (!active_)
		return;

	if (k.value())
		key_action(k.key());
}

void sge::con::console_gfx::tabcomplete(string &il)
{
	if (cursor_pos == 0)
		return;

	// determine which word we are in, if it's the first, complete a command,
	// if it's any other, complete a variable
	string::size_type
		right = cursor_pos,
		left = il.rfind(SGE_TEXT(' '),right-1);

	const bool is_command = left == std::string::npos;

	if (is_command)
		left = 0;

	// use character _after_ the space (or / for that matter)
	left++;

	if (left == right)
		return;
	
	string const to_complete = il.substr(left,right-left);
	
	typedef std::set<string> string_set;
	string_set completions;
	
	// first word
	if (is_command)
	{
		const callback_map &f = funcs();
		for (callback_map::const_iterator i = f.begin(); i != f.end(); ++i)
			if (boost::algorithm::starts_with(i->first,to_complete))
				completions.insert(i->first);
	}
	else
	{
		const var_map &f = vars();
		for (var_map::const_iterator i = f.begin(); i != f.end(); ++i)
			if (boost::algorithm::starts_with(i->first,to_complete))
				completions.insert(i->first);
	}

	if (completions.empty())
		return;

	string replacement;

	if (completions.size() != 1)
	{
		print(SGE_TEXT("possible replacements:"));
		for (string::size_type i = 0;;++i)
		{
			bool found = false;
			const string::value_type ref = (*completions.begin())[i];
			for (string_set::const_iterator j = completions.begin(); j != completions.end(); ++j)
			{
			 // first search iteration: print possibility
				if (i == 0)
					print(*j);

				if (j->length() <= i || (*j)[i] != ref)
				{
					found = true;
					break;
				}
			}

			if (found)
			{
				replacement = completions.begin()->substr(0,i);
				break;
			}
		}
	}
	else
	{
		replacement = *completions.begin();
	}

	//il.replace(left,right-left,replacement+SGE_TEXT(" "));
	il.replace(left,right-left,replacement);
	cursor_pos = left + replacement.length();
}

void sge::con::console_gfx::key_action(const input::key_type &k)
{
	if (!active_)
		return;

	string &il = *input_history_pos;

	// is a printable character? then append to input
	if(std::isprint(k.char_code(),std::locale()))
	{
		// FIXME: input system doesn't work!
		if ((k.char_code() == SGE_TEXT('w') || k.char_code() == SGE_TEXT('W')))
		{
			if (cursor_pos == 0)
				return;

			string::size_type lastws = il.rfind(SGE_TEXT(' '),cursor_pos-1);
			if (lastws == string::npos)
				lastws = 0;
			il.erase(lastws,cursor_pos-lastws);
		}
		else
		{
			il.insert(cursor_pos++,1,k.char_code());
		}
	}

	switch (k.code())
	{
		case input::kc::key_backspace:
			if (cursor_pos <= 0)
				return;

			il.erase(--cursor_pos,1);
		break;
		case input::kc::key_left:
			if (cursor_pos <= 0)
				return;

			--cursor_pos;
		break;
		case input::kc::key_right:
			if (cursor_pos >= il.size()-static_cast<string::size_type>(1))
				return;
			
			++cursor_pos;
		break;
		case input::kc::key_up:
			if (input_history_pos == --input_history.end())
				return;

			input_history_pos = boost::next(input_history_pos);
			cursor_pos = input_history_pos->length()-static_cast<string::size_type>(1);
		break;
		case input::kc::key_down:
			if (input_history_pos == input_history.begin())
				return;

			input_history_pos = boost::prior(input_history_pos);
			cursor_pos = input_history_pos->length()-static_cast<string::size_type>(1);
		break;
		case input::kc::key_pageup:
			if (history_pos == --history.end())
				return;

			history_pos = boost::next(history_pos);
		break;
		case input::kc::key_tab:
			tabcomplete(il);
		break;
		case input::kc::key_home:
			cursor_pos = 0;
		break;
		case input::kc::key_end:
			cursor_pos = il.length()-static_cast<string::size_type>(1);
		break;
		case input::kc::key_pagedown:
			if (history_pos == history.begin())
				return;

			history_pos = boost::prior(history_pos);
		break;
		case input::kc::key_return:
			if (il.empty())
				return;

			print(il);

			try
			{
				eval(il);
			}
			catch (const exception &e)
			{
				print(SGE_TEXT("console error: ")+e.what());
			}

			// add executed command to each history (at the front)...
			input_history.push_front(il);
			// ...and clear front
			input_history_pos = input_history.begin();
			input_history.front() = SGE_TEXT(" ");
			cursor_pos = 0;
		break;
		// else we get a million warnings about unhandled enumeration values
		default: break;
	}
}

void sge::con::console_gfx::draw()
{
	ss.render(bg);

	string iln = *input_history_pos;
	if (cursor_active)
		iln[cursor_pos] = cursor_char;

	if (cursor_timer.update_b())
		cursor_active = !cursor_active;

	// draw input line
	fn->draw_text(iln,
		math::structure_cast<font::unit>(bg.pos()),
		math::structure_cast<font::unit>(bg.size()),
		font::align_h::left,
		font::align_v::bottom);

	// draw history
	std::size_t const total_lines = bg.size().h()/fn->height();

	// go from history_pos to min(history_pos+total_lines,end)
	history_container::iterator history_it = history_pos;
	for (std::size_t i = 0; i < total_lines && history_it != history.end(); ++i)
		history_it++;

	string const history_string = 
		boost::algorithm::join(
			boost::make_iterator_range(
				history_container::const_reverse_iterator(history_it),
				history_container::const_reverse_iterator(history_pos)),
			SGE_TEXT("\n"));

	// draw history lines
	fn->draw_text(history_string,
		math::structure_cast<font::unit>(bg.pos()),
		font::dim(bg.size().w(),bg.size().h()-fn->height()),
		font::align_h::left,
		font::align_v::bottom);
}

sge::time::unit
sge::con::console_gfx::change_cursor_rate(
	time::unit  const n)
{
	cursor_timer.interval(
		time::millisecond(n));
	return n;
}

void sge::con::console_gfx::toggle()
{
	active_ = !active_;
}

bool sge::con::console_gfx::active() const
{
	return active_;
}

void sge::con::console_gfx::print(string const &s)
{
	// if we are at the very bottom, then stay there
	if (history_pos == history.begin())
	{
		history.push_front(s);
		history_pos = history.begin();
	}
	else
	{
		history.push_front(s);
	}
}
