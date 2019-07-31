//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_PARAMETERS_HPP_INCLUDED
#define SGE_FONT_PARAMETERS_HPP_INCLUDED

#include <sge/font/dpi_fwd.hpp>
#include <sge/font/optional_dpi.hpp>
#include <sge/font/optional_family.hpp>
#include <sge/font/optional_ttf_size.hpp>
#include <sge/font/parameters_fwd.hpp>
#include <sge/font/ttf_size.hpp>
#include <sge/font/detail/symbol.hpp>
#include <sge/font/weight/optional_unit.hpp>
#include <sge/font/weight/unit.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace font
{

class parameters
{
public:
	SGE_FONT_DETAIL_SYMBOL
	parameters();

	SGE_FONT_DETAIL_SYMBOL
	sge::font::parameters &
	dpi(
		sge::font::dpi const &
	);

	SGE_FONT_DETAIL_SYMBOL
	sge::font::parameters &
	ttf_size(
		sge::font::ttf_size
	);

	SGE_FONT_DETAIL_SYMBOL
	sge::font::parameters &
	family(
		fcppt::string const &
	);

	SGE_FONT_DETAIL_SYMBOL
	sge::font::parameters &
	weight(
		sge::font::weight::unit
	);

	SGE_FONT_DETAIL_SYMBOL
	sge::font::parameters &
	italic();

	SGE_FONT_DETAIL_SYMBOL
	sge::font::optional_dpi const &
	dpi() const;

	SGE_FONT_DETAIL_SYMBOL
	sge::font::optional_ttf_size const &
	ttf_size() const;

	SGE_FONT_DETAIL_SYMBOL
	sge::font::optional_family const &
	family() const;

	SGE_FONT_DETAIL_SYMBOL
	sge::font::weight::optional_unit const &
	weight() const;

	SGE_FONT_DETAIL_SYMBOL
	bool
	italic() const;
private:
	sge::font::optional_dpi dpi_;

	sge::font::optional_ttf_size ttf_size_;

	sge::font::optional_family family_;

	sge::font::weight::optional_unit weight_;

	bool italic_;
};

}
}

#endif
