#pragma once
#include "RoomCellObject.h"
namespace tggd::common
{
	template<typename TTerrain, typename TObjectData>
	class SimpleObject : public tggd::common::RoomCellObject<TTerrain, TObjectData>
	{
	private:
		TObjectData data;
	public:
		SimpleObject(const TObjectData& data)
			: data(data)
		{

		}
		const TObjectData& GetData() const
		{
			return data;
		}
	};
}
