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


#include <sge/log/option_container.hpp>
#include <sge/systems/log_redirect_path.hpp>
#include <sge/systems/log_settings.hpp>
#include <sge/systems/optional_log_context_ref.hpp>
#include <sge/systems/optional_log_redirect_path.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::systems::log_settings::log_settings(
	sge::log::option_container const &_options
)
:
	options_(
		_options
	),
	redirect_(),
	log_context_()
{
}

sge::systems::log_settings &
sge::systems::log_settings::redirect(
	boost::filesystem::path const &_path
)
{
	redirect_ =
		sge::systems::optional_log_redirect_path(
			sge::systems::log_redirect_path(
				_path
			)
		);

	return
		*this;
}

sge::systems::log_settings &
sge::systems::log_settings::log_context(
	fcppt::log::context &_log_context
)
{
	log_context_ =
		sge::systems::optional_log_context_ref{
			fcppt::make_ref(
				_log_context
			)
		};

	return
		*this;
}

sge::log::option_container const &
sge::systems::log_settings::options() const
{
	return
		options_;
}

sge::systems::optional_log_redirect_path const &
sge::systems::log_settings::redirect() const
{
	return
		redirect_;
}

sge::systems::optional_log_context_ref const &
sge::systems::log_settings::log_context() const
{
	return
		log_context_;
}
