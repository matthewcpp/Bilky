#ifndef BILKY_CARD_COLLECTION
#define BILKY_CARD_COLLECTION

#include <deque>
#include <algorithm>
#include <set>

#include "ICardCollection.hpp"

namespace Bilky{
	class CardCollection : public ICardCollection{
	public:
		virtual void AddCard(Card* card) override;
		virtual Card* GetCard(size_t index) const override;
		virtual Card* RemoveCard(size_t index) override;
		virtual size_t NumCards() const override;
		virtual void Clear() override;
		virtual void Shuffle() override;
		virtual void Assign(ICardCollection* collection) override;
		virtual void Remove(ICardCollection* collection) override;
		virtual bool Remove(Card* card) override;

	protected:
		typedef std::deque<Card*> CardVector;
		typedef std::set<Card*> CardSet;

	protected:
		CardVector m_cards;
	};
}

#endif