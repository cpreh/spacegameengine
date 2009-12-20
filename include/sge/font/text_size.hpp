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


#ifndef SGE_FONT_TEXT_SIZE_HPP_INCLUDED
#define SGE_FONT_TEXT_SIZE_HPP_INCLUDED

#include <sge/font/dim.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <sge/symbol.hpp>
#include <sge/string.hpp>

namespace sge
{
namespace font
{

class text_size {
public:
	typedef string::const_iterator const_iterator;

	SGE_SYMBOL text_size(
		dim const &sz,
		string::const_iterator end,
		string::const_iterator next_begin);

	SGE_SYMBOL dim const &size() const;
	SGE_SYMBOL const_iterator end() const;
	SGE_SYMBOL const_iterator next_begin() const;
private:
	dim            size_;
	const_iterator end_,
	               next_begin_;
};

}
}

#endif
