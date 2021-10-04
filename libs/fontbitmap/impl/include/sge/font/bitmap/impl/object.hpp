//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_BITMAP_IMPL_OBJECT_HPP_INCLUDED
#define SGE_FONT_BITMAP_IMPL_OBJECT_HPP_INCLUDED

#include <sge/font/metrics_fwd.hpp>
#include <sge/font/object.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/font/bitmap/impl/char_map.hpp>
#include <sge/font/bitmap/impl/line_height.hpp>
#include <sge/image/color/optional_format.hpp>
#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/image2d/system_ref.hpp>
#include <sge/parse/json/start_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge::font::bitmap::impl
{

class object
:
	public sge::font::object
{
	FCPPT_NONMOVABLE(
		object
	);
public:
	object(
		fcppt::log::context_reference,
		std::filesystem::path const &,
		sge::image2d::system_ref
	);

	~object()
	override;
private:
	object(
		fcppt::log::context_reference,
		std::filesystem::path const &,
		sge::image2d::system_ref,
		sge::parse::json::start const &
	);

	[[nodiscard]]
	sge::font::text_unique_ptr
	create_text(
		sge::font::string const &,
		sge::font::text_parameters const &
	)
	override;

	[[nodiscard]]
	sge::image::color::optional_format
	preferred_color_format() const
	override;

	[[nodiscard]]
	sge::font::metrics
	metrics() const
	override;

	fcppt::log::object log_;

	sge::font::bitmap::impl::line_height const line_height_;

	using
	image_vector
	=
	std::vector<
		sge::image2d::file_unique_ptr
	>;

	std::pair<
		image_vector,
		sge::font::bitmap::impl::char_map
	> const impl_;

	sge::image::color::optional_format const color_format_;
};

}

#endif
