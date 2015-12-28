#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Bilky.hpp"

void CardDelt(Bilky::Player* player, Bilky::Card* card);
void StateChange(Bilky::Game::State oldState, Bilky::Game::State newState);
void Trade(Bilky::Game& game, const Bilky::Player*, size_t numCards);


int main(int argc, char** argv){
	srand(time(NULL));

	Bilky::Game game;
	
	game.CreatePlayer("Matthew");
	game.CreatePlayer("Tony");

	game.BindStateChangeCallback(&StateChange);
	game.GetDealer()->BindCardDealCallback(&CardDelt);

	if (!game.Start()){
		std::cout << "could not start game" << std::endl;
	}

	Trade(game, game.GetActivePlayer(), 2);
	Trade(game, game.GetActivePlayer(), 2);

	return 0;
}

void CardDelt(Bilky::Player* player, Bilky::Card* card){
	char suit;

	switch (card->GetSuit())
	{
	case Bilky::Card::Suit::Clubs:
		suit = 'C';
		break;

	case Bilky::Card::Suit::Diamonds:
		suit = 'D';
		break;

	case Bilky::Card::Suit::Spades:
		suit = 'S';
		break;

	case Bilky::Card::Suit::Hearts:
		suit = 'H';
		break;
	}

	std::cout << "Delt " << (int)card->GetValue() << suit << " to:" << player->GetName() <<std::endl;
}

std::string GetStateName(Bilky::Game::State state){
	switch (state){
	case Bilky::Game::State::DealingHands:
		return "Dealing Hands";

	case Bilky::Game::State::WaitingForActivePlayer:
		return "Waiting for Active Player";

	case Bilky::Game::State::WaitingForDealerTrade:
		return "Waiting for Dealer Trade";

	case Bilky::Game::State::WaitingForPlayerTrade:
		return "Waiting for Player Trade";

	default:
		return "Stopped";
	}
}

void StateChange(Bilky::Game::State oldState, Bilky::Game::State newState){
	std::cout << "Game State Change: " << GetStateName(oldState) << "  -->  " << GetStateName(newState) << std::endl;
}

void Trade(Bilky::Game& game, const Bilky::Player* player, size_t numCards){
	Bilky::CardCollection trade;

	for (size_t i = 0; i < numCards; i++){
		trade.AddCard(player->GetHand()->GetCard(0));
		trade.AddCard(player->GetHand()->GetCard(1));
		game.TradeCards(player, &trade);
	}
}
