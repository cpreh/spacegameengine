//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE2D_MULTI_SYSTEM_HPP_INCLUDED
#define SGE_IMAGE2D_MULTI_SYSTEM_HPP_INCLUDED

#include <sge/image2d/file_fwd.hpp>
#include <sge/image2d/load_stream_result_fwd.hpp>
#include <sge/image2d/multi_system_fwd.hpp>
#include <sge/image2d/multi_system_parameters_fwd.hpp>
#include <sge/image2d/optional_file_unique_ptr.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/detail/symbol.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/media/extension_fwd.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/muxer.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/stream_unique_ptr_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::image2d
{

class multi_system
:
	public sge::image2d::system
{
	FCPPT_NONMOVABLE(
		multi_system
	);
public:
	SGE_IMAGE2D_DETAIL_SYMBOL
	explicit
	multi_system(
		sge::image2d::multi_system_parameters const &
	);

	SGE_IMAGE2D_DETAIL_SYMBOL
	~multi_system()
	override;

	[[nodiscard]]
	SGE_IMAGE2D_DETAIL_SYMBOL
	sge::image2d::load_stream_result
	load_stream(
		sge::media::stream_unique_ptr &&,
		sge::media::optional_extension const &,
		sge::media::optional_name const &
	)
	override;

	[[nodiscard]]
	SGE_IMAGE2D_DETAIL_SYMBOL
	sge::image2d::optional_file_unique_ptr
	create(
		sge::image2d::view::const_object const &,
		sge::media::extension const &
	)
	override;

	[[nodiscard]]
	SGE_IMAGE2D_DETAIL_SYMBOL
	sge::media::extension_set
	extensions() const
	override;
private:
	using
	muxer
	=
	sge::media::muxer<
		sge::image2d::system,
		sge::image2d::file
	>;

	muxer muxer_;
};

}

#endif
