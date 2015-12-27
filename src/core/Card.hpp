#ifndef BILKY_CARD_HPP
#define BILKY_CARD_HPP

#include <cstdint>

namespace Bilky{

	class Card{
	public:
		enum class Suit{ Spades, Hearts, Clubs, Diamonds};
		enum  class Color{ Red, Black };

	public:
		Card(Suit suit, uint32_t value);

	public:
		Color GetColor() const;
		Suit GetSuit() const;
		uint32_t GetValue() const;

	private:
		Suit m_suit;
		uint32_t m_value;
	};
}

#endif