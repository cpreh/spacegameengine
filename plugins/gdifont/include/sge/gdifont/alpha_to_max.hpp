//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GDIFONT_ALPHA_TO_MAX_HPP_INCLUDED
#define SGE_GDIFONT_ALPHA_TO_MAX_HPP_INCLUDED

#include <sge/gdifont/a8_view.hpp>
#include <sge/image/mizuiro_color_traits.hpp>
#include <mizuiro/color/access/channel_max.hpp>
#include <mizuiro/color/channel/alpha.hpp>


namespace sge
{
namespace gdifont
{

struct alpha_to_max
{
	void
	operator()(
		sge::gdifont::a8_view::reference _color
	) const
	{
		if(
			_color.get(
				mizuiro::color::channel::alpha()
			)
			> 0
		)
			_color.set(
				mizuiro::color::channel::alpha(),
				mizuiro::color::access::channel_max<
					sge::gdifont::a8_view::format::color_format
				>(
					_color.format_store(),
					mizuiro::color::channel::alpha()
				)
			);
	}
};

}
}

#endif
