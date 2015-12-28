#include "CardCollection.hpp"

namespace Bilky{
	void CardCollection::AddCard(Card* card){
		m_cards.push_back(card);
	}

	Card* CardCollection::GetCard(size_t index) const{
		return m_cards[index];
	}

	Card* CardCollection::RemoveCard(size_t index){
		if (index < m_cards.size()){
			Card* card = m_cards[index];
			m_cards.erase(m_cards.begin() + index);

			return card;
		}
		else{
			return nullptr;
		}
	}

	size_t CardCollection::NumCards() const{
		return m_cards.size();
	}

	void CardCollection::Clear(){
		m_cards.clear();
	}

	void CardCollection::Shuffle(){
		std::random_shuffle(m_cards.begin(), m_cards.end());
	}

	void CardCollection::Assign(ICardCollection* collection){
		m_cards.clear();

		size_t collectionSize = collection->NumCards();

		for (size_t i = 0; i < collectionSize; i++){
			m_cards.push_back(collection->GetCard(i));
		}
	}

	void CardCollection::Remove(ICardCollection* collection) {
		size_t collectionSize = collection->NumCards();

		CardSet cardsToRemove;

		for (size_t i = 0; i < collectionSize; i++){
			cardsToRemove.insert(collection->GetCard(i));
		}

		CardVector currentCards = m_cards;
		m_cards.clear();

		for (auto& card : m_cards){
			if (!cardsToRemove.count(card))
				m_cards.push_back(card);
		}
	}

	bool CardCollection::Remove(Card* card) {
		for (size_t i = 0; i < m_cards.size(); i++) {
			if (m_cards[i] == card) {
				m_cards.erase(m_cards.begin() + i);
				return true;
			}
		}

		return false;
	}
}