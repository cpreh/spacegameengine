template<typename T>
bool sge::math::contains(const rect<T>& outer,
                         const rect<T>& inner)
{
	return inner.left() >= outer.left() && inner.right() <= outer.right() &&
	       inner.top() >= outer.top() && inner.bottom() <= outer.bottom();
}


