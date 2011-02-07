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


#ifndef SGE_PLUGIN_INFO_HPP_INCLUDED
#define SGE_PLUGIN_INFO_HPP_INCLUDED

#include <sge/plugin/info_fwd.hpp>
#include <sge/plugin/capabilities_field.hpp>
#include <sge/plugin/min_core_version.hpp>
#include <sge/plugin/version.hpp>
#include <sge/symbol.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>
#include <fcppt/string.hpp>

namespace sge
{
namespace plugin
{

class info
{
public:
	SGE_SYMBOL
	info(
		fcppt::string const &name,
		fcppt::string const &description,
		plugin::version,
		plugin::min_core_version,
		plugin::capabilities_field const &
	);

	SGE_SYMBOL
	fcppt::string const &
	name() const;

	SGE_SYMBOL
	fcppt::string const &
	description() const;

	SGE_SYMBOL
	plugin::version const
	version() const;

	SGE_SYMBOL
	plugin::min_core_version const
	min_core_version() const;

	SGE_SYMBOL
	plugin::capabilities_field const &
	capabilities() const;
private:
	fcppt::string const name_;

	fcppt::string const description_;

	plugin::version version_;

	plugin::min_core_version min_core_version_;

	plugin::capabilities_field capabilities_;
};

}
}

#endif
