//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PANGO_ADDED_HPP_INCLUDED
#define SGE_PANGO_ADDED_HPP_INCLUDED

#include <sge/font/added.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge::pango
{

class added
:
	public sge::font::added
{
	FCPPT_NONMOVABLE(
		added
	);
public:
	explicit
	added(
		std::filesystem::path const &
	);

	~added()
	override;
};

}

#endif
