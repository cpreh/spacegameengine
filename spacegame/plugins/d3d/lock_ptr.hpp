#ifndef SGE_D3D_LOCK_PTR_HPP_INCLUDED
#define SGE_D3D_LOCK_PTR_HPP_INCLUDED

#include "./texture.hpp"
#include "./volume_texture.hpp"
#include "./cube_texture.hpp"

namespace sge
{
	namespace d3d
	{
		template<typename T> class lock_ptr;
		template<> class lock_ptr<texture> {
		public:
			lock_ptr<texture>(texture* const t, const lock_rect* const r = 0)
			: t(t)
			{
				t->lock(r);
			}
			~lock_ptr<texture>() { t->unlock(); }
		private:
			texture* t;
		};
		template<> class lock_ptr<volume_texture> {
		public:
			lock_ptr<volume_texture>(volume_texture* const t, const lock_box* const b = 0)
			: t(t)
			{
				t->lock(b);
			}
			~lock_ptr<volume_texture>() { t->unlock(); }
		private:
			volume_texture* t;
		};
		template<> class lock_ptr<cube_texture> {
		public:
			lock_ptr<cube_texture>(cube_texture* const t, const cube_side s, const lock_rect* const r = 0)
			: t(t)
			{
				t->lock(s,r);
			}
			~lock_ptr<cube_texture>() { t->unlock(); }
		private:
			cube_texture* t;
		};
	}
}

#endif
