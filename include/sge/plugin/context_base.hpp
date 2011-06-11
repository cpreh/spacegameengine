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


#ifndef SGE_PLUGIN_CONTEXT_BASE_HPP_INCLUDED
#define SGE_PLUGIN_CONTEXT_BASE_HPP_INCLUDED

#include <sge/plugin/context_base_fwd.hpp>
#include <sge/plugin/context_fwd.hpp>
#include <sge/plugin/base.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/symbol.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/weak_ptr.hpp>

namespace sge
{
namespace plugin
{

class context_base
{
public:
	SGE_PLUGIN_SYMBOL explicit
	context_base(
		fcppt::filesystem::path const &
	);

	SGE_PLUGIN_SYMBOL
	fcppt::filesystem::path const &
	path() const;

	SGE_PLUGIN_SYMBOL
	plugin::info const &
	info() const;
private:
	template<
		typename T
	> friend class context;

	fcppt::weak_ptr<
		plugin::base
	> ref_;

	fcppt::filesystem::path path_;

	plugin::info info_;
};

}
}

#endif
