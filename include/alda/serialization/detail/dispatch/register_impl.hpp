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


#ifndef ALDA_SERIALIZATION_DETAIL_DISPATCH_REGISTER_IMPL_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_DISPATCH_REGISTER_IMPL_HPP_INCLUDED

#include <alda/serialization/context_decl.hpp>
#include <alda/serialization/detail/dispatch/base_fwd.hpp>
#include <alda/serialization/detail/dispatch/concrete_decl.hpp>
#include <alda/serialization/detail/dispatch/register_decl.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/at.hpp>
#include <exception>
#include <fcppt/config/external_end.hpp>


template<
	typename TypeEnum,
	typename Message
>
alda::serialization::detail::dispatch::register_<
	TypeEnum,
	Message
>::register_(
	context &_context
)
{
	typedef fcppt::unique_ptr<
		alda::serialization::detail::dispatch::base<
			TypeEnum
		>
	> dispatcher_base_unique_ptr;

	typedef typename boost::mpl::at_c<
		typename Message::memory_type::types,
		0
	>::type msg_type;

	// TODO: fix this cast here, maybe replace majutsu::constant by an enum wrapper
	if(
		!fcppt::container::ptr::insert_unique_ptr_map(
			_context.handlers_,
			static_cast<
				typename TypeEnum::type
			>(
				msg_type::value
			),
			dispatcher_base_unique_ptr(
				fcppt::make_unique_ptr<
					alda::serialization::detail::dispatch::concrete<
						TypeEnum,
						Message
					>
				>()
			)
		).second
	)
	{
		fcppt::io::cerr()
			<< FCPPT_TEXT("Message type registered twice: ")
			<< static_cast<
				unsigned
			>(
				msg_type::value
			)
			<< FCPPT_TEXT('\n');

		std::terminate();
	}
}

template<
	typename TypeEnum,
	typename Message
>
alda::serialization::detail::dispatch::register_<
	TypeEnum,
	Message
>::~register_()
{
}

#endif
