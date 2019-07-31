//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_ANY_DETAIL_VARIANT_TYPES_HPP_INCLUDED
#define SGE_RENDERER_INDEX_ANY_DETAIL_VARIANT_TYPES_HPP_INCLUDED

#include <sge/renderer/index/any/detail/make_view_element.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <fcppt/brigand/enum_range.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/algorithms/transform.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/types/args.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace index
{
namespace any
{
namespace detail
{

template<
	typename Constness
>
using
variant_types
=
brigand::transform<
	fcppt::brigand::enum_range<
		sge::renderer::index::dynamic::format
	>,
	brigand::bind<
		sge::renderer::index::any::detail::make_view_element,
		brigand::_1,
		Constness
	>
>;

}
}
}
}
}

#endif
