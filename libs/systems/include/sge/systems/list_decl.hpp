//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_LIST_DECL_HPP_INCLUDED
#define SGE_SYSTEMS_LIST_DECL_HPP_INCLUDED

#include <sge/systems/list_fwd.hpp>
#include <fcppt/container/tuple/push_back_result.hpp>
#include <fcppt/type_traits/remove_cv_ref_t.hpp>


namespace sge
{
namespace systems
{

template<
	typename Inits
>
class list
{
public:
	explicit
	list(
		Inits &&
	);

	template<
		typename Param
	>
	[[nodiscard]]
	list<
		fcppt::container::tuple::push_back_result<
			Inits,
			fcppt::type_traits::remove_cv_ref_t<
				Param
			>
		>
	>
	operator()(
		Param &&
	) const;

	[[nodiscard]]
	Inits &
	get();

	[[nodiscard]]
	Inits const &
	get() const;
private:
	Inits inits_;
};

}
}

#endif
