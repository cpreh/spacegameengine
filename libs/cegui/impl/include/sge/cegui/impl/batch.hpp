//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_IMPL_BATCH_HPP_INCLUDED
#define SGE_CEGUI_IMPL_BATCH_HPP_INCLUDED

#include <sge/cegui/impl/batch_fwd.hpp>
#include <sge/cegui/impl/clip.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference.hpp>


namespace sge
{
namespace cegui
{
namespace impl
{

class batch
{
	FCPPT_NONCOPYABLE(
		batch
	);
public:
	batch(
		sge::renderer::device::core &,
		sge::renderer::vertex::declaration const &,
		sge::renderer::texture::planar &,
		sge::renderer::vertex::count,
		sge::cegui::impl::clip
	);

	batch(
		batch &&
	);

	batch &
	operator=(
		batch &&
	);

	~batch();

	sge::renderer::texture::planar &
	texture() const;

	sge::renderer::vertex::buffer &
	vertex_buffer() const;

	sge::cegui::impl::clip
	clip() const;
private:
	typedef
	fcppt::reference<
		sge::renderer::texture::planar
	>
	planar_texture_ref;

	planar_texture_ref texture_;

	sge::renderer::vertex::buffer_unique_ptr vertex_buffer_;

	sge::cegui::impl::clip clip_;
};

}
}
}

#endif
