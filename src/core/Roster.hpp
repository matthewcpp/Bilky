#ifndef BILKY_ROSTER_HPP
#define BILKY_ROSTER_HPP

#include <memory>
#include <vector>

#include "Player.hpp"

namespace Bilky {
	typedef std::vector<Player*> PlayerVector;

	class Roster {
	public:
		Player* CreatePlayer(const std::string& name);
		Player* GetPlayer(size_t index) const;
		size_t GetNumPlayers() const;

		void GetActivePlayers(PlayerVector& players);

		void Reset();

	private:
		typedef std::shared_ptr<Player> PlayerReference;
		typedef std::vector<PlayerReference> PlayerReferenceVector;
	private:

		PlayerReferenceVector m_players;
	};
}

#endif