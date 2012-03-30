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


#ifndef ALDA_CALL_DETAIL_MAKE_INSTANCE_HPP_INCLUDED
#define ALDA_CALL_DETAIL_MAKE_INSTANCE_HPP_INCLUDED

#include <alda/call/detail/concrete_decl.hpp>
#include <alda/message/detail/extract_id.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/container/ptr/replace_unique_ptr.hpp>


namespace alda
{
namespace call
{
namespace detail
{

template<
	typename TypeEnum,
	typename Callee,
	typename InstanceArray
>
class make_instance
{
	FCPPT_NONASSIGNABLE(
		make_instance
	);
public:
	explicit
	make_instance(
		InstanceArray &_instances
	)
	:
		instances_(
			_instances
		)
	{
	}

	template<
		typename Message
	>
	void
	operator()() const
	{
		fcppt::container::ptr::replace_unique_ptr(
			instances_,
			alda::message::detail::extract_id<
				typename Message::types
			>::type::value,
			fcppt::make_unique_ptr<
				alda::call::detail::concrete<
					TypeEnum,
					Callee,
					Message
				>
			>()
		);
	}
private:
	InstanceArray &instances_;
};

}
}
}

#endif
