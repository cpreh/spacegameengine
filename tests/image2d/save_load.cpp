//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/config/plugin_path.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image/color/rgba8.hpp>
#include <sge/image/color/init/alpha.hpp>
#include <sge/image/color/init/blue.hpp>
#include <sge/image/color/init/green.hpp>
#include <sge/image/color/init/red.hpp>
#include <sge/image/view/wrap.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/system_unique_ptr.hpp>
#include <sge/image2d/algorithm/compare.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/plugin/collection.hpp>
#include <sge/image2d/plugin/context.hpp>
#include <sge/image2d/plugin/iterator.hpp>
#include <sge/image2d/plugin/manager.hpp>
#include <sge/image2d/plugin/object.hpp>
#include <sge/image2d/store/rgba8.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/log/default_level.hpp>
#include <sge/log/default_level_streams.hpp>
#include <sge/media/extension.hpp>
#include <sge/media/optional_extension.hpp>
#include <sge/media/optional_name.hpp>
#include <sge/plugin/collection.hpp>
#include <sge/plugin/context.hpp>
#include <sge/plugin/info.hpp>
#include <sge/plugin/iterator.hpp>
#include <sge/plugin/manager.hpp>
#include <sge/plugin/optional_cache_ref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/catch/begin.hpp>
#include <fcppt/catch/end.hpp>
#include <fcppt/log/context.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/variant/to_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <istream>
#include <sstream>
#include <utility>
#include <fcppt/config/external_end.hpp>


FCPPT_CATCH_BEGIN

TEST_CASE(
	"save_load rgba",
	"[sge]"
)
{
	fcppt::log::context log_context{
		sge::log::default_level(),
		sge::log::default_level_streams()
	};

	using
	store_type
	=
	sge::image2d::store::rgba8;

	store_type const store{
		store_type::dim(
			1U,
			1U
		),
		sge::image::color::rgba8(
			(sge::image::color::init::red() %= 0.5)
			(sge::image::color::init::blue() %= 0.3)
			(sge::image::color::init::green() %= 0.2)
			(sge::image::color::init::alpha() %= 0.1)
		)
	};

	sge::plugin::manager plugins(
		fcppt::make_ref(
			log_context
		),
		sge::config::plugin_path(),
		sge::plugin::optional_cache_ref()
	);

	for(
		sge::plugin::context<
			sge::image2d::system
		> const &element
		:
		plugins.collection<
			sge::image2d::system
		>()
	)
	{
		sge::image2d::plugin::object const plugin(
			element.load()
		);

		sge::image2d::system_unique_ptr const system(
			plugin.get()(
				fcppt::make_ref(
					log_context
				)
			)
		);

		auto stream(
			fcppt::make_unique_ptr<
				std::stringstream
			>()
		);

		sge::image2d::view::const_object const source_view(
			sge::image2d::view::const_object(
				store.const_wrapped_view()
			)
		);

		sge::image2d::file_unique_ptr const created(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				system->create(
					source_view,
					// FIXME: Iterate over all supported formats
					sge::media::extension{
						FCPPT_TEXT("png")
					}
				)
			)
		);

		created->save_stream(
			*stream
		);

		sge::image2d::file_unique_ptr const file(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				fcppt::variant::to_optional<
					sge::image2d::file_unique_ptr
				>(
					system->load_stream(
						fcppt::unique_ptr_to_base<
							std::istream
						>(
							std::move(
								stream
							)
						),
						sge::media::optional_extension(),
						sge::media::optional_name()
					)
				)
			)
		);

		sge::image2d::view::const_object const dest_view(
			file->view()
		);

		REQUIRE(
			sge::image2d::view::size(
				source_view
			)
			==
			sge::image2d::view::size(
				dest_view
			)
		);

		store_type const store_back{
			store.size(),
			store_type::init_function{
				[
					&dest_view
				](
					store_type::view_type const &_dest
				)
				{
					sge::image2d::algorithm::copy_and_convert(
						dest_view,
						sge::image2d::view::object(
							sge::image::view::wrap(
								_dest
							)
						),
						sge::image::algorithm::may_overlap::no,
						sge::image::algorithm::uninitialized::yes
					);
				}
			}
		};

		sge::image2d::view::const_object const store_back_view(
			sge::image2d::view::const_object(
				store_back.const_wrapped_view()
			)
		);

		CHECK(
			sge::image2d::algorithm::compare(
				source_view,
				store_back_view
			)
		);
	}
}

FCPPT_CATCH_END
