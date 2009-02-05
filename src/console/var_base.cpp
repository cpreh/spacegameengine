#include <sge/console/var_base.hpp>
#include <sge/console/object.hpp>

sge::console::var_base::var_base(
	object &_object,
	sge::string const &_name)
	: object_(_object),
	  name_(_name)
{
	object_.insert(*this);
}

sge::string const sge::console::var_base::name() const
{
	return name_;
}

sge::console::var_base::~var_base()
{
	object_.erase(*this);
}
