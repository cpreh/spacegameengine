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


#ifndef SGE_OPENGL_TEXTURE_WARN_MIN_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_WARN_MIN_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/to_array.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/dim/static.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

template<
	typename T,
	fcppt::math::size_type N
>
void
warn_min(
	fcppt::log::object &_log,
	fcppt::math::dim::static_<
		T,
		N
	> const &_dim,
	T const &_min,
	fcppt::string const &_what
)
{
	typedef
	fcppt::math::dim::static_<
		T,
		N
	>
	dim_type;

	for(
		auto const element
		:
		fcppt::math::to_array(
			_dim
		)
	)
		if(
			element < _min
		)
		{
			FCPPT_LOG_DEBUG(
				_log,
				fcppt::log::_
					<< FCPPT_TEXT("OpenGL implementations are not required to support ")
					<< _what
					<< FCPPT_TEXT("s smaller than ")
					<< fcppt::math::dim::fill<
						dim_type
					>(
						_min
					)
					<< FCPPT_TEXT(". Specified texture size was ")
					<< _dim
					<< FCPPT_TEXT('.')
			);

			return;
		}
}

}
}
}

#endif
