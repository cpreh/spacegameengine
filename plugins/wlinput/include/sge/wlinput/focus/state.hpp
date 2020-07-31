//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WLINPUT_FOCUS_STATE_HPP_INCLUDED
#define SGE_WLINPUT_FOCUS_STATE_HPP_INCLUDED

#include <sge/wlinput/focus/keymap_ref.hpp>
#include <sge/wlinput/focus/state_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xkbcommon/xkbcommon.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace wlinput
{
namespace focus
{

class state
{
	FCPPT_NONCOPYABLE(
		state
	);
public:
	explicit
	state(
		sge::wlinput::focus::keymap_ref
	);

	state(
		state &&
	)
	noexcept;

	state &
	operator=(
		state &&
	)
	noexcept;

	~state();

	[[nodiscard]]
	xkb_state *
	get() const;
private:
	xkb_state *state_;
};

}
}
}

#endif
