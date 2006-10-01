#include "../resource.hpp"
#include "../renderer.hpp"

sge::d3d::resource::resource(renderer* const r, const bool needs_restore)
: my_list(needs_restore ? &r->resources : 0),
  my_place(needs_restore ? my_list.insert(my_list.end()) : my_list.end())
{}

sge::d3d::resource::~resource()
{
	if(my_list)
		my_list->erase(my_place);
}
