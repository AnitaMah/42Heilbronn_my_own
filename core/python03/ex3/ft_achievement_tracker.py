"""!
@file ft_achievement_tracker.py
@brief Generate and compare random achievement sets across players.
"""
import random
from typing import List, Set


class PlayerData:
    """!
    @brief Holds a player's name and the set of achievements they own.
    """

    def __init__(self, name: str) -> None:
        """!
        @brief Create a player with an empty achievement set.
        @param name The player's display name.
        @return None.
        """
        self.name = name
        self.achievements: Set[str] = set()


def get_all_possible_achievements() -> Set[str]:
    """!
    @brief List every achievement that can be unlocked in the game.
    @return The full set of possible achievements.
    """
    return {
        'Crafting Genius', 'World Savior', 'Master Explorer',
        'Collector Supreme', 'Untouchable', 'Boss Slayer',
        'Strategist', 'Unstoppable', 'Speed Runner', 'Survivor',
        'Treasure Hunter', 'First Steps', 'Sharp Mind',
        'Hidden Path Finder'
    }


def gen_player_achievements() -> Set[str]:
    """!
    @brief Randomly assign a set of achievements to a player.
    @return A randomly sized subset of the achievement pool.
    """
    pool = get_all_possible_achievements()
    count = random.randint(3, 9)
    return set(random.sample(list(pool), count))


def check_achievements(players: List[PlayerData]) -> None:
    """!
    @brief Print achievement stats: shared, unique and missing per player.
    @param players The list of players to analyze.
    @return None.
    """
    all_pool = get_all_possible_achievements()
    all_sets = [p.achievements for p in players]

    all_distinct = set().union(*all_sets)
    common = set.intersection(*all_sets)

    print("=== Achievement Tracker System ===")
    for p in players:
        print(f"Player {p.name}: {p.achievements}")

    print(f"All distinct achievements: {all_distinct}")
    print(f"Common achievements: {common}")

    for p in players:
        others = set().union(*(other.achievements for other in players
                               if other != p))
        print(f"Only {p.name} has: {p.achievements.difference(others)}")

    for p in players:
        print(f"{p.name} is missing: {all_pool.difference(p.achievements)}")


def main() -> None:
    """!
    @brief Generate achievements for four players and report analytics.
    @return None.
    """
    names = ["Alice", "Bob", "Charlie", "Dylan"]
    players = [PlayerData(name) for name in names]

    for player in players:
        player.achievements = gen_player_achievements()

    check_achievements(players)


if __name__ == "__main__":
    main()
