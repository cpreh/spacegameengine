//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_WARN_POW2_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_WARN_POW2_HPP_INCLUDED

#include <fcppt/not.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/math/is_power_of_2.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/to_array.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/math/dim/output.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

template<
	typename T,
	fcppt::math::size_type N,
	typename S
>
void
warn_pow2(
	fcppt::log::object &_log, // NOLINT(google-runtime-references)
	fcppt::math::dim::object<
		T,
		N,
		S
	> const &_dim,
	fcppt::string const &_what
)
{
	for(
		auto const element
		:
		fcppt::math::to_array(
			_dim
		)
	)
	{
		if(
			fcppt::not_(
				fcppt::math::is_power_of_2(
					element
				)
			)
		)
		{
			FCPPT_LOG_DEBUG(
				_log,
				fcppt::log::out
					<< FCPPT_TEXT("OpenGL implementations are not required to support ")
					<< _what
					<< FCPPT_TEXT("s with dimensions that are not a power of 2.")\
					FCPPT_TEXT(" Specified size was ")
					<< _dim
					<< FCPPT_TEXT('.')
			)

			return;
		}
	}
}

}
}
}

#endif
