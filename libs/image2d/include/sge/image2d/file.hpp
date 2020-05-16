//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE2D_FILE_HPP_INCLUDED
#define SGE_IMAGE2D_FILE_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/image2d/dim_fwd.hpp>
#include <sge/image2d/file_fwd.hpp>
#include <sge/image2d/detail/symbol.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image2d
{

class SGE_CORE_DETAIL_CLASS_SYMBOL file
{
	FCPPT_NONMOVABLE(
		file
	);
protected:
	SGE_IMAGE2D_DETAIL_SYMBOL
	file();
public:
	[[nodiscard]]
	virtual
	sge::image2d::view::const_object
	view() const = 0;

	[[nodiscard]]
	virtual
	sge::image2d::dim
	size() const = 0;

	virtual
	void
	save(
		std::filesystem::path const &
	) const = 0;

	virtual
	void
	save_stream(
		std::ostream &
	) const = 0;

	SGE_IMAGE2D_DETAIL_SYMBOL
	virtual
	~file();
};

}
}

#endif
