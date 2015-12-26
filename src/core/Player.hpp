#ifndef BILKY_PLAYER_HPP
#define BILKY_PLAYER_HPP

#include <cstdint>
#include <string>

#include "CardCollection.hpp"

namespace Bilky{
	class Player{
	public:
		Player(const std::string& name);

	public:
		void Reset();
		uint8_t GetScore();
		std::string GetName() const;

		const ICardCollection* GetHand() const;
		ICardCollection* Hand();

	private:
		uint8_t m_score;
		std::string m_name;
		CardCollection m_hand;	
	};
}

#endif