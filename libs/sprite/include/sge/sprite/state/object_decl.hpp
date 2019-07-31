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
#include <fcppt/noncopyable.hpp>


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
	FCPPT_NONCOPYABLE(
		object
	);
public:
	typedef StateChoices state_choices;

	typedef
	sge::sprite::state::detail::object_class<
		StateChoices
	>
	elements_type;

	typedef
	sge::sprite::state::parameters<
		state_choices
	>
	parameters_type;

	typedef
	sge::sprite::state::render_device<
		StateChoices
	>
	render_device;

	object(
		render_device &,
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
	render_device &renderer_;

	elements_type elements_;
};

}
}
}

#endif
