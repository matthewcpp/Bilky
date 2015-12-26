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
		size_t GetNumPlayers() const;

		virtual State GetState() const;

		Dealer* GetDealer();

		const Round* GetCurrentRound();
		const Round* GetRound(size_t index);
		size_t GetNumRounds() const;

		const Player* GetActivePlayer();

		bool TradeCards(const Player* player, ICardCollection* cards);

		void BindStateChangeCallback(StateChangeCallback callback);

	private:
		void NewRound(uint8_t handSize);
		void Reset();
		void SetupPlayOrder();

		bool DealerTradeCards(const Player* player, ICardCollection* cards);
		bool PlayerTradeCards(const Player* player, ICardCollection* cards);
		void PerformCardTrade(Player* player, ICardCollection* cards);

		Player* ActivePlayer();
		void NextActivePlayer();

		virtual void SetState(State newState);
		void OnCardDelt(Player* player, Card* card);

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