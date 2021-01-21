#pragma once
namespace tggd::common
{
	template<typename TCommand>
	class CommandProcessor
	{
	public:
		virtual void OnCommand(const TCommand&) = 0;
	};
}
