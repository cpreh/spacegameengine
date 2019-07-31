//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_DETAIL_OPTIONS_CLASS_IMPL_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_OPTIONS_CLASS_IMPL_HPP_INCLUDED

#include <sge/sprite/state/detail/options_class_element.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/algorithms/remove.hpp>
#include <brigand/algorithms/transform.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/functions/logical/and.hpp>
#include <brigand/functions/logical/not.hpp>
#include <brigand/sequences/append.hpp>
#include <brigand/types/args.hpp>
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
	brigand::and_<
		brigand::not_<
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
	fcppt::record::object<
		brigand::append<
			brigand::transform<
				brigand::filter<
					typename
					StateChoices::optional_elements,
					brigand::bind<
						has_option,
						brigand::_1
					>
				>,
				brigand::bind<
					option_class_element,
					brigand::_1
				>
			>,
			brigand::transform<
				typename
				StateChoices::optional_elements,
				brigand::bind<
					sge::sprite::state::detail::options_class_element,
					brigand::_1
				>
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
