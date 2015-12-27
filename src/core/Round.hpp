#ifndef BILKY_DEAL_HPP
#define BILKY_DEAL_HPP

#include <cstdint>
#include <map>
#include <memory>
#include <vector>

#include "Player.hpp"
#include "Trick.hpp"
#include "CardCollection.hpp"

namespace Bilky{
	class Round{
	public:
		Round(Player* leadPlayer, uint32_t handSize);

		uint8_t GetHandSize() const;

		void SetTradeLimit(uint32_t maxTradeSize);
		uint8_t GetTradeLimit() const;

		void CardTrade(Player* player, ICardCollection* cards);
		const ICardCollection* GetTradeForPlayer(Player* player) const;

		Trick* CreateTrick();
		size_t GetNumTricks() const;
		const Trick* GetCurrentTrick() const;
		const Trick* GetTrick(size_t index) const;

		const Player* GetLeadPlayer() const;
		const Player* GetWinningPlayer() const;

		bool IsComplete() const;
		void SetComplete(bool complete = true);

	private:
		typedef std::shared_ptr<CardCollection> CardCollectionReference;
		typedef std::map<Player*, CardCollectionReference> CardCollectionMap;

		typedef std::shared_ptr<Trick> TrickReference;
		typedef std::vector<TrickReference> TrickVector;

	private:
		uint32_t m_handSize;
		uint32_t m_maxTradeSize;

		CardCollectionMap m_playerTrades;

		TrickVector m_tricks;

		Player* m_leadPlayer;

		bool m_isComplete;
	};
}

#endif