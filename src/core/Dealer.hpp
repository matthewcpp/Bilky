#ifndef BILKY_DEALER_HPP
#define BILKY_DEALER_HPP

#include <memory>
#include <deque>
#include <vector>
#include <functional>

#include "Player.hpp"
#include "Card.hpp"
#include "CardCollection.hpp"
#include "DealInfo.hpp"

namespace Bilky {
	class Dealer{
	public:
		typedef std::function<void(Player* player, Card* card)> CardDealCallback;

	public:
		void CreateCardPool(size_t numPlayers);

		size_t GetNumDecks() const;

		void Clear();
		void Reset(bool shuffle = true);

		Card* DealCardToPlayer(Player* player);

		void BindCardDealCallback(CardDealCallback callback);

	private:
		void CreateCardsInSuit(Card::Suit suit);

	private:
		typedef std::shared_ptr<Card> CardReference;
		typedef std::vector<CardReference> CardVector;

		typedef std::vector<CardDealCallback> CardDealCallbackVector;

	private:
		size_t m_numDecks;

		CardVector m_cards;
		CardCollection m_deck;

		CardDealCallbackVector m_callbacks;
	};
}

#endif