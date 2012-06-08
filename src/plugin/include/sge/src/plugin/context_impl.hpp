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


#ifndef SGE_SRC_PLUGIN_CONTEXT_IMPL_HPP_INCLUDED
#define SGE_SRC_PLUGIN_CONTEXT_IMPL_HPP_INCLUDED

#include <sge/plugin/context.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/object.hpp>
#include <sge/src/plugin/load_info.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Type
>
sge::plugin::context<
	Type
>::context(
	boost::filesystem::path const &_path
)
:
	ref_(),
	path_(
		_path
	),
	info_(
		sge::plugin::load_info(
			_path
		)
	)
{
}

template<
	typename Type
>
typename sge::plugin::context<
	Type
>::object_shared_ptr
sge::plugin::context<
	Type
>::load()
{
	object_shared_ptr const ptr(
		ref_.lock()
	);

	if(
		ptr
	)
		return
			ptr;

	ptr_type const new_ptr(
		fcppt::make_shared_ptr<
			sge::plugin::object<
				Type
			>
		>(
			this->path()
		)
	);

	ref_ = new_ptr;

	return
		new_ptr;
}

template<
	typename Type
>
boost::filesystem::path const &
sge::plugin::context<
	Type
>::path() const
{
	return
		path_;
}

template<
	typename Type
>
sge::plugin::info const &
sge::plugin::context<
	Type
>::info() const
{
	return
		info_;
}

#endif
