//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/impl/algorithm/instantiate_print.hpp>
#include <sge/image/impl/algorithm/print_impl.hpp>
#include <sge/image3d/tag.hpp>
#include <sge/image3d/algorithm/print.hpp>
#include <sge/image3d/view/const_object.hpp>
#include <fcppt/io/ostream_fwd.hpp>


void
sge::image3d::algorithm::print(
	fcppt::io::ostream &_ostream,
	sge::image3d::view::const_object const &_view
)
{
	sge::image::algorithm::print<
		sge::image3d::tag
	>(
		_ostream,
		_view
	);
}

SGE_IMAGE_IMPL_ALGORITHM_INSTANTIATE_PRINT(
	sge::image3d::tag
);
