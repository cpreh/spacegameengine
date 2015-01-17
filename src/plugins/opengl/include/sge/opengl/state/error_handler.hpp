/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_STATE_ERROR_HANDLER_HPP_INCLUDED
#define SGE_OPENGL_STATE_ERROR_HANDLER_HPP_INCLUDED

#include <sge/opengl/state/check_error.hpp>
#include <fcppt/nonassignable.hpp>
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
	typename Actor
>
class error_handler
{
	FCPPT_NONASSIGNABLE(
		error_handler
	);
public:
	error_handler(
		Actor const &_actor,
		fcppt::string &&_name
	)
	:
		actor_{
			_actor
		},
		name_{
			std::move(
				_name
			)
		}
	{
	}

	typedef
	void
	result_type;

	template<
		typename... Args
	>
	result_type
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
	Actor const actor_;

	fcppt::string const name_;
};

}
}
}

#endif
