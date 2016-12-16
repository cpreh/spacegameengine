/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/console/function_map.hpp>
#include <sge/console/gfx/cursor.hpp>
#include <sge/font/char_type.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/string.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/container/at_optional.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/object_impl.hpp>


sge::console::gfx::cursor::cursor()
:
	line_(),
	pos_{
		0u
	}
{
}

sge::console::gfx::cursor::~cursor()
{
}

sge::font::string
sge::console::gfx::cursor::edited() const
{
	sge::font::string result(
		line_
	);

	sge::font::char_type const caret{
		SGE_FONT_LIT('_')
	};

	fcppt::optional::maybe(
		fcppt::container::at_optional(
			result,
			pos_
		),
		[
			caret,
			&result
		]{
			result.push_back(
				caret
			);
		},
		[
			caret
		](
			fcppt::reference<
				sge::font::char_type
			> const _ref
		)
		{
			_ref.get() =
				caret;
		}
	);

	return
		result;
}

sge::font::string const &
sge::console::gfx::cursor::string() const
{
	return
		line_;
}

void
sge::console::gfx::cursor::string(
	sge::font::string const &_line
)
{
	line_ =
		_line;

	pos_ =
		line_.length();
}

void
sge::console::gfx::cursor::erase_word()
{
	typedef
	fcppt::optional::object<
		size_type
	>
	optional_index;

	auto const rfind(
		[
			this
		](
			sge::font::char_type const _char,
			size_type const _index
		)
		->
		optional_index
		{
			size_type const index{
				line_.rfind(
					_char,
					_index
				)
			};

			return
				index
				==
				sge::font::string::npos
				?
					optional_index()
				:
					optional_index(
						index
					)
				;
		}
	);

	if(
		pos_
		==
		0u
	)
		return;

	size_type const index{
		fcppt::optional::from(
			rfind(
				SGE_FONT_LIT(' '),
				pos_
				-
				1u
			),
			[]{
				return
					fcppt::literal<
						size_type
					>(
						0u
					);
			}
		)
	};

	line_.erase(
		index,
		pos_
		-
		index
	);

	pos_ =
		index;
}

void
sge::console::gfx::cursor::erase_char()
{
	line_.erase(
		pos_,
		1u
	);
}

void
sge::console::gfx::cursor::left()
{
	if(
		pos_
		!=
		0u
	)
		--pos_;
}

void
sge::console::gfx::cursor::right()
{
	if(
		pos_
		!=
		line_.length()
	)
		++pos_;
}

void
sge::console::gfx::cursor::to_start()
{
	pos_ =
		0u;
}

void
sge::console::gfx::cursor::to_end()
{
	pos_ =
		line_.length();
}

bool
sge::console::gfx::cursor::empty() const
{
	return
		line_.empty();
}

void
sge::console::gfx::cursor::insert(
	sge::font::char_type const _char
)
{
	line_.insert(
		pos_,
		1u,
		_char
	);

	++pos_;
}

void
sge::console::gfx::cursor::complete_word(
	sge::console::function_map const &_map
)
{
}
