//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WLINPUT_XKB_CONTEXT_HPP_INCLUDED
#define SGE_WLINPUT_XKB_CONTEXT_HPP_INCLUDED

#include <sge/wlinput/xkb_context_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xkbcommon/xkbcommon.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace wlinput
{

class xkb_context
{
	FCPPT_NONMOVABLE(
		xkb_context
	);
public:
	xkb_context();

	~xkb_context();

	[[nodiscard]]
	::xkb_context *
	get() const;
private:
	::xkb_context *context_;
};

}
}

#endif
