//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_DETAIL_OBJECT_CLASS_IMPL_HPP_INCLUDED
#define SGE_SPRITE_STATE_DETAIL_OBJECT_CLASS_IMPL_HPP_INCLUDED

#include <fcppt/optional/object_impl.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/algorithms/transform.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/types/args.hpp>
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
struct object_class_impl
{
private:
	template<
		typename Type
	>
	using
	object_class_element
	=
	fcppt::record::element<
		typename
		Type::role,
		std::conditional_t<
			Type::persistent::value,
			typename
			Type::state_type,
			fcppt::optional::object<
				typename
				Type::state_type
			>
		>
	>;
public:
	typedef
	fcppt::record::object<
		brigand::transform<
			typename
			StateChoices::optional_elements,
			brigand::bind<
				object_class_element,
				brigand::_1
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
