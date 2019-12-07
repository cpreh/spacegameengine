//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SPRITE_VERTEX_FORMAT_HPP_INCLUDED
#define SGE_SPRITE_VERTEX_FORMAT_HPP_INCLUDED

#include <sge/renderer/vf/format.hpp>
#include <sge/sprite/detail/vf/format_part.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{

template<
	typename Choices
>
struct vertex_format
{
	typedef sge::renderer::vf::format<
		metal::list<
			typename sge::sprite::detail::vf::format_part<
				Choices
			>::type
		>
	> type;
};

}
}

#endif
