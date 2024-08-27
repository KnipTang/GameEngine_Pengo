#pragma once
#include <string>

namespace dae
{
	struct PlayMessage
	{
		std::string name;
		int volume;
		int loops;
	};
	class SoundSystem
	{
	public:
		SoundSystem() = default;
		virtual ~SoundSystem() = default;

		SoundSystem(const SoundSystem& other) = delete;
		SoundSystem(SoundSystem&& other) = delete;
		SoundSystem& operator=(const SoundSystem& other) = delete;
		SoundSystem& operator=(SoundSystem&& other) = delete;

		virtual void Update() = 0;

		virtual void play(const std::string name, const int volume, const int loops = 0) = 0;
		virtual void Stop() = 0;

		virtual void Mute() = 0;
	};
}