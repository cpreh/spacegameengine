/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/console/detail/cursor.hpp>
#include <sge/text.hpp>

sge::console::detail::cursor::cursor()
	: line_(SGE_TEXT(" ")),
		pos_(0)
{
}

void sge::console::detail::cursor::reset()
{
	line_ = SGE_TEXT(" ");
	pos_ = 0;
}

sge::string const sge::console::detail::cursor::edited(bool _active) const
{
	sge::string l = line_;
	if (_active)
		l[pos_] = SGE_TEXT('_');
	return l;
}

sge::string const sge::console::detail::cursor::string() const
{
	// skip last space
	return line_.substr(0,line_.length()-1);
}

void sge::console::detail::cursor::string(sge::string const &_line)
{
	line_ = _line;
	line_.push_back(SGE_TEXT(' '));
	pos_ = line_.length()-1;
}

void sge::console::detail::cursor::erase_word()
{
	if (line_.length() == 1)
		return;

	string::size_type s = line_.rfind(SGE_TEXT(' '),pos_-1);
	if (s == string::npos)
		s = 0;
	
	line_.erase(s,pos_-s);
	pos_ = s;
}

void sge::console::detail::cursor::erase_char()
{
	if (pos_ == line_.length()-1)
		return;
	
	line_.erase(pos_,1);
}

void sge::console::detail::cursor::left()
{
	if (pos_ == 0)
		return;
	pos_ = pos_-1;
}

void sge::console::detail::cursor::right()
{
	if (pos_ == line_.length()-1)
		return;
	pos_ = pos_+1;
}

void sge::console::detail::cursor::to_start()
{
	pos_ = 0;
}

void sge::console::detail::cursor::to_end()
{
	pos_ = line_.length()-1;
}

bool sge::console::detail::cursor::empty() const
{
	return line_.length() == 1;
}

void sge::console::detail::cursor::insert(char_type const c)
{
	line_.insert(
		pos_,
		1,
		c);
}

bool sge::console::detail::cursor::at_start() const
{
	return pos_ == 0;
}

void sge::console::detail::cursor::complete_word(
	variable_map const &,
	function_map const &)
{
	// TODO
}

#if 0
void sge::console::gfx::tab_complete(string &input_line)
{
	if (cursor_pos == 0)
		return;

	// determine which word we are in, if it's the first, complete a command,
	// if it's any other, complete a variable
	string::size_type
		right = cursor_pos,
		left = input_line.rfind(SGE_TEXT(' '),right-1);

	const bool is_command = left == std::string::npos;

	if (is_command)
		left = 0;

	// use character _after_ the space (or / for that matter)
	left++;

	if (left == right)
		return;
	
	string const to_complete = input_line.substr(left,right-left);
	
	typedef std::set<string> string_set;
	string_set completions;
	
	// first word
	if (is_command)
	{
		const function_map &f = funcs();
		for (function_map::const_iterator i = f.begin(); i != f.end(); ++i)
			if (boost::algorithm::starts_with(i->first,to_complete))
				completions.insert(i->first);
	}
	else
	{
		const variable_map &f = vars();
		for (variable_map::const_iterator i = f.begin(); i != f.end(); ++i)
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
	input_line.replace(left,right-left,replacement);
	cursor_pos = left + replacement.length();
}
#endif
