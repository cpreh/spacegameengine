/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "version_fun.hpp"
#include <sge/plugin/context_base.hpp>
#include <sge/plugin/info.hpp>
#include <sge/library/object_impl.hpp>

sge::plugin::context_base::context_base(
	fcppt::filesystem::path const &path_
)
:
	path_(path_)
{
	typedef void (*version_function)(sge::plugin::info*);

	library::object lib(path());

	version_function vf(
		lib.load_function<version_function>(version_fun)
	);

	info info_;

	vf(&info_);

	name_ = info_.name;
	description_ = info_.description;
	version_ = info_.plugin_version;
	type_ = info_.type;
}

fcppt::string const &
sge::plugin::context_base::name() const
{
	return name_;
}

fcppt::string const &
sge::plugin::context_base::description() const
{
	return description_;
}

unsigned
sge::plugin::context_base::version() const
{
	return version_;
}

sge::plugin::capabilities::type
sge::plugin::context_base::type() const
{
	return type_;
}

fcppt::filesystem::path const &
sge::plugin::context_base::path() const
{
	return path_;
}
