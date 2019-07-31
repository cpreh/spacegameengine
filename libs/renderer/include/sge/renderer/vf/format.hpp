//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_FORMAT_HPP_INCLUDED
#define SGE_RENDERER_VF_FORMAT_HPP_INCLUDED

#include <sge/renderer/vf/format_fwd.hpp>
#include <fcppt/type_traits/is_brigand_sequence.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename PartList
>
struct format
{
	static_assert(
		fcppt::type_traits::is_brigand_sequence<
			PartList
		>::value,
		"PartList must be a brigand sequence"
	);

	typedef PartList parts;
};

}
}
}

#endif
