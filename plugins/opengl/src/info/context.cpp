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


#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/fun_ptr.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/extension_set.hpp>
#include <sge/opengl/info/get_extensions.hpp>
#include <sge/opengl/info/get_version.hpp>
#include <sge/opengl/info/version.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/info.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


#undef major
#undef minor

sge::opengl::info::context::context(
	fcppt::log::object &_log,
	sge::opengl::backend::current const &_current
)
:
	current_(
		_current
	),
	version_(
		sge::opengl::info::get_version(
			_current
		)
	),
	extensions_(
		sge::opengl::info::get_extensions(
			_current
		)
	)
{
	FCPPT_LOG_INFO(
		_log,
		fcppt::log::_
			<< FCPPT_TEXT("Version is: ")
			<< version_.major()
			<< FCPPT_TEXT('.')
			<< version_.minor()
	);
}

sge::opengl::info::context::~context()
{
}

sge::opengl::info::version
sge::opengl::info::context::version() const
{
	return
		version_;
}

sge::opengl::info::extension_set const &
sge::opengl::info::context::extensions() const
{
	return
		extensions_;
}

sge::opengl::backend::fun_ptr
sge::opengl::info::context::load_function(
	std::string const &_name
) const
{
	return
		current_.load_function(
			_name
		);
}
