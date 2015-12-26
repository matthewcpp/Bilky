#ifndef BILKY_ICARDCOLLECTION_HPP
#define BILKY_ICARDCOLLECTION_HPP

#include "Card.hpp"

namespace Bilky{
	class ICardCollection{
	public:
		virtual void AddCard(Card* card) = 0;
		virtual Card* GetCard(size_t index) const = 0;
		virtual Card* RemoveCard(size_t index) = 0;
		virtual size_t NumCards() const = 0;
		virtual void Clear() = 0;
		virtual void Shuffle() = 0;
		virtual void Assign(ICardCollection* collection) = 0;
		virtual void Remove(ICardCollection* collection) = 0;
	};
}

#endif