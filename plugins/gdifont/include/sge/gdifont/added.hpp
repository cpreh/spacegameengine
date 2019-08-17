//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GDIFONT_ADDED_HPP_INCLUDED
#define SGE_GDIFONT_ADDED_HPP_INCLUDED

#include <sge/font/added.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace gdifont
{

class added
:
	public sge::font::added
{
	FCPPT_NONCOPYABLE(
		added
	);
public:
	explicit
	added(
		std::filesystem::path const &
	);

	~added()
	override;
private:
	std::filesystem::path const path_;
};

}
}

#endif
