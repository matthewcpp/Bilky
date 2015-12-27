#include "Round.hpp"

namespace Bilky{
	Round::Round(Player* leadPlayer, uint32_t handSize){
		m_handSize = handSize;
		m_leadPlayer = leadPlayer;

		m_isComplete = false;
	}

	uint8_t Round::GetHandSize() const{
		return m_handSize;
	}

	void Round::SetTradeLimit(uint32_t maxTradeSize){
		m_maxTradeSize = maxTradeSize;
	}

	uint8_t Round::GetTradeLimit() const{
		return m_maxTradeSize;
	}

	void Round::CardTrade(Player* player, ICardCollection* cards){
		CardCollection* collection = new CardCollection();
		collection->Assign(cards);

		CardCollectionReference collectionRef;
		collectionRef.reset(collection);

		m_playerTrades[player] = collectionRef;
	}

	const ICardCollection* Round::GetTradeForPlayer(Player* player) const{
		auto result = m_playerTrades.find(player);

		if (result == m_playerTrades.end()){
			return nullptr;
		}
		else{
			return result->second.get();
		}
	}
	
	Trick* Round::CreateTrick() {
		TrickReference newTrick;
		newTrick.reset(new Trick());

		m_tricks.push_back(newTrick);

		return newTrick.get();
	}

	size_t Round::GetNumTricks() const {
		return m_tricks.size();
	}

	const Trick* Round::GetCurrentTrick() const {
		if (m_tricks.size() > 0) {
			return m_tricks[m_tricks.size() - 1].get();
		}
		else {
			return nullptr;
		}
	}

	const Trick* Round::GetTrick(size_t index) const {
		if (index < m_tricks.size()) {
			return m_tricks[index].get();
		}
		else {
			return nullptr;
		}
	}

	const Player* Round::GetLeadPlayer() const {
		return m_leadPlayer;
	}

	bool Round::IsComplete() const {
		return m_isComplete;
	}

	void Round::SetComplete(bool complete) {
		m_isComplete = complete;
	}

	const Player* Round::GetWinningPlayer() const {
		if (IsComplete()) {
			return m_tricks.back()->GetWinningPlayer();
		}
		else {
			return nullptr;
		}

	}
}