#include "Game.hpp"

namespace Bilky{

	Game::Game(){
		m_gameState = State::Stopped;
	}

	Roster* Game::GetRoster() {
		return &m_roster;
	}

	Game::State Game::GetState() const{
		return m_gameState;
	}

	Player* Game::GetActivePlayer(){
		return m_roster.GetPlayer(m_currentPlayer);
	}

	bool Game::Start(){
		if (m_roster.GetNumPlayers() < 2){
			return false;
		}

		if (m_gameState != State::Stopped){
			return false;
		}

		Reset();

		//setup the deck for this game
		m_dealer.CreateCardPool(m_roster.GetNumPlayers());
		
		NewRound(5);

		return true;
	}

	bool Game::Stop(){
		if (m_gameState != State::Stopped){
			return true;
		}
		else{
			return false;
		}
	}

	void Game::Reset(){
		m_roster.Reset();

		m_rounds.clear();
		m_dealer.Clear();

		m_currentPlayer = 0;
	}

	void Game::NewRound(uint32_t handSize){
		SetState(State::DealingHands);
		m_dealer.Reset();
		m_roster.GetActivePlayers(m_activePlayers);

		//first round will start with a randomized lead player
		if (m_rounds.size() == 0) {
			m_startingPlayer = rand() % m_activePlayers.size();
		}
		else { //otherwise get the winner from the last round
			m_startingPlayer = m_rounds.back()->GetWinningPlayer()->GetId();
		}

		m_currentPlayer = m_startingPlayer;

		Round* round = new Round(m_roster.GetPlayer(m_startingPlayer), handSize);
		RoundReference ref;
		ref.reset(round);
		m_rounds.push_back(ref);

		//deal cards to players
		for (uint32_t i = 0; i < handSize; i++){
			for (auto& player : m_activePlayers){
				m_dealer.DealCardToPlayer(player);
			}
		}

		SetState(State::WaitingForDealerTrade);
	}

	void Game::RoundEnd() {
		Round* currentRound = GetCurrentRound();
		
		currentRound->SetComplete();

		Player* winningPlayer = currentRound->GetCurrentTrick()->GetWinningPlayer();
		uint32_t winningCardValue = currentRound->GetCurrentTrick()->GetWinningCard()->GetValue();

		// if the last trick was won with an ace (highly unlikely) the hand size and point value is 11
		uint32_t points = (winningCardValue == 14) ? 11 : std::max(winningCardValue, 10U);

		winningPlayer->SetScore(winningPlayer->GetScore() + points);

		NewRound(points);
	}

	void Game::NewTrick() {
		RoundReference currentRound = m_rounds.back();
		
		//if this is the first trick in a round, then the player following the dealer goes first
		if (currentRound->GetNumTricks() == 0) {
			NextActivePlayer();
			m_startingPlayer = m_currentPlayer;
		}
		else { //the winning player from the last trick goes first
			m_startingPlayer = currentRound->GetCurrentTrick()->GetWinningPlayer()->GetId();
			m_currentPlayer = m_startingPlayer;
		}

		currentRound->CreateTrick();

		SetState(State::WaitingForActivePlayer);
	}

	void Game::TrickEnd() {
		Round* currentRound = GetCurrentRound();
		Trick* currentTrick = currentRound->GetCurrentTrick();

		currentTrick->SetComplete();

		//all tricks have been completed, start a new round
		if (currentRound->GetNumTricks() == currentRound->GetHandSize()) {
			RoundEnd();
		}
		else { //else start a new trick
			NewTrick();
		}
	}

	Dealer* Game::GetDealer(){
		return &m_dealer;
	}

	bool Game::PlayCard(Player* player, Card* card) {
		if (m_gameState != State::WaitingForActivePlayer)
			return false;

		if (player == GetActivePlayer()) {
			if (!PlayIsValid(player, card))
				return false;

			Trick* currentTrick = (Trick*)GetCurrentRound()->GetCurrentTrick();
			currentTrick->CardPlay(player, card);
			player->GetHand()->Remove(card);

			NextActivePlayer();

			if (m_currentPlayer == m_startingPlayer)
				TrickEnd();

			return true;
		}
		else {
			return false;
		}
	}

	bool Game::PlayIsValid(Player* player, Card* card) const {
		const Trick* currentTrick = GetCurrentRound()->GetCurrentTrick();
		const ICardCollection* playerHand = player->GetHand();

		//player may always play the lowest card in their hand
		size_t handSize = playerHand->NumCards();
		bool cardIsLowest = true;
		for (size_t i = 0; i < handSize; i++) {
			if (playerHand->GetCard(i)->GetValue() < card->GetValue()) {
				cardIsLowest = false;
				break;
			}
		}
		
		if (cardIsLowest) return true;

		// if the card is not the lowest then it must be greater than or equal to the leading card for the current trick
		const Card* leadCard = currentTrick->GetLeadCard();
		if (!leadCard) {
			return true;
		}
		else {
			return card->GetValue() >= leadCard->GetValue();
		}
	}

	bool Game::TradeCards(Player* player, ICardCollection* cards){
		if (m_gameState == State::WaitingForDealerTrade)
			return DealerTradeCards(player, cards);
		else if (m_gameState == State::WaitingForPlayerTrade)
			return PlayerTradeCards(player, cards);
		else
			return false;
	}

	void Game::PerformCardTrade(Player* player, ICardCollection* cards){
		Round* round = (Round*)GetCurrentRound();
		round->CardTrade(player, cards);

		player->GetHand()->Remove(cards);

		size_t numCards = cards->NumCards();
		for (size_t i = 0; i < numCards; i++){
			m_dealer.DealCardToPlayer(player);
		}

		NextActivePlayer();
	}

	bool Game::DealerTradeCards(Player* player, ICardCollection* cards){
		if (player == GetActivePlayer()){
			Round* round = (Round*)GetCurrentRound();
			round->SetTradeLimit(cards->NumCards());

			PerformCardTrade(player, cards);

			SetState(State::WaitingForPlayerTrade);

			return true;
		}
		else{
			return false;
		}
	}

	bool Game::PlayerTradeCards(Player* player, ICardCollection* cards){
		if (player == GetActivePlayer()){
			Round* round = (Round*)GetCurrentRound();
			if (cards->NumCards() > round->GetTradeLimit())
				return false;

			PerformCardTrade(player, cards);

			if (m_currentPlayer == m_startingPlayer)
				NewTrick();

			return true;
		}
		else{
			return false;
		}
	}

	void Game::NextActivePlayer(){
		m_currentPlayer += 1;

		if (m_currentPlayer == m_activePlayers.size()){
			m_currentPlayer = 0;
		}
	}

	Round* Game::GetCurrentRound() const{
		if (m_rounds.size() == 0){
			return nullptr;
		}
		else{
			return m_rounds[m_rounds.size() - 1].get();
		}
	}

	Round* Game::GetRound(size_t index){
		return m_rounds[index].get();
	}
	size_t Game::GetNumRounds() const{
		return m_rounds.size();
	}

	void Game::SetState(State newState){
		if (m_gameState != newState){
			State oldState = m_gameState;
			m_gameState = newState;

			for (auto& callback : m_stateChangeCallbacks){
				callback(oldState, newState);
			}
		}
	}

	void Game::BindStateChangeCallback(StateChangeCallback callback){
		m_stateChangeCallbacks.push_back(callback);
	}
}
