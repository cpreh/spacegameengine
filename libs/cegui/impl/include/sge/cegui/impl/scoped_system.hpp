//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_IMPL_SCOPED_SYSTEM_HPP_INCLUDED
#define SGE_CEGUI_IMPL_SCOPED_SYSTEM_HPP_INCLUDED

#include <sge/cegui/impl/image_codec_fwd.hpp>
#include <sge/cegui/impl/renderer_fwd.hpp>
#include <sge/cegui/impl/resource_provider_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace cegui
{
namespace impl
{

class scoped_system
{
	FCPPT_NONCOPYABLE(
		scoped_system
	);
public:
	scoped_system(
		sge::cegui::impl::renderer &,
		sge::cegui::impl::image_codec &,
		sge::cegui::impl::resource_provider &
	);

	~scoped_system();
};

}
}
}

#endif
