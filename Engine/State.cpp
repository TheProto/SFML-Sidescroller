#include "State.h"

namespace ProtoEngine
{
	std::string State::get_name() {
		return _stateName;
	}

	void State::set_name(std::string stateName) {
		_stateName.assign(stateName);
	}
}