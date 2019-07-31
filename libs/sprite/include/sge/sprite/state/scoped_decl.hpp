//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_STATE_SCOPED_DECL_HPP_INCLUDED
#define SGE_SPRITE_STATE_SCOPED_DECL_HPP_INCLUDED

#include <sge/sprite/state/object_fwd.hpp>
#include <sge/sprite/state/options_decl.hpp>
#include <sge/sprite/state/render_context.hpp>
#include <sge/sprite/state/render_device.hpp>
#include <sge/sprite/state/scoped_fwd.hpp>
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
class scoped
{
	FCPPT_NONCOPYABLE(
		scoped
	);
public:
	typedef
	sge::sprite::state::render_device<
		StateChoices
	>
	render_device;

	typedef
	sge::sprite::state::render_context<
		StateChoices
	>
	render_context;

	typedef sge::sprite::state::options<
		StateChoices
	> state_options;

	typedef sge::sprite::state::object<
		StateChoices
	> state_object;

	scoped(
		render_device &,
		render_context &,
		state_options const &,
		state_object &
	);

	~scoped();
private:
	render_context &render_context_;

	state_options const options_;
};

}
}
}

#endif
