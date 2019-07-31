//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GDIFONT_TEXT_HPP_INCLUDED
#define SGE_GDIFONT_TEXT_HPP_INCLUDED

#include <sge/font/dim_fwd.hpp>
#include <sge/font/index.hpp>
#include <sge/font/optional_index_fwd.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/vector_fwd.hpp>
#include <sge/font/view_fwd.hpp>
#include <sge/gdifont/device_context_fwd.hpp>
#include <sge/gdifont/format.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace gdifont
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
		sge::gdifont::device_context const &,
		HFONT,
		sge::font::string const &,
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

	sge::gdifont::device_context const &device_context_;

	HFONT const hfont_;

	sge::font::string const string_;

	sge::gdifont::format const render_flags_;

	sge::font::rect const rect_;

};

}
}

#endif
