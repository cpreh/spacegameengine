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


#ifndef SGE_PLUGIN_CONTEXT_IMPL_HPP_INCLUDED
#define SGE_PLUGIN_CONTEXT_IMPL_HPP_INCLUDED

#include <sge/plugin/context.hpp>
#include <sge/plugin/context_base.hpp>
#include <sge/plugin/plugin.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/shared_ptr.hpp>

template<
	typename T
>
sge::plugin::context<T>::context(
	context_base &base_
)
:
	base_(&base_)
{}

template<
	typename T
>
typename sge::plugin::context<T>::ptr_type
sge::plugin::context<T>::load()
{
	fcppt::shared_ptr<
		base
	> const ptr_base(
		base_->ref.lock()
	);

	if(ptr_base)
		return fcppt::polymorphic_pointer_cast<
			plugin<T>
		>(
			ptr_base
		);

	fcppt::shared_ptr<
		plugin<
			T
		>
	> const new_ptr(
		fcppt::make_shared_ptr<
			plugin<T>
		>(
			base_->path()
		)
	);

	base_->ref = new_ptr;

	return new_ptr;
}

template<
	typename T
>
sge::plugin::context_base const &
sge::plugin::context<T>::info() const
{
	return *base_;
}

#endif
