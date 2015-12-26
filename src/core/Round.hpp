#ifndef BILKY_DEAL_HPP
#define BILKY_DEAL_HPP

#include <cstdint>
#include <map>
#include <memory>

#include "Player.hpp"
#include "Trick.hpp"
#include "CardCollection.hpp"

namespace Bilky{
	class Round{
	public:
		Round(uint8_t handSize);

		uint8_t GetHandSize() const;

		void SetTradeLimit(uint8_t maxTradeSize);
		uint8_t GetTradeLimit() const;

		void CardTrade(Player* player, ICardCollection* cards);
		const ICardCollection* GetTradeForPlayer(Player* player) const;

	private:
		typedef std::shared_ptr<CardCollection> CardCollectionReference;
		typedef std::map<Player*, CardCollectionReference> CardCollectionMap;

	private:
		uint8_t m_handSize;
		uint8_t m_maxTradeSize;

		CardCollectionMap m_playerTrades;
	};
}

#endif