//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_DETAIL_ITERATOR_BASE_HPP_INCLUDED
#define SGE_RENDERER_INDEX_DETAIL_ITERATOR_BASE_HPP_INCLUDED

#include <sge/renderer/index/const_proxy_fwd.hpp>
#include <sge/renderer/index/difference_type.hpp>
#include <sge/renderer/index/iterator_fwd.hpp>
#include <sge/renderer/index/nonconst_tag.hpp>
#include <sge/renderer/index/proxy_fwd.hpp>
#include <fcppt/iterator/base_decl.hpp>
#include <fcppt/iterator/types.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iterator>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::renderer::index::detail
{

template<
	typename Format,
	typename Constness
>
using
iterator_base
=
fcppt::iterator::base<
	fcppt::iterator::types<
		sge::renderer::index::iterator<
			Format,
			Constness
		>,
		typename
		Format::index_type,
		std::conditional_t<
			std::is_same_v<
				Constness,
				sge::renderer::index::nonconst_tag
			>,
			sge::renderer::index::proxy<
				Format
			>,
			sge::renderer::index::const_proxy<
				Format
			>
		>,
		sge::renderer::index::difference_type,
		// TODO(philipp): output_iterator?
		std::input_iterator_tag
	>
>;

}

#endif
