#include "../resource.hpp"
#include "../renderer.hpp"

sge::d3d::resource::resource(renderer* r)
: r(r)
{
	r->resources.push_back(this);
}

sge::d3d::resource::~resource()
{
	r->resources.erase(std::find(r->resources.begin(),r->resources.end(),this));
}
