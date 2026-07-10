import random

class PlayerData:
    def __init__(self, name):
        self.name = name
        self.achievements = set()

def get_all_possible_achievements():
    return {
        'Crafting Genius', 'World Savior', 'Master Explorer', 'Collector Supreme',
        'Untouchable', 'Boss Slayer', 'Strategist', 'Unstoppable', 'Speed Runner',
        'Survivor', 'Treasure Hunter', 'First Steps', 'Sharp Mind', 'Hidden Path Finder'
    }

def add_atributs(player):
    pool = get_all_possible_achievements()
    count = random.randint(3, 9)
    player.achievements = set(random.sample(list(pool), count))

def check_atributs(players):
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
        others = set().union(*(other.achievements for other in players if other != p))
        print(f"Only {p.name} has: {p.achievements.difference(others)}")

    for p in players:
        print(f"{p.name} is missing: {all_pool.difference(p.achievements)}")

def gen_player_achievements():
    names = ["Alice", "Bob", "Charlie", "Dylan"]
    players = [PlayerData(name) for name in names]

    for player in players:
        add_atributs(player)

    check_atributs(players)

def main():
    gen_player_achievements()

if __name__ == "__main__":
    gen_player_achievements()
