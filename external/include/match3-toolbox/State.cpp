#include "State.h"


State::State(int name_, std::vector<int> from_, std::function<void(int)> enter_, std::function<void()> update_, std::function<void(int)> exit_) {
	name = name_;
	from = from_;
	enter = enter_;
	update = update_;
	exit = exit_;
}


State::~State() {
}
