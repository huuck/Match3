#pragma once
#include <vector>
#include <functional>

class State
{
public:
	State(int name_, std::vector<int> from_, std::function<void(int)> enter_, std::function<void()> update_, std::function<void(int)> exit_);

	int name;
	std::vector<int> from;

	std::function<void(int)> enter;
	std::function<void()> update;
	std::function<void(int)> exit;

	~State();
};

