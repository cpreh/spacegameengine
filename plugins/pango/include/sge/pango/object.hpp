//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PANGO_OBJECT_HPP_INCLUDED
#define SGE_PANGO_OBJECT_HPP_INCLUDED

#include <sge/font/metrics.hpp>
#include <sge/font/object.hpp>
#include <sge/font/parameters_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/image/color/optional_format_fwd.hpp>
#include <sge/pango/glib_deleter_fwd.hpp>
#include <sge/pango/pango_layout_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-fontmap.h>
#include <pango/pango-layout.h>
#include <pango/pango-types.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace pango
{

class object
:
	public sge::font::object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		sge::font::parameters const &
	);

	~object()
	override;
private:
	sge::font::text_unique_ptr
	create_text(
		sge::font::string const &,
		sge::font::text_parameters const &
	)
	override;

	sge::image::color::optional_format
	preferred_color_format() const
	override;

	sge::font::metrics
	metrics() const
	override;

	typedef
	fcppt::unique_ptr<
		PangoFontMap,
		sge::pango::glib_deleter
	>
	font_map_unique_ptr;

	font_map_unique_ptr const font_map_;

	typedef
	fcppt::unique_ptr<
		PangoContext,
		sge::pango::glib_deleter
	>
	context_unique_ptr;

	context_unique_ptr const context_;

	sge::pango::pango_layout_unique_ptr const layout_;

	sge::font::metrics const metrics_;
};

}
}

#endif
