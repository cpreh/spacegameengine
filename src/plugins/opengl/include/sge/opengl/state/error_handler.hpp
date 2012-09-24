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


#ifndef SGE_OPENGL_STATE_ERROR_HANDLER_HPP_INCLUDED
#define SGE_OPENGL_STATE_ERROR_HANDLER_HPP_INCLUDED

#include <sge/opengl/state/check_error.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/string.hpp>


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
		fcppt::string const &_name
	)
	:
		actor_(
			_actor
		),
		name_(
			_name
		)
	{
	}

	typedef void result_type;

	result_type
	operator()() const
	{
		actor_();

		this->check_error();
	}

	template<
		typename Arg1
	>
	result_type
	operator()(
		Arg1 const &_arg1
	) const
	{
		actor_(
			_arg1
		);

		this->check_error();
	}
private:
	void
	check_error() const
	{
		sge::opengl::state::check_error(
			name_
		);
	}

	Actor const actor_;

	fcppt::string const name_;
};

}
}
}

#endif
