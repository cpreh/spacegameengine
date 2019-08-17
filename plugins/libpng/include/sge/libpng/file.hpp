//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_LIBPNG_FILE_HPP_INCLUDED
#define SGE_LIBPNG_FILE_HPP_INCLUDED

#include <sge/image2d/dim_fwd.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/libpng/file_rep.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace libpng
{

class file
:
	public sge::image2d::file
{
	FCPPT_NONCOPYABLE(
		file
	);
public:
	file(
		fcppt::log::object &,
		sge::libpng::file_rep &&
	);

	~file()
	override;
private:
	sge::image2d::view::const_object
	view() const
	override;

	sge::image2d::dim
	size() const
	override;

	void
	save(
		std::filesystem::path const &
	) const
	override;

	void
	save_stream(
		std::ostream &
	) const
	override;

	fcppt::log::object &log_;

	sge::libpng::file_rep const rep_;
};

}
}

#endif
