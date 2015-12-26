#include "Game.hpp"

namespace Bilky{

	Game::Game(){
		m_gameState = State::Stopped;
	}

	Player* Game::CreatePlayer(const std::string& name){
		PlayerReference newPlayer;
		if (m_gameState == State::Stopped){
			newPlayer.reset(new Player(name));
			m_players.push_back(newPlayer);
		}

		return newPlayer.get();
	}

	size_t Game::GetNumPlayers() const{
		return m_players.size();
	}

	Game::State Game::GetState() const{
		return m_gameState;
	}

	Player* Game::ActivePlayer(){
		return m_players[m_activePlayer].get();
	}

	const Player* Game::GetActivePlayer(){
		return ActivePlayer();
	}

	bool Game::Start(){
		if (m_players.size() < 2){
			return false;
		}

		if (m_gameState != State::Stopped){
			return false;
		}

		Reset();

		//determine the player that will be starting
		m_startingPlayer = rand() % m_players.size();
		m_activePlayer = m_startingPlayer;

		//setup the deck for this game
		m_dealer.CreateCardPool(m_players.size());
		
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
		for (auto& player : m_players){
			player->Reset();
		}

		m_rounds.clear();
		m_dealer.Clear();

		m_activePlayer = 0;
	}

	void Game::NewRound(uint8_t handSize){
		SetState(State::DealingHands);

		m_dealer.Reset();

		Round* round = new Round(handSize);
		RoundReference ref;
		ref.reset(round);
		m_rounds.push_back(ref);

		for (uint8_t i = 0; i < handSize; i++){
			for (auto& player : m_players){
				m_dealer.DealCardToPlayer(player.get());
			}
		}

		SetState(State::WaitingForDealerTrade);
	}

	Dealer* Game::GetDealer(){
		return &m_dealer;
	}

	bool Game::TradeCards(const Player* player, ICardCollection* cards){
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

		player->Hand()->Remove(cards);

		size_t numCards = cards->NumCards();
		for (size_t i = 0; i < numCards; i++){
			m_dealer.DealCardToPlayer(player);
		}

		NextActivePlayer();
	}

	bool Game::DealerTradeCards(const Player* player, ICardCollection* cards){
		Player* activePlayer = ActivePlayer();

		if (player == activePlayer){
			Round* round = (Round*)GetCurrentRound();
			round->SetTradeLimit(cards->NumCards());

			PerformCardTrade(activePlayer, cards);

			SetState(State::WaitingForPlayerTrade);

			return true;
		}
		else{
			return false;
		}
	}

	bool Game::PlayerTradeCards(const Player* player, ICardCollection* cards){
		Player* activePlayer = ActivePlayer();

		if (player == GetActivePlayer()){
			Round* round = (Round*)GetCurrentRound();
			if (cards->NumCards() > round->GetTradeLimit())
				return false;

			PerformCardTrade(activePlayer, cards);

			if (m_activePlayer == m_startingPlayer)
				SetState(State::WaitingForActivePlayer);

			return true;
		}
		else{
			return false;
		}
	}

	void Game::NextActivePlayer(){
		m_activePlayer += 1;

		if (m_activePlayer == m_players.size()){
			m_activePlayer = 0;
		}
	}

	const Round* Game::GetCurrentRound(){
		if (m_rounds.size() == 0){
			return nullptr;
		}
		else{
			return m_rounds[m_rounds.size() - 1].get();
		}
	}

	const Round* Game::GetRound(size_t index){
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
