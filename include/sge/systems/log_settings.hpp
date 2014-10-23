/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SYSTEMS_LOG_SETTINGS_HPP_INCLUDED
#define SGE_SYSTEMS_LOG_SETTINGS_HPP_INCLUDED

#include <sge/log/option_container.hpp>
#include <sge/systems/log_settings_fwd.hpp>
#include <sge/systems/optional_log_redirect_path.hpp>
#include <sge/systems/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace systems
{

class log_settings
{
public:
	SGE_SYSTEMS_DETAIL_SYMBOL
	explicit
	log_settings(
		sge::log::option_container const &
	);

	SGE_SYSTEMS_DETAIL_SYMBOL
	sge::systems::log_settings &
	redirect(
		boost::filesystem::path const &
	);

	sge::log::option_container const &
	options() const;

	sge::systems::optional_log_redirect_path const &
	redirect() const;
private:
	sge::log::option_container options_;

	sge::systems::optional_log_redirect_path redirect_;
};

}
}

#endif
