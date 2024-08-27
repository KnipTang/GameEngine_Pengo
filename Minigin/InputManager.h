#pragma once
#include "Singleton.h"
#include "Command.h"
#include <unordered_map>
#include <SDL.h>
#include "InputManager.h"
#define NOMINMAX
#include <Windows.h>
#include <memory>
namespace dae
{
	enum class InputActionType {
		IsDown,
		IsUp,
		IsPressed
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager() override;

		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;

		void BindCommand(SDL_Scancode key, InputActionType inputAction, std::unique_ptr<Command> command);
		void BindCommand(DWORD controllerIndex, WORD button, InputActionType inputAction, std::unique_ptr<Command> command);

		bool ProcessInput(float deltaTime);
	private:
		class ControllerPimpl;
		std::unique_ptr<ControllerPimpl> m_Pimpl;

		std::unordered_map<SDL_Scancode, std::pair<InputActionType, std::unique_ptr<Command>>> keyBindings;
		bool keysPressedThisFrame[SDL_NUM_SCANCODES] = { false };
		bool keysReleasedThisFrame[SDL_NUM_SCANCODES] = { false };
	};
}
