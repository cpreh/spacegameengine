#include <sge/console/console.hpp>
#include <sge/console/singleton.hpp>

void sge::con::eval(const string &s)
{
	instance().eval(s);
}

void sge::con::chat_callback(const callback &c)
{
	instance().chat = c;
}

void sge::con::add(const string &name,const callback &c)
{
	instance().add(name,c);
}

void sge::con::prefix(const string::value_type &c)
{
	instance().prefix = c;
}

sge::string::value_type sge::con::prefix()
{
	return instance().prefix;
}

void sge::con::read_config(
	filesystem::path const &s)
{
	instance().read_config(s);
}

const sge::con::var_map &sge::con::vars()
{
	return instance().vars;
}

const sge::con::callback_map &sge::con::funcs()
{
	return instance().funcs;
}

sge::string const sge::con::get_var(const sge::string &name)
{
	return instance().var(name);
}

void sge::con::set_var(const sge::string &name,const sge::string &value)
{
	instance().var(name,value);
}

void sge::con::latch(const sge::string &name,const sge::string &value)
{
	instance().latch(name,value);
}
