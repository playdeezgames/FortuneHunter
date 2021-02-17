#pragma once
namespace tggd::common
{
	template<typename TDimension>
	class XY
	{
	private:
		TDimension x;
		TDimension y;
	public:
		XY() : x(), y() {}
		XY(const TDimension& x, const TDimension& y) : x(x), y(y) {}
		const TDimension& GetX() const { return x; }
		const TDimension& GetY() const { return y; }
	};
	template<typename TDimension>
	XY<TDimension> operator+(const XY<TDimension>& first, const XY<TDimension>& second)
	{
		return XY<TDimension>(first.GetX() + second.GetX(), first.GetY() + second.GetY());
	}
}
