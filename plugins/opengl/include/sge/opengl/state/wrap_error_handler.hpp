//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_WRAP_ERROR_HANDLER_HPP_INCLUDED
#define SGE_OPENGL_STATE_WRAP_ERROR_HANDLER_HPP_INCLUDED

#include <sge/opengl/state/error_handler.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace state
{

template<
	typename Result,
	typename Actor
>
Result
wrap_error_handler(
	Actor const &_actor,
	// TODO: Pass a function returning a string here
	fcppt::string &&_name
)
{
	return
		Result{
			sge::opengl::state::error_handler<
				Actor
			>(
				_actor,
				std::move(
					_name
				)
			)
		};
}

}
}
}

#endif
