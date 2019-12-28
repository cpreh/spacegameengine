//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_FORMAT_HPP_INCLUDED
#define SGE_RENDERER_INDEX_FORMAT_HPP_INCLUDED

#include <sge/renderer/index/format_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace index
{

template<
	typename Index
>
struct format
{
	typedef
	Index
	index_type;

	static_assert(
		std::is_integral_v<
			Index
		>
	);
};

}
}
}

#endif
