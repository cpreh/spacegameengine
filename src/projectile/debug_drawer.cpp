#include "detail/debug_drawer_impl.hpp"
#include <sge/projectile/debug_drawer.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sge::projectile::debug_drawer::debug_drawer(
	world &_world,
	sge::renderer::device_ptr const _renderer)
:
	impl_(
		fcppt::make_unique_ptr<detail::debug_drawer_impl>(
			fcppt::ref(
				_world),
			_renderer))
{
}

void
sge::projectile::debug_drawer::update()
{
	impl_->update();
}

void
sge::projectile::debug_drawer::render(
	sge::renderer::matrix4 const &mvp)
{
	impl_->render(
		mvp);
}

void
sge::projectile::debug_drawer::active(
	bool const _active)
{
	impl_->active(
		_active);
}

bool 
sge::projectile::debug_drawer::active() const
{
	return impl_->active();
}

sge::projectile::debug_drawer::~debug_drawer()
{
}
