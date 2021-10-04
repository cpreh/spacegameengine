//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_IMPL_SCOPED_SYSTEM_HPP_INCLUDED
#define SGE_CEGUI_IMPL_SCOPED_SYSTEM_HPP_INCLUDED

#include <sge/cegui/impl/image_codec_fwd.hpp>
#include <sge/cegui/impl/renderer_ref.hpp>
#include <sge/cegui/impl/resource_provider_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_fwd.hpp>


namespace sge::cegui::impl
{

class scoped_system
{
	FCPPT_NONMOVABLE(
		scoped_system
	);
public:
	scoped_system(
		sge::cegui::impl::renderer_ref,
		fcppt::reference<
			sge::cegui::impl::image_codec
		>,
		fcppt::reference<
			sge::cegui::impl::resource_provider
		>
	);

	~scoped_system();
};

}

#endif
