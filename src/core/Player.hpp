#ifndef BILKY_PLAYER_HPP
#define BILKY_PLAYER_HPP

#include <cstdint>
#include <string>

#include "CardCollection.hpp"

namespace Bilky{
	class Player{
	public:
		Player(const std::string& name, uint32_t id);

	public:
		void Reset();
		uint32_t GetScore();
		std::string GetName() const;

		uint32_t GetId() const;
		void Setid(uint32_t id);

		const ICardCollection* GetHand() const;
		ICardCollection* Hand();

	private:
		uint32_t m_score;
		uint32_t m_id;
		std::string m_name;
		CardCollection m_hand;	
	};
}

#endif