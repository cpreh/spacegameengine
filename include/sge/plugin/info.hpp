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


#ifndef SGE_PLUGIN_INFO_HPP_INCLUDED
#define SGE_PLUGIN_INFO_HPP_INCLUDED

#include <sge/plugin/capabilities_field.hpp>
#include <sge/plugin/description.hpp>
#include <sge/plugin/flags_field.hpp>
#include <sge/plugin/info_fwd.hpp>
#include <sge/plugin/min_core_version.hpp>
#include <sge/plugin/name.hpp>
#include <sge/plugin/version.hpp>
#include <sge/plugin/detail/symbol.hpp>


namespace sge
{
namespace plugin
{

class info
{
public:
	SGE_PLUGIN_DETAIL_SYMBOL
	info(
		sge::plugin::name const &,
		sge::plugin::description const &,
		sge::plugin::version,
		sge::plugin::min_core_version,
		sge::plugin::capabilities_field const &,
		sge::plugin::flags_field const &
	);

	SGE_PLUGIN_DETAIL_SYMBOL
	sge::plugin::name const &
	name() const;

	SGE_PLUGIN_DETAIL_SYMBOL
	sge::plugin::description const &
	description() const;

	SGE_PLUGIN_DETAIL_SYMBOL
	sge::plugin::version const
	version() const;

	SGE_PLUGIN_DETAIL_SYMBOL
	sge::plugin::min_core_version const
	min_core_version() const;

	SGE_PLUGIN_DETAIL_SYMBOL
	sge::plugin::capabilities_field const &
	capabilities() const;

	SGE_PLUGIN_DETAIL_SYMBOL
	sge::plugin::flags_field const &
	flags() const;
private:
	sge::plugin::name name_;

	sge::plugin::description description_;

	sge::plugin::version version_;

	sge::plugin::min_core_version min_core_version_;

	sge::plugin::capabilities_field capabilities_;

	sge::plugin::flags_field flags_;
};

}
}

#endif
