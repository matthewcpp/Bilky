#include "Dealer.hpp"

namespace Bilky{
	void Dealer::CreateCardPool(size_t numPlayers){
		Clear();

		m_numDecks = numPlayers / 5 + 1;

		for (size_t i = 0; i < m_numDecks; i++){
			CreateCardsInSuit(Card::Suit::Hearts);
			CreateCardsInSuit(Card::Suit::Diamonds);
			CreateCardsInSuit(Card::Suit::Clubs);
			CreateCardsInSuit(Card::Suit::Spades);
		}
	}

	void Dealer::Clear(){
		m_numDecks = 0;
		m_deck.Clear();
	}

	size_t Dealer::GetNumDecks() const{
		return m_numDecks;
	}

	void Dealer::Reset(bool shuffle){
		m_deck.Clear();

		for (auto& card : m_cards){
			m_deck.AddCard(card.get());
		}

		if (shuffle)
			m_deck.Shuffle();
	}

	void Dealer::CreateCardsInSuit(Card::Suit suit){
		CardReference card;
		for (uint8_t v = 2; v <= 14; v++){
			card.reset(new Card(suit, v));
			m_cards.push_back(card);
		}
	}

	Card* Dealer::DealCardToPlayer(Player* player){
		if (m_deck.NumCards() > 0){

		ICardCollection* playerHand = player->Hand();
			
		Card* card = m_deck.RemoveCard(0);
		playerHand->AddCard(card);

		for (auto& callback : m_callbacks){
			callback(player, card);
		}

		return card;
		}
		else{
			return nullptr;
		}
		
	}

	void Dealer::BindCardDealCallback(CardDealCallback callback){
		m_callbacks.push_back(callback);
	}
}