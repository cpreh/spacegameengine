//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PANGO_TEXT_HPP_INCLUDED
#define SGE_PANGO_TEXT_HPP_INCLUDED

#include <sge/charconv/index_vector.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/font/dim_fwd.hpp>
#include <sge/font/index.hpp>
#include <sge/font/optional_index_fwd.hpp>
#include <sge/font/rect_fwd.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/vector_fwd.hpp>
#include <sge/font/view_fwd.hpp>
#include <sge/pango/extents.hpp>
#include <sge/pango/pango_layout_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-layout.h>
#include <fcppt/config/external_end.hpp>


namespace sge::pango
{

class text
:
	public sge::font::text
{
	FCPPT_NONMOVABLE(
		text
	);
public:
	text(
		PangoLayout &, // NOLINT(google-runtime-references)
		sge::charconv::utf8_string const &,
		sge::font::text_parameters const &
	);

	~text()
	override;
private:
	void
	render(
		sge::font::view const &
	)
	override;

	[[nodiscard]]
	sge::font::rect
	rect() const
	override;

	[[nodiscard]]
	sge::font::dim
	logical_size() const
	override;

	[[nodiscard]]
	sge::font::rect
	cursor_rect(
		sge::font::index
	) const
	override;

	[[nodiscard]]
	sge::font::optional_index
	pos_to_index(
		sge::font::vector
	) const
	override;

	sge::pango::pango_layout_unique_ptr const layout_;

	sge::pango::extents const extents_;

	sge::charconv::index_vector const indices_;
};

}

#endif
