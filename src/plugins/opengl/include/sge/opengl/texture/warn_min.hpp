/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/log/global.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/output.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

template<
	typename T,
	typename N,
	typename S
>
void
warn_min(
	fcppt::math::dim::basic<
		T,
		N,
		S
	> const &_dim,
	T const &_min,
	fcppt::string const &_what
)
{
	typedef fcppt::math::dim::basic<T, N, S> dim_type;

	for(
		typename dim_type::const_iterator it(
			_dim.begin()
		);
		it != _dim.end();
		++it
	)
		if(
			*it < _min
		)
		{
			FCPPT_LOG_WARNING(
				log::global(),
				fcppt::log::_
					<< FCPPT_TEXT("OpenGL implementations are not required to support ")
					<< _what
					<< FCPPT_TEXT("s smaller than ")
					<< fcppt::math::dim::fill<
						N::value
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
