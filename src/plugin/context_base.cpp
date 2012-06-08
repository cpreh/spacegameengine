/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/plugin/cache.hpp>
#include <sge/plugin/flags.hpp>
#include <sge/plugin/optional_cache_ref.hpp>
#include <sge/plugin/library/object_shared_ptr.hpp>
#include <sge/src/plugin/context_base.hpp>
#include <sge/src/plugin/load_info.hpp>
#include <sge/src/plugin/library/object.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::plugin::context_base::context_base(
	sge::plugin::optional_cache_ref const &_cache,
	boost::filesystem::path const &_path
)
:
	cache_(
		_cache
	),
	path_(
		_path
	),
	info_(
		sge::plugin::load_info(
			_path
		)
	),
	library_ptr_()
{
}

sge::plugin::context_base::~context_base()
{
}

boost::filesystem::path const &
sge::plugin::context_base::path() const
{
	return
		path_;
}

sge::plugin::info const &
sge::plugin::context_base::info() const
{
	return
		info_;
}

sge::plugin::library::object_shared_ptr const
sge::plugin::context_base::load()
{
	{
		sge::plugin::library::object_shared_ptr const ptr(
			library_ptr_.lock()
		);

		if(
			ptr
		)
			return ptr;
	}

	sge::plugin::library::object_shared_ptr const ret(
		fcppt::make_shared_ptr<
			sge::plugin::library::object
		>(
			path_
		)
	);

	library_ptr_ = ret;

	if(
		cache_
		&&
		(
			this->info().flags()
			&
			sge::plugin::flags::delayed_unload
		)
	)
		cache_->add(
			ret
		);

	return
		ret;
}
