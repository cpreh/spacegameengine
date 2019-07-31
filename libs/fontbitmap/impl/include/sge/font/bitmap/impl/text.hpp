//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_BITMAP_IMPL_TEXT_HPP_INCLUDED
#define SGE_FONT_BITMAP_IMPL_TEXT_HPP_INCLUDED

#include <sge/font/dim_fwd.hpp>
#include <sge/font/index.hpp>
#include <sge/font/optional_index_fwd.hpp>
#include <sge/font/rect_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/vector_fwd.hpp>
#include <sge/font/view_fwd.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/font/bitmap/impl/char_map.hpp>
#include <sge/font/bitmap/impl/line_height.hpp>
#include <sge/font/bitmap/impl/rep.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace font
{
namespace bitmap
{
namespace impl
{

class text
:
	public sge::font::text
{
	FCPPT_NONCOPYABLE(
		text
	);
public:
	text(
		fcppt::log::object &,
		sge::font::bitmap::impl::char_map const &,
		sge::font::string const &,
		sge::font::text_parameters const &,
		sge::font::bitmap::impl::line_height
	);

	~text()
	override;
private:
	void
	render(
		sge::font::view const &
	)
	override;

	sge::font::rect
	rect() const
	override;

	sge::font::dim
	logical_size() const
	override;

	sge::font::rect
	cursor_rect(
		sge::font::index
	) const
	override;

	sge::font::optional_index
	pos_to_index(
		sge::font::vector
	) const
	override;

	template<
		typename Function
	>
	void
	iterate(
		Function const &
	) const;

	sge::font::bitmap::impl::line_height const line_height_;

	sge::font::align_h::variant const align_h_;

	sge::font::bitmap::impl::rep const rep_;
};

}
}
}
}

#endif
