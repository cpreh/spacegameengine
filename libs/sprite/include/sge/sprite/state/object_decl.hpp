//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_OBJECT_DECL_HPP_INCLUDED
#define SGE_SPRITE_STATE_OBJECT_DECL_HPP_INCLUDED

#include <sge/sprite/state/object_fwd.hpp>
#include <sge/sprite/state/parameters_fwd.hpp>
#include <sge/sprite/state/render_device.hpp>
#include <sge/sprite/state/detail/object_class.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace sprite
{
namespace state
{

template<
	typename StateChoices
>
class object
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	using
	state_choices
	=
	StateChoices;

	using
	elements_type
	=
	sge::sprite::state::detail::object_class<
		StateChoices
	>;

	using
	parameters_type
	=
	sge::sprite::state::parameters<
		state_choices
	>;

	using
	render_device
	=
	sge::sprite::state::render_device<
		StateChoices
	>;

	object(
		fcppt::reference<
			render_device
		>,
		parameters_type const &
	);

	~object();

	elements_type &
	elements();

	elements_type const &
	elements() const;

	render_device &
	renderer() const;
private:
	fcppt::reference<
		render_device
	> const renderer_;

	elements_type elements_;
};

}
}
}

#endif
