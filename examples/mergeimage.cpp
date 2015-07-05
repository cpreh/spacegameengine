/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/core/exception.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/view/wrap.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/image2d/load_exn.hpp>
#include <sge/image2d/save_from_view.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/algorithm/fill.hpp>
#include <sge/image2d/store/srgba8.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/image2d/view/to_const.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_set.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/systems/image2d.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/with_image2d.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/text.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::renderer::size_type
calc_size(
	sge::renderer::size_type const _image_count,
	sge::renderer::dim2 const &_dim
)
{
	for(
		sge::renderer::size_type const index
		:
		fcppt::make_int_range_count(
			11u
		)
	)
	{
		sge::renderer::size_type const size(
			1u << index
		);

		if(
			(size / (_dim.w() + 1))
			* (size / (_dim.h() + 1))
			>= _image_count
		)
			return size;
	}

	throw sge::core::exception(
		FCPPT_TEXT("size too big!")
	);
}

sge::renderer::dim2 const
first_dim(
	boost::filesystem::path const &_path,
	sge::image2d::system &_system
)
{
	boost::filesystem::directory_iterator const it(
		_path
	);

	return
		sge::image2d::load_exn(
			_system,
			*it
		)->size();
}

typedef std::vector<
	boost::filesystem::path
> path_vector;

path_vector
sort_paths(
	boost::filesystem::path const &_path
)
{
	path_vector ret{
		boost::filesystem::directory_iterator(
			_path
		),
		boost::filesystem::directory_iterator()
	};

	std::sort(
		ret.begin(),
		ret.end()
	);

	return ret;
}

}

int
main(
	int argc,
	char **argv
)
try
{
	if(
		argc != 2
	)
	{
		fcppt::io::cerr()
			<< FCPPT_TEXT("please specify a path!\n");

		return EXIT_FAILURE;
	}

	sge::systems::instance<
		boost::mpl::vector1<
			sge::systems::with_image2d
		>
	> const sys(
		sge::systems::make_list
		(
			sge::systems::image2d(
				sge::media::optional_extension_set(
					sge::media::extension_set{
						sge::media::extension(
							FCPPT_TEXT("png")
						)
					}
				)
			)
		)
	);

	sge::image2d::system &il(
		sys.image_system()
	);

	boost::filesystem::path const path(
		fcppt::from_std_string(
			argv[1]
		)
	);

	sge::renderer::size_type const image_count(
		static_cast<
			sge::renderer::size_type
		>(
			std::distance(
				boost::filesystem::directory_iterator(
					path
				),
				boost::filesystem::directory_iterator()
			)
		)
	);

	if(
		image_count == 0
	)
	{
		fcppt::io::cerr()
			<< FCPPT_TEXT("No files here.\n");

		return EXIT_SUCCESS;
	}

	sge::renderer::dim2 const dim(
		first_dim(
			path,
			il
		)
	);

	sge::renderer::size_type const border_sz(
		calc_size(
			image_count,
			dim
		)
	);

	typedef sge::image2d::store::srgba8 image_type;

	image_type dest{
		fcppt::math::dim::fill<
			image_type::dim
		>(
			border_sz
		),
		[](
			image_type::view_type const &_view
		)
		{
			sge::image2d::algorithm::fill(
				sge::image2d::view::object(
					sge::image::view::wrap(
						_view
					)
				),
				sge::image::color::predef::transparent(),
				sge::image::algorithm::uninitialized::yes
			);
		}
	};


	sge::image2d::view::object const dest_view(
		dest.wrapped_view()
	);

	sge::image2d::rect::vector pos(
		sge::image2d::rect::vector::null()
	);

	path_vector const paths(
		sort_paths(
			path
		)
	);

	for(
		auto const &cur_path
		:
		paths
	)
	{
		sge::image2d::file_unique_ptr const img(
			sge::image2d::load_exn(
				il,
				cur_path
			)
		);

		if(
			img->size() != dim
		)
		{
			fcppt::io::cerr()
				<< FCPPT_TEXT("some dimensions do not match!\n");

			return EXIT_FAILURE;
		}

		sge::image2d::algorithm::copy_and_convert(
			img->view(),
			sge::image2d::view::sub(
				dest_view,
				sge::image2d::rect(
					pos,
					dim
				)
			),
			sge::image::algorithm::may_overlap::no,
			sge::image::algorithm::uninitialized::no
		);

		pos.x() += dim.w() + 1;

		if(
			pos.x() + dim.w() + 1 > border_sz
		)
		{
			pos.x() = 0;
			pos.y() += dim.h() + 1;
		}
	}

	sge::image2d::save_from_view(
		il,
		sge::image2d::view::to_const(
			dest_view
		),
		FCPPT_TEXT("out.png")
	);
}
catch(
	fcppt::exception const &_exception
)
{
	fcppt::io::cerr()
		<< _exception.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_exception
)
{
	std::cerr
		<< _exception.what()
		<< '\n';

	return EXIT_FAILURE;
}
