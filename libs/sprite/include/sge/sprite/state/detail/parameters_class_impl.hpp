//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_DETAIL_PARAMETERS_CLASS_IMPL_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_PARAMETERS_CLASS_IMPL_HPP_INCLUDED

#include <fcppt/record/element.hpp>
#include <fcppt/record/from_list.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace state
{
namespace detail
{

template<
	typename StateChoices
>
struct parameters_class_impl
{
private:
	template<
		typename Type
	>
	using
	has_parameter
	=
	std::conjunction<
		typename
		Type::persistent,
		typename
		Type::has_parameter
	>;

	template<
		typename Type
	>
	using
	parameter_class_element
	=
	fcppt::record::element<
		typename
		Type::parameter_role,
		typename
		Type::optional_extra_parameters
	>;
public:
	using
	type
	=
	fcppt::record::from_list<
		metal::transform<
			metal::lambda<
				parameter_class_element
			>,
			metal::copy_if<
				typename
				StateChoices::optional_elements,
				metal::trait<
					has_parameter
				>
			>
		>
	>;
};

}
}
}
}

#endif
