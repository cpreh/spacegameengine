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


#include "../client_state.hpp"
#include <sge/log/global.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


namespace
{

template<
	typename Set
>
void
insert_checked(
	Set &,
	typename Set::value_type
);

template<
	typename Set
>
void
erase_checked(
	Set &,
	typename Set::value_type
);

}

void
sge::opengl::vf::client_state::enable(
	GLenum const _value
)
{
	::insert_checked(
		normal_states_,
		_value
	);
}

void
sge::opengl::vf::client_state::disable(
	GLenum const _value
)
{
	::erase_checked(
		normal_states_,
		_value
	);
}

void
sge::opengl::vf::client_state::enable_texture(
	renderer::stage const _value
)
{
	::insert_checked(
		texture_states_,
		_value
	);
}

void
sge::opengl::vf::client_state::disable_texture(
	renderer::stage const _value
)
{
	::erase_checked(
		texture_states_,
		_value
	);
}

void
sge::opengl::vf::client_state::enable_attribute(
	GLuint const _value
)
{
	::insert_checked(
		attribute_states_,
		_value
	);
}

void
sge::opengl::vf::client_state::disable_attribute(
	GLuint const _value
)
{
	::erase_checked(
		attribute_states_,
		_value
	);
}

sge::opengl::vf::client_state::normal_state_set const &
sge::opengl::vf::client_state::normal_states() const
{
	return normal_states_;
}

sge::opengl::vf::client_state::texture_state_set const &
sge::opengl::vf::client_state::texture_states() const
{
	return texture_states_;
}

sge::opengl::vf::client_state::index_state_set const &
sge::opengl::vf::client_state::attribute_states() const
{
	return attribute_states_;
}

namespace
{

fcppt::string const common_error(
	FCPPT_TEXT(" This usually happens if you forget to call renderer::device::unset_vertex_buffer() before setting a new one.")
);

template<
	typename Set
>
void
insert_checked(
	Set &_set,
	typename Set::value_type const _value
)
{
	if(
		!_set.insert(
			_value
		).second
	)
		FCPPT_LOG_WARNING(
			sge::log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("Duplicate state inserted in opengl::vf!")
				<< common_error
		);
}

template<
	typename Set
>
void
erase_checked(
	Set &_set,
	typename Set::value_type const _value
)
{
	if(
		!_set.erase(
			_value
		)
	)
		FCPPT_LOG_WARNING(
			sge::log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("State erased in opengl::vf that was not there!")
				<< common_error
		);
}

}
