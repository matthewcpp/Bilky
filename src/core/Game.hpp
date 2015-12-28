#ifndef BILKY_GAME_HPP
#define BILKY_GAME_HPP

#include <memory>
#include <vector>
#include <string>
#include <functional>

#include "Player.hpp"
#include "Dealer.hpp"
#include "Round.hpp"

namespace Bilky {

	class Game{
	public:
		enum class State{
			Stopped,
			DealingHands,
			WaitingForDealerTrade,
			WaitingForPlayerTrade,
			WaitingForActivePlayer
		};

		typedef std::function<void(State, State)> StateChangeCallback;

	public:
		Game();

	public:
		bool Start();
		bool Stop();

		Player* CreatePlayer(const std::string& name);
		Player* GetPlayer(size_t index) const;
		size_t GetNumPlayers() const;

		virtual State GetState() const;

		Dealer* GetDealer();

		Round* GetCurrentRound() const;
		Round* GetRound(size_t index);
		size_t GetNumRounds() const;

		Player* GetActivePlayer();

		bool TradeCards(Player* player, ICardCollection* cards);
		bool PlayCard(Player* player, Card* card);
		bool PlayIsValid(Player* player, Card* card) const;

		void BindStateChangeCallback(StateChangeCallback callback);

	private:
		void NewRound(uint32_t handSize);
		void RoundEnd();

		void NewTrick();
		void TrickEnd();

		void Reset();

		bool DealerTradeCards(Player* player, ICardCollection* cards);
		bool PlayerTradeCards(Player* player, ICardCollection* cards);
		void PerformCardTrade(Player* player, ICardCollection* cards);

		void NextActivePlayer();

		virtual void SetState(State newState);

	private:
		typedef std::shared_ptr<Player> PlayerReference;
		typedef std::vector<PlayerReference> PlayerVector;

		typedef std::shared_ptr<Round> RoundReference;
		typedef std::vector<RoundReference> RoundVector;

		typedef std::vector<StateChangeCallback> StateChangeCallbackVector;

	private:
		Dealer m_dealer;

		PlayerVector m_players;
		RoundVector m_rounds;

		size_t m_startingPlayer;
		size_t m_activePlayer;

		State m_gameState;
		StateChangeCallbackVector m_stateChangeCallbacks;
	};


}

#endif