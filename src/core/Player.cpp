#include "Player.hpp"

namespace Bilky{
	Player::Player(const std::string& name){
		m_name = name;

		Reset();
	}

	void Player::Reset(){
		m_score = 0;
		m_hand.Clear();
	}

	std::string Player::GetName() const{
		return m_name;
	}

	const ICardCollection* Player::GetHand() const{
		return &m_hand;
	}

	ICardCollection* Player::Hand(){
		return &m_hand;
	}

	uint8_t Player::GetScore(){
		return m_score;
	}
}