/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/plugin/capabilities.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/export.hpp>
#include <sge/string.hpp>
#include <sge/weak_ptr.hpp>

namespace sge
{
namespace plugin
{

class context_base
{
public:
	SGE_SYMBOL explicit context_base(
		fcppt::filesystem::path const &p
	);

	SGE_SYMBOL fcppt::string const &
	name() const;

	SGE_SYMBOL fcppt::string const &
	description() const;

	SGE_SYMBOL unsigned
	version() const;

	SGE_SYMBOL capabilities::type
	type() const;

	SGE_SYMBOL fcppt::filesystem::path const &
	path() const;
private:
	template<
		typename T
	> friend class context;

	fcppt::weak_ptr<base> ref;
	filesystem::path path_;
	fcppt::string name_;
	fcppt::string description_;
	unsigned version_;
	capabilities::type type_;
};

}
}

#endif
