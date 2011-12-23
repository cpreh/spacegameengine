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


#ifndef SGE_SRC_PLUGIN_CONTEXT_IMPL_HPP_INCLUDED
#define SGE_SRC_PLUGIN_CONTEXT_IMPL_HPP_INCLUDED

#include <sge/plugin/context.hpp>
#include <sge/plugin/context_base.hpp>
#include <sge/plugin/object.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/shared_ptr_impl.hpp>
#include <fcppt/static_pointer_cast.hpp>


template<
	typename T
>
sge::plugin::context<T>::context(
	context_base &_base
)
:
	base_(&_base)
{
}

template<
	typename T
>
typename sge::plugin::context<T>::ptr_type
sge::plugin::context<T>::load()
{
	typedef fcppt::shared_ptr<
		plugin::base
	> base_ptr;

	base_ptr const ptr(
		base_->ref_.lock()
	);

	if(
		ptr
	)
		return
			fcppt::static_pointer_cast<
				plugin::object<T>
			>(
				ptr
			);

	ptr_type const new_ptr(
		fcppt::make_shared_ptr<
			plugin::object<
				T
			>
		>(
			base_->path()
		)
	);

	base_->ref_ = new_ptr;

	return new_ptr;
}

template<
	typename T
>
sge::plugin::context_base const &
sge::plugin::context<T>::base() const
{
	return *base_;
}

#endif
