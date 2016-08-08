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


#ifndef SGE_PLUGIN_IMPL_CONTEXT_IMPL_HPP_INCLUDED
#define SGE_PLUGIN_IMPL_CONTEXT_IMPL_HPP_INCLUDED

#include <sge/plugin/context.hpp>
#include <sge/plugin/info_fwd.hpp>
#include <sge/plugin/object.hpp>
#include <sge/plugin/impl/context_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


template<
	typename Type
>
sge::plugin::context<
	Type
>::context(
	sge::plugin::context_base &_context_base
)
:
	context_base_(
		_context_base
	)
{
}

template<
	typename Type
>
sge::plugin::context<
	Type
>::context(
	context const &_other
)
:
	context_base_(
		_other.context_base_
	)
{
}

template<
	typename Type
>
sge::plugin::context<
	Type
>::~context()
{
}

template<
	typename Type
>
typename
sge::plugin::context<
	Type
>::object
sge::plugin::context<
	Type
>::load() const
{
	return
		sge::plugin::object<
			Type
		>(
			context_base_.load()
		);
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
		context_base_.path();
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
		context_base_.info();
}

#endif
