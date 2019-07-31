//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_DEFAULT_FONT_HPP_INCLUDED
#define SGE_CEGUI_DEFAULT_FONT_HPP_INCLUDED

#include <sge/cegui/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>



namespace sge
{
namespace cegui
{

class default_font
{
public:
	SGE_CEGUI_DETAIL_SYMBOL
	default_font(
		boost::filesystem::path const &,
		float font_size
	);

	boost::filesystem::path const &
	path() const;

	float
	font_size() const;
private:
	boost::filesystem::path path_;

	float font_size_;
};

}
}

#endif
