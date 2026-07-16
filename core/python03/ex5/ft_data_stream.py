import random
from typing import Generator


class GameData:
    def __init__(self) -> None:
        self.players = ["bob", "alice", "dylan", "charlie"]
        self.actions = [
            "run",
            "eat",
            "sleep",
            "grab",
            "move",
            "climb",
            "swim",
            "use",
            "release"]

    def get_game_parameters(self) -> tuple[list[str], list[str]]:
        return self.players, self.actions


data_source = GameData()


def generate_rools() -> Generator[tuple[str, str], None, None]:
    players, actions = data_source.get_game_parameters()
    while True:
        yield (random.choice(players), random.choice(actions))


def creat_items(generator: Generator[tuple[str, str],
                None, None], count: int) -> list[tuple[str, str]]:
    return [next(generator) for _ in range(count)]


def get_event(event_list: list[tuple[str, str]]
              ) -> Generator[tuple[str, str], None, None]:
    while len(event_list) > 0:
        index = random.randint(0, len(event_list) - 1)
        yield event_list.pop(index)


def main() -> None:
    print("=== Game Data Stream Processor ===")
    event_gen = generate_rools()

    for i in range(1000):
        event = next(event_gen)
        print(f"Event {i}: Player {event[0]} did action {event[1]}")

    items = creat_items(event_gen, 10)
    print(f"Built list of 10 events: {items}")

    for event in get_event(items):
        print(f"Got event from list: {event}")
        print(f"Remains in list: {items}")


if __name__ == "__main__":
    main()
