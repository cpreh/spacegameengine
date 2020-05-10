//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_OBJECT_HPP_INCLUDED
#define SGE_FONT_OBJECT_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/font/metrics_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters_fwd.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/font/detail/symbol.hpp>
#include <sge/image/color/optional_format_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge
{
namespace font
{

class SGE_CORE_DETAIL_CLASS_SYMBOL object
{
	FCPPT_NONMOVABLE(
		object
	);
protected:
	SGE_FONT_DETAIL_SYMBOL
	object();
public:
	SGE_FONT_DETAIL_SYMBOL
	virtual
	~object();

	[[nodiscard]]
	virtual
	sge::font::text_unique_ptr
	create_text(
		sge::font::string const &,
		sge::font::text_parameters const &
	) = 0;

	/**
	\brief Tells which color format is preferred by this font, if any.
	*/
	[[nodiscard]]
	virtual
	sge::image::color::optional_format
	preferred_color_format() const = 0;

	[[nodiscard]]
	virtual
	sge::font::metrics
	metrics() const = 0;
};

}
}

#endif
