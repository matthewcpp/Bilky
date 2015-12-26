#include "Round.hpp"

namespace Bilky{
	Round::Round(uint8_t handSize){
		m_handSize = handSize;
	}

	uint8_t Round::GetHandSize() const{
		return m_handSize;
	}

	void Round::SetTradeLimit(uint8_t maxTradeSize){
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
	
}