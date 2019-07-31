//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DETAIL_COPY_N_HPP_INCLUDED
#define SGE_RENDERER_VF_DETAIL_COPY_N_HPP_INCLUDED

#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstring>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace detail
{

inline
void
copy_n(
	sge::renderer::const_raw_pointer const _src,
	sge::renderer::vf::vertex_size const _sz,
	sge::renderer::raw_pointer const _dest
)
{
	std::memcpy(
		_dest,
		_src,
		_sz
	);
}

}
}
}
}

#endif
