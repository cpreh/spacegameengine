//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_ERROR_HANDLER_HPP_INCLUDED
#define SGE_OPENGL_STATE_ERROR_HANDLER_HPP_INCLUDED

#include <sge/opengl/state/check_error.hpp>
#include <fcppt/string.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace state
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4626)
FCPPT_PP_DISABLE_VC_WARNING(5027)

template<
	typename Actor
>
class error_handler
{
public:
	error_handler(
		Actor &&_actor,
		fcppt::string &&_name
	)
	:
		actor_{
			std::move(
				_actor
			)
		},
		name_{
			std::move(
				_name
			)
		}
	{
	}

	template<
		typename... Args
	>
	void
	operator()(
		Args && ..._args
	) const
	{
		actor_(
			std::forward<
				Args
			>(
				_args
			)...
		);

		sge::opengl::state::check_error(
			name_
		);
	}
private:
	Actor actor_;

	fcppt::string name_;
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
