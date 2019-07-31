//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GDIFONT_COLORS_TO_MAX_VISITOR_HPP_INCLUDED
#define SGE_GDIFONT_COLORS_TO_MAX_VISITOR_HPP_INCLUDED

#include <sge/gdifont/a8_view.hpp>
#include <sge/gdifont/alpha_to_max.hpp>
#include <mizuiro/image/algorithm/for_each.hpp>
#include <mizuiro/image/algorithm/make_iterator_identity.hpp>
#include <mizuiro/image/algorithm/uninitialized.hpp>
#include <fcppt/assert/unreachable.hpp>


namespace sge
{
namespace gdifont
{

struct colors_to_max_visitor
{
	typedef void result_type;

	template<
		typename View
	>
	result_type
	operator()(
		View const &
	) const
	{
		// TOOD: Maybe we have to support a generic version here
		FCPPT_ASSERT_UNREACHABLE;
	}

	result_type
	operator()(
		sge::gdifont::a8_view const &_view
	) const
	{
		mizuiro::image::algorithm::for_each(
			_view,
			sge::gdifont::alpha_to_max(),
			mizuiro::image::algorithm::make_iterator_identity(),
			mizuiro::image::algorithm::uninitialized::yes
		);
	}
};

}
}

#endif
