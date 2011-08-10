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


#ifndef MAJUTSU_CLASS_HPP_INCLUDED
#define MAJUTSU_CLASS_HPP_INCLUDED

#include <majutsu/role_return_type.hpp>
#include <majutsu/memory/init_count.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/container/generation/make_vector.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/static_assert.hpp>

#ifndef MAJUTSU_MAX_CTOR_ARGS
#define MAJUTSU_MAX_CTOR_ARGS 20
#endif

namespace majutsu
{

template<
	typename Type,
	template<
		typename
	> class Memory
>
struct class_
{
	typedef Type types;

	typedef Memory<
		types
	> memory_type;

	class_()
	:
		memory_()
	{}

	class_(
		class_ const &_other
	)
	:
		memory_(
			_other.memory_
		)
	{}

	template<
		typename Argument
	>
	explicit class_(
		Argument const &_argument,
		typename boost::disable_if<
			boost::fusion::traits::is_sequence<
				Argument
			>,
			void
		>::type * = 0
	)
	:
		memory_(
			boost::fusion::make_vector(
				_argument
			)
		)
	{
		BOOST_STATIC_ASSERT(
			memory::init_count<
				memory_type
			>::value
			== 1u
		);
	}

#define MAJUTSU_CLASS_MAKE_VARIADIC_CTOR(z, n, text)\
template<\
        BOOST_PP_ENUM_PARAMS_Z(\
                z,\
                n,\
                typename T\
        )>\
explicit class_(\
        BOOST_PP_ENUM_BINARY_PARAMS_Z(\
                z,\
		n,\
                const T,\
                &t\
        )\
)\
:\
	memory_(\
		boost::fusion::make_vector(\
			BOOST_PP_ENUM_PARAMS_Z(\
				z,\
				n,\
				t\
			)\
		)\
	)\
{\
	BOOST_STATIC_ASSERT(\
		memory::init_count<\
			memory_type\
		>::value == n\
	);\
}

BOOST_PP_REPEAT_FROM_TO(
	2,
        MAJUTSU_MAX_CTOR_ARGS,
        MAJUTSU_CLASS_MAKE_VARIADIC_CTOR,
        void
)

#undef MAJUTSU_CLASS_MAKE_VARIADIC_CTOR

	template<
		typename Vector
	>
	explicit class_(
		Vector const &_initializers,
		typename boost::enable_if<
			boost::fusion::traits::is_sequence<
				Vector
			>,
			void
		>::type * = 0
	)
	:
		memory_(
			_initializers
		)
	{
		BOOST_STATIC_ASSERT(
			memory::init_count<
				memory_type
			>::value
			== boost::mpl::size<
				Vector
			>::value
		);
	}

	template<
		typename Role,
		typename T
	>
	void
	set(
		T const &_value
	)
	{
		memory_.set<
			Role
		>(
			_value
		);
	}

	template<
		typename Role
	>
	typename role_return_type<
		typename memory_type::types,
		Role
	>::type
	get() const
	{
		return
			memory_.get<
				Role
			>();
	}

	memory_type &
	memory()
	{
		return memory_;
	}

	memory_type const &
	memory() const
	{
		return memory_;
	}
private:
	memory_type memory_;
};

}

#endif
