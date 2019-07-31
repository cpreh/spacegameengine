//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_LIBPNG_SYSTEM_HPP_INCLUDED
#define SGE_LIBPNG_SYSTEM_HPP_INCLUDED

#include <sge/image2d/optional_file_unique_ptr.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/media/extension_fwd.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/stream_unique_ptr_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/object.hpp>


namespace sge
{
namespace libpng
{

class system
:
	public sge::image2d::system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	explicit
	system(
		fcppt::log::context &
	);

	~system()
	override;

	sge::image2d::load_stream_result
	load_stream(
		sge::media::stream_unique_ptr &&,
		sge::media::optional_extension const &,
		sge::media::optional_name const &
	)
	override;

	sge::image2d::optional_file_unique_ptr
	create(
		sge::image2d::view::const_object const &,
		sge::media::extension const &
	)
	override;

	sge::media::extension_set
	extensions() const
	override;
private:
	fcppt::log::object log_;
};

}
}

#endif
