//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CEGUI_IMPL_BATCH_HPP_INCLUDED
#define SGE_CEGUI_IMPL_BATCH_HPP_INCLUDED

#include <sge/cegui/impl/batch_fwd.hpp>
#include <sge/cegui/impl/clip.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/texture/planar_ref.hpp>
#include <sge/renderer/vertex/buffer_unique_ptr.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/renderer/vertex/count.hpp>
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
		sge::renderer::device::core_ref,
		sge::renderer::vertex::const_declaration_ref,
		sge::renderer::texture::planar_ref,
		sge::renderer::vertex::count,
		sge::cegui::impl::clip
	);

	batch(
		batch &&
	)
	noexcept;

	batch &
	operator=(
		batch &&
	)
	noexcept;

	~batch();

	[[nodiscard]]
	sge::renderer::texture::planar &
	texture() const;

	[[nodiscard]]
	sge::renderer::vertex::buffer &
	vertex_buffer() const;

	[[nodiscard]]
	sge::cegui::impl::clip
	clip() const;
private:
	sge::renderer::texture::planar_ref texture_;

	sge::renderer::vertex::buffer_unique_ptr vertex_buffer_;

	sge::cegui::impl::clip clip_;
};

}
}
}

#endif
