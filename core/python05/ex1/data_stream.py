from abc import ABC, abstractmethod
from typing import Any


class DataProcessor(ABC):
    def __init__(self) -> None:
        self._data: list[str] = []
        self._rank: int = 0
        self._total_processed: int = 0

    @abstractmethod
    def validate(self, data: Any) -> bool:
        """Check if the data can be processed by this processor."""
        pass

    @abstractmethod
    def ingest(self, data: Any) -> None:
        """Process and store the data internally."""
        pass

    def output(self) -> tuple[int, str]:
        """Extract the oldest stored data and its rank."""
        if not self._data:
            raise IndexError("No data to output")
        item = self._data.pop(0)
        rank = self._rank
        self._rank += 1
        return (rank, item)


class NumericProcessor(DataProcessor):
    def validate(self, data: Any) -> bool:
        """Check if the data is numeric (int, float, or list of these)."""
        if isinstance(data, (int, float)):
            return True
        if isinstance(data, list):
            return all(isinstance(item, (int, float)) for item in data)
        return False

    def ingest(self, data: int | float | list[int | float]) -> None:
        """Process and store numeric data."""
        if not self.validate(data):
            raise ValueError("Improper numeric data")
        if isinstance(data, list):
            self._data.extend(map(str, data))
            self._total_processed += len(data)
        else:
            self._data.append(str(data))
            self._total_processed += 1


class TextProcessor(DataProcessor):
    def validate(self, data: Any) -> bool:
        """Check if the data is a string or list of strings."""
        if isinstance(data, str):
            return True
        if isinstance(data, list):
            return all(isinstance(item, str) for item in data)
        return False

    def ingest(self, data: str | list[str]) -> None:
        """Process and store text data."""
        if not self.validate(data):
            raise ValueError("Improper text data")
        if isinstance(data, list):
            self._data.extend(data)
            self._total_processed += len(data)
        else:
            self._data.append(data)
            self._total_processed += 1


class LogProcessor(DataProcessor):
    def validate(self, data: Any) -> bool:
        """Check if the data is a log dict or a list of log dicts."""
        if isinstance(data, list):
            return all(self._is_log(item) for item in data)
        return self._is_log(data)

    def _is_log(self, data: Any) -> bool:
        """Check for a str k/v dict with log_level and log_message keys."""
        return (
            isinstance(data, dict)
            and "log_level" in data
            and "log_message" in data
            and all(
                isinstance(k, str) and isinstance(v, str)
                for k, v in data.items()
            )
        )

    def ingest(self, data: dict[str, str] | list[dict[str, str]]) -> None:
        """Process and store log data."""
        if not self.validate(data):
            raise ValueError("Improper log data")
        if isinstance(data, list):
            for item in data:
                log_str = f"{item['log_level']}: {item['log_message']}"
                self._data.append(log_str)
            self._total_processed += len(data)
        else:
            log_str = f"{data['log_level']}: {data['log_message']}"
            self._data.append(log_str)
            self._total_processed += 1


class DataStream:
    def __init__(self) -> None:
        self._processors: list[DataProcessor] = []

    def register_processor(self, proc: DataProcessor) -> None:
        """Register a new data processor."""
        self._processors.append(proc)

    def process_stream(self, stream: list[Any]) -> None:
        """Route each element in the stream to the appropriate processor."""
        for data in stream:
            processed = False
            for proc in self._processors:
                if proc.validate(data):
                    try:
                        proc.ingest(data)
                        processed = True
                    except (ValueError, KeyError):
                        pass
                    break
            if not processed:
                print(f"DataStream error - "
                      f"Can't process element in stream: {data}")

    def print_processors_stats(self) -> None:
        """Print statistics for all registered processors."""
        if not self._processors:
            print("No processor found, no data")
            return
        for proc in self._processors:
            processor_name = proc.__class__.__name__.replace(
                "Processor", " Processor")
            total_processed = getattr(proc, "_total_processed", 0)
            remaining = len(getattr(proc, "_data", []))
            print(
                f"{processor_name}: total {total_processed} items processed, "
                f"remaining {remaining} on processor"
            )


def main() -> None:
    print("=== Code Nexus - Data Stream ===")
    print()

    print("Initialize Data Stream...")
    stream = DataStream()
    print("== DataStream statistics ==")
    stream.print_processors_stats()
    print()

    print("Registering Numeric Processor")
    numeric_proc = NumericProcessor()
    stream.register_processor(numeric_proc)

    batch: list[Any] = [
        "Hello world",
        [3.14, -1, 2.71],
        [
            {"log_level": "WARNING",
             "log_message": "Telnet access! Use ssh instead"},
            {"log_level": "INFO", "log_message": "User wil is connected"},
        ],
        42,
        ["Hi", "five"],
    ]
    print(f"\nSend first batch of data on stream: {batch}")
    stream.process_stream(batch)
    print("== DataStream statistics ==")
    stream.print_processors_stats()

    print("\nRegistering other data processors")
    text_proc = TextProcessor()
    log_proc = LogProcessor()
    stream.register_processor(text_proc)
    stream.register_processor(log_proc)
    print("Send the same batch again")
    stream.process_stream(batch)
    print("== DataStream statistics ==")
    stream.print_processors_stats()

    print("\nConsume some elements from the data processors: "
          "Numeric 3, Text 2, Log 1")
    for _ in range(3):
        numeric_proc.output()
    for _ in range(2):
        text_proc.output()
    for _ in range(1):
        log_proc.output()
    print("== DataStream statistics ==")
    stream.print_processors_stats()


if __name__ == "__main__":
    main()
