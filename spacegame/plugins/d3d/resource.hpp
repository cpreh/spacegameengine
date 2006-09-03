#ifndef SGE_D3D_RESOURCE_HPP_INCLUDED
#define SGE_D3D_RESOURCE_HPP_INCLUDED

#include <list>

namespace sge
{
namespace d3d
{

class renderer;

typedef std::list<renderer*> resource_list;

class resource {
public:
	resource(renderer* r, bool needs_restore);
	virtual void on_loss() {}
	virtual void on_reset() {}
	virtual ~resource();
private:
	resource_list*          my_list;
	resource_list::iterator my_place;
};

}
}

#endif
