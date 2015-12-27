#ifndef BILKY_TRICK_HPP
#define BILKY_TRICK_HPP

#include <map>

#include "Player.hpp"
#include "Card.hpp"

namespace Bilky{
	class Trick{
	public:
		Trick();

	public:
		const Player* GetLeadPlayer() const;
		const Card* GetLeadCard() const;

		const Player* GetWinningPlayer() const ;
		const Card* GetWinningCard() const;

		size_t GetNumPlays() const;

		void CardPlay(Player* player, Card* card);
		const Card* GetCardForPlayer(Player* player) const;

		bool IsComplete() const;
		void SetComplete(bool complete = true);

	private:
		typedef std::map<Player*, Card*> PlayerCardMap;

	private:
		PlayerCardMap m_plays;
		
		Player* m_leadPlayer;
		Player* m_winningPlayer;

		Card* m_leadCard;
		Card* m_winningCard;

		bool m_isComplete;
	};
}

#endif