#ifndef SGE_D3D_RESOURCE_HPP_INCLUDED
#define SGE_D3D_RESOURCE_HPP_INCLUDED

namespace sge
{
	namespace d3d
	{
		class renderer;

		class resource {
		public:
			resource(renderer* r);
			virtual void on_loss() {}
			virtual void on_reset() {}
			virtual ~resource();
		private:
			renderer* r;
		};
	}
}

#endif
