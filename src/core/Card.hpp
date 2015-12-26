#ifndef BILKY_CARD_HPP
#define BILKY_CARD_HPP

#include <cstdint>

namespace Bilky{

	class Card{
	public:
		enum class Suit : uint8_t{ Spades, Hearts, Clubs, Diamonds};
		enum  class Color : uint8_t{ Red, Black };

	public:
		Card(Suit suit, uint8_t value);

	public:
		Color GetColor() const;
		Suit GetSuit() const;
		uint8_t GetValue() const;

	private:
		Suit m_suit;
		uint8_t m_value;
	};
}

#endif