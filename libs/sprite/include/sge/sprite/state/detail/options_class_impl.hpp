//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_DETAIL_OPTIONS_CLASS_IMPL_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_OPTIONS_CLASS_IMPL_HPP_INCLUDED

#include <sge/sprite/state/detail/options_class_element.hpp>
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
struct options_class_impl
{
private:
	template<
		typename Type
	>
	using
	has_option
	=
	std::conjunction<
		std::negation<
			typename
			Type::persistent
		>,
		typename
		Type::has_parameter
	>;

	template<
		typename Type
	>
	using
	option_class_element
	=
	fcppt::record::element<
		typename
		Type::option_role,
		typename
		Type::optional_extra_option
	>;
public:
	typedef
	fcppt::record::from_list<
		metal::join<
			metal::transform<
				metal::lambda<
					option_class_element
				>,
				metal::copy_if<
					typename
					StateChoices::optional_elements,
					metal::trait<
						has_option
					>
				>
			>,
			metal::transform<
				metal::lambda<
					sge::sprite::state::detail::options_class_element
				>,
				typename
				StateChoices::optional_elements
			>
		>
	>
	type;
};

}
}
}
}

#endif
