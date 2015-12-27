#include "Player.hpp"

namespace Bilky{
	Player::Player(const std::string& name, uint32_t id){
		m_name = name;
		m_id = id;

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

	uint32_t Player::GetScore(){
		return m_score;
	}

	uint32_t Player::GetId() const {
		return m_id;
	}

	void Player::Setid(uint32_t id) {
		m_id = id;
	}
}