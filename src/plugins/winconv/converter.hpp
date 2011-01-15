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


#ifndef SGE_WINCONV_CONVERTER_HPP_INCLUDED
#define SGE_WINCONV_CONVERTER_HPP_INCLUDED

#include <sge/charconv/converter.hpp>
#include <sge/charconv/conversion_status.hpp>
#include <sge/charconv/input_range.hpp>
#include <sge/charconv/source_encoding.hpp>
#include <sge/charconv/dest_encoding.hpp>
#include <sge/charconv/output_range.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace winconv
{

class converter
:
	public sge::charconv::converter
{
	FCPPT_NONCOPYABLE(
		converter
	)
public:
	converter(
		charconv::source_encoding const &source,
		charconv::dest_encoding const &dest
	);

	~converter();

	charconv::conversion_status::type
	convert(
		charconv::input_range &,
		charconv::output_range &
	);
};

}
}

#endif
