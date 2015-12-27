#include "Trick.hpp"

namespace Bilky {
	Trick::Trick() {
		m_leadPlayer = nullptr;
		m_winningPlayer = nullptr;

		m_winningPlayer = nullptr;
		m_winningCard = nullptr;

		m_isComplete = false;
	}

	const Player* Trick::GetLeadPlayer() const {
		return m_leadPlayer;
	}

	const Card* Trick::GetLeadCard() const {
		return m_leadCard;
	}

	const Player* Trick::GetWinningPlayer() const {
		return m_winningPlayer;
	}

	const Card* Trick::GetWinningCard() const {
		return m_winningCard;
	}

	size_t Trick::GetNumPlays() const {
		return m_plays.size();
	}

	void Trick::CardPlay(Player* player, Card* card) {
		if (m_plays.size() == 0) {
			m_leadPlayer = player;
			m_winningPlayer = player;

			m_leadCard = card;
			m_winningCard = card;
		}
		else if (card->GetValue() >= m_winningCard->GetValue()){
			m_winningCard = card;
			m_winningPlayer = player;
		}

		m_plays[player] = card;
	}

	const Card* Trick::GetCardForPlayer(Player* player) const {
		auto result = m_plays.find(player);

		if (result == m_plays.end()) {
			return nullptr;
		}
		else {
			return result->second;
		}
	}

	bool Trick::IsComplete() const {
		return m_isComplete;
	}
	void Trick::SetComplete(bool complete) {
		m_isComplete = complete;
	}
}