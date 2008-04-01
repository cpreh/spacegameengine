// c++
#include <cctype>
// boost
#include <boost/bind.hpp>
// sge
#include "../../sprite/system_impl.hpp"
#include "../../math/matrix_util.hpp"
#include "../../math/matrix_impl.hpp"
#include "../../iostream.hpp"
#include "../../ostream.hpp"
#include "../../fstream.hpp"
#include "../console_gfx.hpp"

namespace
{

template<typename IteratorType>
typename IteratorType::value_type join(IteratorType begin,IteratorType end,const typename IteratorType::value_type &middle)
{
	typedef typename IteratorType::value_type string_type;

	if (begin == end)
		return string_type();

	string_type s;
	--end;
	for (; begin != end; ++begin)
		s += (*begin) + middle;
	s += *begin;
	return s;
}

}

sge::con::console_gfx::console_gfx(
	const renderer_ptr rend,
	const virtual_texture_ptr texture,
	const font_ptr fn,
	const input_system_ptr is,
	const sprite::point &pos,
	const sprite::dim &size)
: rend(rend),
  fn(fn),
  ic(is->register_callback(boost::bind(&console_gfx::key_callback,this,_1))),
  irc(is->register_repeat_callback(boost::bind(&console_gfx::key_action,this,_1))),
  mod(is),
  ss(rend),
  bg(pos,texture,size),
  active_(false),
  cursor_timer(timer::interval_type(300)),
  cursor_rate(SGE_TEXT("cursor_rate"),boost::bind(&console_gfx::change_cursor_rate,this,_1,_2),timer::interval_type(300)),
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
		std::copy(history.begin(),history.end(),std::ostream_iterator<sge::string,sge::string::value_type>(sge::cout,SGE_TEXT("\n")));
		print(SGE_TEXT("dumped history to stdout"));
	}
	else
	{
		sge::text_ofstream file(args[1]);
		sge::cout << args[1] << SGE_TEXT("\n");
		if (!file.is_open())
		{
			print(SGE_TEXT("error: couldn't open file \"") + args[1] + SGE_TEXT("\""));
		}
		else
		{
			std::copy(history.begin(),history.end(),std::ostream_iterator<sge::string,sge::string::value_type>(file, SGE_TEXT("\n")));
			print(SGE_TEXT("dumped history to \"")+args[1]+SGE_TEXT("\""));
		}
	}
}

void sge::con::console_gfx::key_callback(const key_pair &k)
{
	if (!active_)
		return;

	if (k.value())
		key_action(k.key());
}

void sge::con::console_gfx::key_action(const key_type &k)
{
	if (!active_)
		return;

	sge::string &il = *input_history_pos;

	// is a printable character? then append to input
	if(std::isprint(k.char_code(),std::locale()))
	{
		// FIXME: input system doesn't work!
		if (mod.state().ctrl && (k.char_code() == SGE_TEXT('w') || k.char_code() == SGE_TEXT('W')))
		{
			if (cursor_pos == 0)
				return;

			sge::string::size_type lastws = il.rfind(SGE_TEXT(' '),cursor_pos-1);
			if (lastws == std::string::npos)
				lastws = 0;
			il.erase(lastws,cursor_pos-lastws);
		}
		else
		{
			il.insert(cursor_pos++,1,k.char_code());
		}
	}

	if (k.code() == kc::key_backspace && cursor_pos > 0)
		il.erase(--cursor_pos,1);

	if (k.code() == kc::key_left && cursor_pos > 0)
		--cursor_pos;

	if (k.code() == kc::key_right && cursor_pos < il.size()-1)
		++cursor_pos;

	if (k.code() == kc::key_up && input_history_pos != --input_history.end())
		{ input_history_pos = input_history_pos+1; cursor_pos = 0; }

	if (k.code() == kc::key_down && input_history_pos != input_history.begin())
		{ input_history_pos = input_history_pos-1; cursor_pos = 0; }

	if (k.code() == kc::key_pageup && history_pos != --history.end())
		++history_pos;

	if (k.code() == kc::key_pagedown && history_pos != history.begin())
		--history_pos;

	if (k.code() == kc::key_return && il.size())
	{
		print(il);

		try
		{
			eval(il);
		}
		catch (const exception &e)
		{
			print(SGE_TEXT("console error: ")+e.wide_what());
		}

		// add executed command to each history (at the front)...
		input_history.push_front(il);
		// ...and clear front
		input_history_pos = input_history.begin();
		input_history.front().clear();
		cursor_pos = 0;
	}
}

void sge::con::console_gfx::draw()
{
	ss.render(&bg, &bg+1);

	string iln = *input_history_pos;
	if (cursor_active)
		iln[cursor_pos] = cursor_char;

	if (!math::almost_zero(cursor_timer.update()))
		cursor_active = !cursor_active;

	// draw input line
	fn->draw_text(iln,
		math::structure_cast<font_unit>(bg.pos()),
		math::structure_cast<font_unit>(bg.size()),
		font_align_h::left,font_align_v::bottom);

	// draw history
	const std::size_t total_lines = bg.size().h()/fn->height();

	history_container::const_reverse_iterator history_it(history_pos),history_end(history.end());
	// go from history_pos to history_pos+total_lines (or the end, if this comes before)
	for (std::size_t i = 0; i < total_lines && history_it != history_end; ++i)
		history_it--;

	const sge::string history_string = join(history_it,history_container::const_reverse_iterator(history_pos),SGE_TEXT("\n"));
	// draw history lines
	fn->draw_text(history_string,
		math::structure_cast<font_unit>(bg.pos()),
		sge::font_dim(bg.size().w(),bg.size().h()-fn->height()),
		font_align_h::left,font_align_v::bottom);
}

sge::timer::interval_type sge::con::console_gfx::change_cursor_rate(
	const timer::interval_type &n,
	const timer::interval_type &)
{
	cursor_timer.interval(n);
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

void sge::con::console_gfx::print(const string_type &s)
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
