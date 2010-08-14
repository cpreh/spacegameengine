/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_FONT_TEXT_PART_HPP_INCLUDED
#define SGE_FONT_TEXT_PART_HPP_INCLUDED

#include <sge/font/text_part_fwd.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/string.hpp>
#include <sge/symbol.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

namespace sge
{
namespace font
{

class text_part
{
public:
	typedef string::const_iterator const_iterator;

	SGE_SYMBOL text_part(
		dim const &sz,
		string::const_iterator end,
		string::const_iterator next_begin
	);

	/// The size of this text part
	SGE_SYMBOL dim const &
	size() const;

	/// The end() iterator for this text part.
	/**
	 * Don't render the text any further than this.
	*/
	SGE_SYMBOL const_iterator
	end() const;

	/// The next iterator one should start with to draw the next part.
	SGE_SYMBOL const_iterator
	next_begin() const;
private:
	dim size_;

	const_iterator
		end_,
		next_begin_;
};

}
}

#endif
