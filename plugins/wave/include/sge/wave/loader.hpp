//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WAVE_LOADER_HPP_INCLUDED
#define SGE_WAVE_LOADER_HPP_INCLUDED

#include <sge/audio/load_stream_result_fwd.hpp>
#include <sge/audio/loader.hpp>
#include <sge/media/extension_set.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/optional_name_fwd.hpp>
#include <sge/media/stream_unique_ptr_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/context_reference_fwd.hpp>
#include <fcppt/log/object.hpp>


namespace sge::wave
{

class loader
:
	public sge::audio::loader
{
	FCPPT_NONMOVABLE(
		loader
	);
public:
	explicit
	loader(
		fcppt::log::context_reference
	);

	~loader()
	override;

	[[nodiscard]]
	sge::audio::load_stream_result
	load_stream(
		sge::media::stream_unique_ptr &&,
		sge::media::optional_extension const &,
		sge::media::optional_name const &
	)
	override;

	[[nodiscard]]
	sge::media::extension_set
	extensions() const
	override;
private:
	fcppt::log::object log_;
};

}

#endif
