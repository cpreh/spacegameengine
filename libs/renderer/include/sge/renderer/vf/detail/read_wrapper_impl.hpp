//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DETAIL_READ_WRAPPER_IMPL_HPP_INCLUDED
#define SGE_RENDERER_VF_DETAIL_READ_WRAPPER_IMPL_HPP_INCLUDED

#include <sge/renderer/vf/detail/read_wrapper_decl.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


template<
	typename T,
	typename Enable
>
inline
sge::renderer::vf::detail::read_wrapper<
	T,
	Enable
>::read_wrapper()
:
	value_(
		fcppt::no_init()
	)
{
}

template<
	typename T,
	typename Enable
>
inline
sge::renderer::vf::detail::read_wrapper<
	T,
	Enable
>::~read_wrapper()
{
}

template<
	typename T,
	typename Enable
>
inline
T &
sge::renderer::vf::detail::read_wrapper<
	T,
	Enable
>::get()
{
	return value_;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename T
>
inline
sge::renderer::vf::detail::read_wrapper<
	T,
	std::enable_if_t<
		std::is_fundamental<
			T
		>::value
	>
>::read_wrapper()
// Don't initialize value_
{
}

FCPPT_PP_POP_WARNING

template<
	typename T
>
inline
sge::renderer::vf::detail::read_wrapper<
	T,
	std::enable_if_t<
		std::is_fundamental<
			T
		>::value
	>
>::~read_wrapper()
{
}

template<
	typename T
>
inline
T &
sge::renderer::vf::detail::read_wrapper<
	T,
	std::enable_if_t<
		std::is_fundamental<
			T
		>::value
	>
>::get()
{
	return value_;
}

#endif
