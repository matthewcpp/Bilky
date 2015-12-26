#ifndef BILKY_DEAL_REQUEST_HPP
#define BILKY_DEAL_REQUEST_HPP

#include "Player.hpp"

namespace Bilky{
	class DealInfo{
	public:
		DealInfo(Player* player, size_t numCards) : m_player(player), m_numCards(numCards){}

	public:
		inline Player* GetPlayer() const;
		inline size_t GetNumCards() const;

	private:
		Player* m_player;
		size_t m_numCards;
	};

	inline Player* DealInfo::GetPlayer() const { return m_player; }
	inline size_t DealInfo::GetNumCards() const { return m_numCards; }
}

#endif