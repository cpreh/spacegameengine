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


#ifndef ALDA_CALL_OBJECT_DECL_HPP_INCLUDED
#define ALDA_CALL_OBJECT_DECL_HPP_INCLUDED

#include <alda/call/default_function_fwd.hpp>
#include <alda/call/object_fwd.hpp>
#include <alda/call/detail/base_fwd.hpp>
#include <alda/message/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_array.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace call
{

template<
	typename TypeEnum,
	typename Messages,
	typename Callee
>
class object
{
	FCPPT_NONCOPYABLE(
		object
	);

	typedef typename Callee::result_type result_type;

	typedef alda::call::detail::base<
		TypeEnum,
		Callee
	> base;
public:
	typedef typename alda::call::default_function<
		TypeEnum,
		result_type
	>::type default_function;

	typedef alda::message::base<
		TypeEnum
	> message_base;

	object();

	~object();

	result_type
	operator()(
		message_base const &,
		Callee &,
		default_function const &
	) const;
private:
	typedef boost::ptr_array<
		base,
		TypeEnum::size::value
	> instance_array;

	instance_array instances_;
};

}
}

#endif
