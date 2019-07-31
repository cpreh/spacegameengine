//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_WARN_MIN_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_WARN_MIN_HPP_INCLUDED

#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
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
				fcppt::log::out
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
			)

			return;
		}
}

}
}
}

#endif
