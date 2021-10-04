//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_FORMAT_HPP_INCLUDED
#define SGE_RENDERER_VF_FORMAT_HPP_INCLUDED

#include <sge/renderer/vf/format_fwd.hpp>
#include <sge/renderer/vf/is_part.hpp>
#include <fcppt/mpl/lambda.hpp>
#include <fcppt/mpl/list/all_of.hpp>
#include <fcppt/mpl/list/object.hpp>


namespace sge::renderer::vf
{

template<
	typename... Parts
>
struct format
{
	using
	parts
	=
	fcppt::mpl::list::object<
		Parts...
	>;

	static_assert(
		fcppt::mpl::list::all_of<
			parts,
			fcppt::mpl::lambda<
				sge::renderer::vf::is_part
			>
		>::value,
		"PartList must be a list of sge::renderer::vf::part"
	);
};

}

#endif
