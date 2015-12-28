#include "Roster.hpp"

namespace Bilky {
	Player* Roster::CreatePlayer(const std::string& name) {
		PlayerReference newPlayer;

		newPlayer.reset(new Player(name, m_players.size()));
		m_players.push_back(newPlayer);

		return newPlayer.get();
	}

	Player* Roster::GetPlayer(size_t index) const {
		return m_players[index].get();
	}

	size_t Roster::GetNumPlayers() const {
		return m_players.size();
	}

	void Roster::Reset() {
		for (auto& player : m_players) {
			player->Reset();
		}
	}

	void Roster::GetActivePlayers(PlayerVector& players) {
		players.clear();

		for (auto& player : m_players) {
			if (player->IsActive())
				players.push_back(player.get());
		}
	}
}