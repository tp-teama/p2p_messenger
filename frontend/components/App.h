#include "Base.cpp"
#include "constants.cpp"

class A: public Base {
public:
	using Base::Base;
	int do_something() override;
	ReturnCode render() override;
	ReturnCode redraw(int el) override;
};
