//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/gdifont/colors_to_max.hpp>
#include <sge/gdifont/colors_to_max_visitor.hpp>
#include <sge/image2d/view/object.hpp>
#include <fcppt/variant/apply.hpp>


void
sge::gdifont::colors_to_max(
	sge::image2d::view::object const &_view
)
{
	fcppt::variant::apply(
		sge::gdifont::colors_to_max_visitor(),
		_view.get()
	);
}
