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

	ICardCollection* Player::GetHand(){
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

	void Player::SetScore(size_t score) {
		m_score = score;
	}

	bool Player::IsActive() const {
		return m_score < 21;
	}
}