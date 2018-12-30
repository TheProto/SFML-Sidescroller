#include "StateMachine.h"
#include <iostream>

namespace ProtoEngine {

	StateMachine::StateMachine() {
	}
	
	StateMachine::~StateMachine() {
	}


	void StateMachine::AddState(StateRef newState, bool is_Replacing) {
		this->_isAdding = true;
		this->_isReplacing = is_Replacing;
		this->_newState = std::move( newState );
	}

	void StateMachine::RemoveState() {
		this->_isRemoving = true;
	}

	void StateMachine::ProcessStateChanges() {

		if (this->_isRemoving && !this->_states.empty()) 
		{
			this->_states.pop();

			if (!this->_states.empty()) {
				this->_states.top()->Resume();
			}

			this->_isRemoving = false;
		}

		//TODO:Add handling of error messages if there are no states present;
		if (this->_isAdding) {
			if (!this->_states.empty()) 
			{
				if (this->_isReplacing)
				{
					this->_states.pop();
					std::cout << "StatePopped:" << std::endl;
					this->_isReplacing = false;
				}
				else 
				{
					this->_states.top()->Pause();
				}
			}

			this->_states.push(std::move(this->_newState));
			this->_states.top()->Init();
			this->_isAdding = false;
			std::cout << "StateCount:" << _states.size() << std::endl;
			std::cout << "CurrentlyActiveState:" << _states.top()->get_name() << std::endl;
		}

	}

	StateRef &StateMachine::GetActiveState() 
	{
		return this->_states.top();
	}
}