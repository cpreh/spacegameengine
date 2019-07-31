//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PANGO_FONT_DESCRIPTION_HPP_INCLUDED
#define SGE_PANGO_FONT_DESCRIPTION_HPP_INCLUDED

#include <sge/font/ttf_size.hpp>
#include <sge/font/weight/unit.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <pango/pango-font.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace pango
{

class font_description
{
	FCPPT_NONCOPYABLE(
		font_description
	);
public:
	font_description();

	~font_description();

	void
	ttf_size(
		sge::font::ttf_size
	);

	void
	family(
		fcppt::string const &
	);

	void
	weight(
		sge::font::weight::unit
	);

	void
	italic();

	PangoFontDescription *
	get();
private:
	PangoFontDescription *const impl_;
};

}
}

#endif
