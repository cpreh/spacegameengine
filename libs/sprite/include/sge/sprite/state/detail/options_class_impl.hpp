//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_DETAIL_OPTIONS_CLASS_IMPL_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_OPTIONS_CLASS_IMPL_HPP_INCLUDED

#include <sge/sprite/state/detail/options_class_element.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/append.hpp>
#include <fcppt/mpl/list/keep_if.hpp>
#include <fcppt/mpl/list/map.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/from_list.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::sprite::state::detail
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
	using
	type
	=
	fcppt::record::from_list<
		fcppt::mpl::list::append<
			fcppt::mpl::list::map<
				fcppt::mpl::list::keep_if<
					typename
					StateChoices::optional_elements,
					fcppt::mpl::lambda<
						has_option
					>
				>,
				fcppt::mpl::lambda<
					option_class_element
				>
			>,
			fcppt::mpl::list::map<
				typename
				StateChoices::optional_elements,
				fcppt::mpl::lambda<
					sge::sprite::state::detail::options_class_element
				>
			>
		>
	>;
};

}

#endif
