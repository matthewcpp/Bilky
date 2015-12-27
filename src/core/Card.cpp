#include "Card.hpp"

namespace Bilky{
	Card::Card(Suit suit, uint32_t value){
		m_suit = suit;
		m_value = value;
	}

	Card::Color Card::GetColor() const{
		if (m_suit == Suit::Clubs || m_suit == Suit::Spades)
			return Color::Black;
		else
			return Color::Red;
	}

	Card::Suit Card::GetSuit() const{
		return m_suit;
	}

	uint32_t Card::GetValue() const{
		return m_value;
	}
}