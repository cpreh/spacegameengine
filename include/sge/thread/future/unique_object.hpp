#ifndef SGE_THREAD_FUTURE_UNIQUE_OBJECT_HPP_INCLUDED
#define SGE_THREAD_FUTURE_UNIQUE_OBJECT_HPP_INCLUDED

#include <sge/thread/future/detail/object.hpp>
#include <sge/thread/future/shared_object_fwd.hpp>
#include <sge/thread/future/uninitialized.hpp>
#include <sge/thread/future/state.hpp>
#include <sge/noncopyable.hpp>
#include <sge/shared_ptr.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/thread/detail/move.hpp>
#include <boost/thread/thread_time.hpp>

namespace sge
{
namespace thread
{
namespace future
{
template<typename T>
class unique_object
{
//SGE_NONCOPYABLE(unique_object)
private:
	unique_object(
		unique_object &);
	unique_object &operator=(
		unique_object &);
	typedef sge::shared_ptr< detail::object<T> > object_ptr;
	typedef typename boost::add_reference<T>::type reference;
public:
	unique_object();
	unique_object(
		object_ptr);
	unique_object(
		boost::detail::thread_move_t<unique_object>);
	unique_object &operator=(
		boost::detail::thread_move_t<unique_object>);
	operator boost::detail::thread_move_t<unique_object>();
	void swap(
		unique_object &);
	T move();
	bool try_move(
		reference);
	template<typename Duration>
	bool timed_move(
		reference,
		Duration const &);
	bool timed_move_until(
		reference,
		boost::system_time const &);
	reference get();
	bool try_get(
		reference);
	template<typename Duration>
	bool timed_get(
		reference,
		Duration const&);
	bool timed_get_until(
		reference,
		boost::system_time const&);
	future::state::type state() const;
	bool is_ready() const;
	bool has_exception() const;
	bool has_value() const;
	bool was_moved() const;
	void wait() const;
	template<typename Duration>
	bool timed_wait(
		Duration const&) const;
	bool timed_wait_until(
		boost::system_time const&) const;
private:
	object_ptr object_;
	friend class shared_object<T>;
};

template<>
class unique_object<void>
{
//SGE_NONCOPYABLE(unique_object);
private:
	unique_object(
		unique_object &);
	unique_object &operator=(
		unique_object &);
	typedef sge::shared_ptr< detail::object<void> > object_ptr;
public:
	unique_object(
		object_ptr);
	unique_object();
	unique_object(
		boost::detail::thread_move_t<unique_object>);
	unique_object& operator=(
		boost::detail::thread_move_t<unique_object>);
	operator boost::detail::thread_move_t<unique_object>();
	void swap(unique_object&);
	void move();
	void get();
	// functions to check state, and wait for ready
	sge::thread::future::state::type state() const;
	bool is_ready() const;
	bool has_exception() const;
	bool has_value() const;
	bool was_moved() const;
	void wait() const;
	template<typename Duration>
	bool timed_wait(Duration const&) const;
	bool timed_wait_until(boost::system_time const&) const;
private:
	object_ptr object_;
	friend class shared_object<void>;
};
}
}
}

template<typename T>
sge::thread::future::unique_object<T>::unique_object()
:
	object_()
{
}

template<typename T>
sge::thread::future::unique_object<T>::unique_object(
	object_ptr _object)
:
	object_(
		_object)
{
}

template<typename T>
sge::thread::future::unique_object<T>::unique_object(
	boost::detail::thread_move_t<unique_object> _other)
:
	object_(
		_other->object_)
{
	_other->object_.reset();
}

template<typename T>
sge::thread::future::unique_object<T> &sge::thread::future::unique_object<T>::operator=(
	boost::detail::thread_move_t<unique_object> _other)
{
	object_ = _other->object_;
	_other->object_.reset();
	return *this;
}

template<typename T>
sge::thread::future::unique_object<T>::operator boost::detail::thread_move_t< sge::thread::future::unique_object<T> >()
{
	return 
		boost::detail::thread_move_t<unique_object>(
			*this);
}

template<typename T>
void sge::thread::future::unique_object<T>::swap(
	unique_object &_other)
{
	object_.swap(
		_other);
}

template<typename T>
T sge::thread::future::unique_object<T>::move()
{
	if (!object_)
		throw uninitialized();
	return object_->move();
}

template<typename T>
bool sge::thread::future::unique_object<T>::try_move(
	reference _dest)
{
	if (!object_)
		throw uninitialized();
	return 
		object_->try_move(
			_dest);
}

template<typename T>
template<typename Duration>
bool sge::thread::future::unique_object<T>::timed_move(
	reference _dest,
	Duration const &_time)
{
	return 
		timed_move_until(
			_dest,
			boost::get_system_time()+_time);
}

template<typename T>
bool sge::thread::future::unique_object<T>::timed_move_until(
	reference _dest,
	boost::system_time const &_time)
{
	if (!object_)
		throw uninitialized();
	return 
		object_->timed_move_until(
			_dest,
			_time);
}

