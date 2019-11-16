//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/core/exception.hpp>
#include <sge/image/size_type.hpp>
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
#include <sge/systems/image2d.hpp>
#include <sge/systems/instance.hpp>
#include <sge/systems/list.hpp>
#include <sge/systems/make_list.hpp>
#include <sge/systems/with_image2d.hpp>
#include <fcppt/args_char.hpp>
#include <fcppt/args_from_second.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/main.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/vector/null.hpp>
#include <fcppt/options/argument.hpp>
#include <fcppt/options/error.hpp>
#include <fcppt/options/error_output.hpp>
#include <fcppt/options/long_name.hpp>
#include <fcppt/options/optional_help_text.hpp>
#include <fcppt/options/parse.hpp>
#include <fcppt/options/result_of.hpp>
#include <fcppt/record/get.hpp>
#include <fcppt/record/make_label.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/list/list.hpp>
#include <algorithm>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace
{

sge::image::size_type
calc_size(
	sge::image::size_type const _image_count,
	sge::image2d::dim const &_dim
)
{
	for(
		sge::image::size_type const index
		:
		fcppt::make_int_range_count(
			11u
		)
	)
	{
		sge::image::size_type const size(
			fcppt::literal<
				sge::image::size_type
			>(
				1
			)
			<< index
		);

		if(
			(size / (_dim.w() + 1))
			* (size / (_dim.h() + 1))
			>= _image_count
		)
			return size;
	}

	throw
		sge::core::exception{
			FCPPT_TEXT("size too big!")
		};
}

sge::image2d::dim
first_dim(
	std::filesystem::path const &_path,
	sge::image2d::system &_system
)
{
	std::filesystem::directory_iterator const it(
		_path
	);

	return
		sge::image2d::load_exn(
			_system,
			*it
		)->size();
}

typedef
std::vector<
	std::filesystem::path
>
path_vector;

path_vector
sort_paths(
	std::filesystem::path const &_path
)
{
	path_vector ret{
		std::filesystem::directory_iterator(
			_path
		),
		std::filesystem::directory_iterator()
	};

	std::sort(
		ret.begin(),
		ret.end()
	);

	return
		ret;
}

int
program_main(
	std::filesystem::path const &_path
)
{
	sge::systems::instance<
		metal::list<
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

	sge::image::size_type const image_count(
		fcppt::cast::size<
			sge::image::size_type
		>(
			fcppt::cast::to_unsigned(
				std::distance(
					std::filesystem::directory_iterator(
						_path
					),
					std::filesystem::directory_iterator()
				)
			)
		)
	);

	if(
		image_count
		==
		0
	)
	{
		fcppt::io::cerr()
			<<
			FCPPT_TEXT("No files here.\n");

		return
			EXIT_SUCCESS;
	}

	sge::image2d::dim const dim(
		first_dim(
			_path,
			il
		)
	);

	sge::image::size_type const border_sz(
		calc_size(
			image_count,
			dim
		)
	);

	typedef
	sge::image2d::store::srgba8
	image_type;

	image_type dest{
		fcppt::math::dim::fill<
			image_type::dim
		>(
			border_sz
		),
		image_type::init_function{
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
					sge::image::color::any::object{
						sge::image::color::predef::transparent()
					},
					sge::image::algorithm::uninitialized::yes
				);
			}
		}
	};


	sge::image2d::view::object const dest_view(
		dest.wrapped_view()
	);

	sge::image2d::rect::vector pos(
		fcppt::math::vector::null<
			sge::image2d::rect::vector
		>()
	);

	path_vector const paths(
		sort_paths(
			_path
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
			img->size()
			!=
			dim
		)
		{
			fcppt::io::cerr()
				<<
				FCPPT_TEXT("Dimension ")
				<<
				img->size()
				<<
				FCPPT_TEXT(" is different from the previously used dimension ")
				<<
				dim
				<<
				FCPPT_TEXT('\n');

			return
				EXIT_FAILURE;
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

	return
		EXIT_SUCCESS;
}

FCPPT_RECORD_MAKE_LABEL(
	path_label
);

}

int
FCPPT_MAIN(
	int argc,
	fcppt::args_char **argv
)
try
{
	auto const parser(
		fcppt::options::argument<
			path_label,
			fcppt::string
		>{
			fcppt::options::long_name{
				FCPPT_TEXT("path")
			},
			fcppt::options::optional_help_text{}
		}
	);

	typedef
	fcppt::options::result_of<
		decltype(
			parser
		)
	>
	result_type;

	return
		fcppt::either::match(
			fcppt::options::parse(
				parser,
				fcppt::args_from_second(
					argc,
					argv
				)
			),
			[](
				fcppt::options::error const &_error
			)
			{
				fcppt::io::cerr()
					<<
					_error
					<<
					FCPPT_TEXT('\n');

				return
					EXIT_FAILURE;
			},
			[](
				result_type const &_result
			)
			{
				program_main(
					std::filesystem::path{
						fcppt::record::get<
							path_label
						>(
							_result
						)
					}
				);

				return
					EXIT_SUCCESS;
			}
		);
}
catch(
	fcppt::exception const &_exception
)
{
	fcppt::io::cerr()
		<<
		_exception.string()
		<<
		FCPPT_TEXT('\n');

	return
		EXIT_FAILURE;
}
catch(
	std::exception const &_exception
)
{
	std::cerr
		<<
		_exception.what()
		<<
		'\n';

	return
		EXIT_FAILURE;
}
