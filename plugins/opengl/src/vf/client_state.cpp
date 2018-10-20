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


#include <sge/opengl/common.hpp>
#include <sge/opengl/vf/client_state.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
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
	fcppt::log::object &,
	Set &,
	typename Set::value_type
);

template<
	typename Set
>
void
erase_checked(
	fcppt::log::object &,
	Set &,
	typename Set::value_type
);

}

sge::opengl::vf::client_state::client_state(
	fcppt::log::object &_log
)
:
	log_{
		_log
	},
	normal_states_(),
	texture_states_(),
	attribute_states_()
{
}

void
sge::opengl::vf::client_state::enable(
	GLenum const _value
)
{
	::insert_checked(
		log_.get(),
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
		log_.get(),
		normal_states_,
		_value
	);
}

void
sge::opengl::vf::client_state::enable_texture(
	sge::renderer::texture::stage const _value
)
{
	::insert_checked(
		log_.get(),
		texture_states_,
		_value
	);
}

void
sge::opengl::vf::client_state::disable_texture(
	sge::renderer::texture::stage const _value
)
{
	::erase_checked(
		log_.get(),
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
		log_.get(),
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
		log_.get(),
		attribute_states_,
		_value
	);
}

sge::opengl::vf::client_state::normal_state_set const &
sge::opengl::vf::client_state::normal_states() const
{
	return
		normal_states_;
}

sge::opengl::vf::client_state::texture_state_set const &
sge::opengl::vf::client_state::texture_states() const
{
	return
		texture_states_;
}

sge::opengl::vf::client_state::index_state_set const &
sge::opengl::vf::client_state::attribute_states() const
{
	return
		attribute_states_;
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
	fcppt::log::object &_log,
	Set &_set,
	typename Set::value_type const _value
)
{
	if(
		!_set.insert(
			_value
		).second
	)
		FCPPT_LOG_ERROR(
			_log,
			fcppt::log::out
				<< FCPPT_TEXT("Duplicate state inserted in opengl::vf!")
				<< common_error
		);
}

template<
	typename Set
>
void
erase_checked(
	fcppt::log::object &_log,
	Set &_set,
	typename Set::value_type const _value
)
{
	if(
		!_set.erase(
			_value
		)
	)
		FCPPT_LOG_ERROR(
			_log,
			fcppt::log::out
				<< FCPPT_TEXT("State erased in opengl::vf that was not there!")
				<< common_error
		);
}

}
