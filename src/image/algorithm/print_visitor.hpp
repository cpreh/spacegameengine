/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_IMAGE_ALGORITHM_PRINT_VISITOR_HPP_INCLUDED
#define SGE_IMAGE_ALGORITHM_PRINT_VISITOR_HPP_INCLUDED

#include <fcppt/io/ostream.hpp>
#include <fcppt/nonassignable.hpp>
#include <mizuiro/image/algorithm/print.hpp>

namespace sge
{
namespace image
{
namespace algorithm
{

class print_visitor
{
	FCPPT_NONASSIGNABLE(
		print_visitor
	);
public:
	typedef void result_type;

	explicit print_visitor(
		fcppt::io::ostream &_ostream
	)
	:
		ostream_(_ostream)
	{
	}

	template<
		typename View
	>
	result_type
	operator()(
		View const &_view
	) const
	{
		mizuiro::image::algorithm::print(
			ostream_,
			_view
		);
	}
private:
	fcppt::io::ostream &ostream_;
};

}
}
}

#endif
