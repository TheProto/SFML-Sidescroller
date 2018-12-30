#pragma once
#include <string>
namespace ProtoEngine
{
	class State {
	public:
		virtual void Init() = 0;
		virtual void HandleInput() = 0;
		virtual void Update(float dt) = 0;
		virtual void Draw(float dt) = 0;

		virtual void Pause() {}
		virtual void Resume() {}

		std::string get_name();
		void set_name(std::string stateName);

	private:
		std::string _stateName;
	};
}