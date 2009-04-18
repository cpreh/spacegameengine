#include "wipe_texture.hpp"
#include "wipe_image_view.hpp"
#include <sge/renderer/texture.hpp>
#include <sge/renderer/scoped_texture_lock.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/math/rect_impl.hpp>

void sge::gui::utility::wipe_texture(
	renderer::texture_ptr const t)
{
	renderer::scoped_texture_lock const lock_(
		t,
		renderer::lock_rect(
			t->dim()),
		renderer::lock_flags::readwrite);
	
	wipe_image_view(
		lock_.value());
}