template<typename T>
typename sge::thread::future::unique_object<T>::reference sge::thread::future::unique_object<T>::get()
{
	if (!object_)
		throw uninitialized();
	return object_->get();
}

template<typename T>
bool sge::thread::future::unique_object<T>::try_get(
	reference _dest)
{
	if (!object_)
		throw uninitialized();
	return 
		object_->try_get(
			_dest);
}

template<typename T>
template<typename Duration>
bool sge::thread::future::unique_object<T>::timed_get(
	reference _dest,
	Duration const&_time)
{
	return 
		timed_get_until(
			_dest,
			boost::get_system_time()+_time);
}

template<typename T>
bool sge::thread::future::unique_object<T>::timed_get_until(
	reference _dest,
	boost::system_time const& _time)
{
	if (!object_)
		throw uninitialized();
	return 
		object_->timed_get_until(
			_dest,
			_time);
}

template<typename T>
sge::thread::future::state::type sge::thread::future::unique_object<T>::state() const
{
	if (!object_)
		throw uninitialized();
	return object_->state();
}

template<typename T>
bool sge::thread::future::unique_object<T>::is_ready() const
{
	return state() == sge::thread::future::state::ready;
}

template<typename T>
bool sge::thread::future::unique_object<T>::has_exception() const
{
	if(!object_)
		return false;
	boost::lock_guard<boost::mutex> guard(
		object_->mutex_);
	return 
		object_->done_ && object_->exception_;
}

template<typename T>
bool sge::thread::future::unique_object<T>::has_value() const
{
	if(!object_)
		return false;
	boost::lock_guard<boost::mutex> guard(
		object_->mutex_);
	return 
		object_->done_ && object_->result_;
}

template<typename T>
bool sge::thread::future::unique_object<T>::was_moved() const
{
	return state() == sge::thread::future::state::moved;
}

template<typename T>
void sge::thread::future::unique_object<T>::wait() const
{
	if (object_)
		throw uninitialized();
	object_->wait();
}

template<typename T>
template<typename Duration>
bool sge::thread::future::unique_object<T>::timed_wait(
	Duration const& _time) const
{
	return
		timed_wait_until(
			boost::get_system_time()+_time);
}

template<typename T>
bool sge::thread::future::unique_object<T>::timed_wait_until(
	boost::system_time const& _time) const
{
	if (object_)
		throw uninitialized();
	return 
		object_->timed_wait_until(
			_time);
}

sge::thread::future::unique_object<void>::unique_object(
	object_ptr _object)
:
	object_(
		_object)
{
}

sge::thread::future::unique_object<void>::unique_object()
{
}

sge::thread::future::unique_object<void>::unique_object(
	boost::detail::thread_move_t<unique_object> _other)
:
	object_(
		_other->object_)
{
	_other->object_.reset();
}

sge::thread::future::unique_object<void>& sge::thread::future::unique_object<void>::operator=(
	boost::detail::thread_move_t<unique_object> _other)
{
	object_ = _other->object_;
	_other->object_.reset();
	return *this;
}

sge::thread::future::unique_object<void>::operator boost::detail::thread_move_t<unique_object>()
{
	return 
		boost::detail::thread_move_t<unique_object>(
			*this);
}

void sge::thread::future::unique_object<void>::swap(
	unique_object& _other)
{
	object_.swap(
		_other.object_);
}

void sge::thread::future::unique_object<void>::move()
{
	if(!object_)
		throw uninitialized();

	object_->move();
}

void sge::thread::future::unique_object<void>::get()
{
	if(!object_)
		throw uninitialized();
	object_->get();
}

sge::thread::future::state::type sge::thread::future::unique_object<void>::state() const
{
	if(!object_)
		return sge::thread::future::state::uninitialized;
	return object_->state();
}

bool sge::thread::future::unique_object<void>::is_ready() const
{
	return state() == sge::thread::future::state::ready;
}

bool sge::thread::future::unique_object<void>::has_exception() const
{
	if(!object_)
		return false;
	boost::lock_guard<boost::mutex> guard(
		object_->mutex_);
	return 
		object_->done_ && object_->exception_;
}

bool sge::thread::future::unique_object<void>::has_value() const
{
	if(!object_)
		return false;
	boost::lock_guard<boost::mutex> guard(
		object_->mutex_);
	return 
		object_->done_ && object_->result_;
}

bool sge::thread::future::unique_object<void>::was_moved() const
{
	return state() == sge::thread::future::state::moved;
}

void sge::thread::future::unique_object<void>::wait() const
{
	if(!object_)
		throw uninitialized();
	object_->wait();
}

template<typename Duration>
bool sge::thread::future::unique_object<void>::timed_wait(
	Duration const&_time) const
{
	return 
		timed_wait_until(
			boost::get_system_time()+_time);
}

bool sge::thread::future::unique_object<void>::timed_wait_until(
	boost::system_time const&_time) const
{
	if(!object_)
		throw uninitialized();
	return 
		object_->timed_wait_until(
			_time);
}

#endif // SGE_THREAD_FUTURE_UNIQUE_OBJECT_HPP_INCLUDED
