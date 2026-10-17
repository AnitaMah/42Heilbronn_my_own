from abc import ABC, abstractmethod
from typing import Any, Protocol, runtime_checkable


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


@runtime_checkable
class ExportPlugin(Protocol):
    def process_output(self, data: list[tuple[int, str]]) -> None:
        pass


class CSVPlugin:
    def process_output(self, data: list[tuple[int, str]]) -> None:
        csv_data = [value for _, value in data]
        print("CSV Output:\n" + ",".join(csv_data))


class JSONPlugin:
    def process_output(self, data: list[tuple[int, str]]) -> None:
        pairs: list[str] = []
        for rank, value in data:
            escaped = value.replace("\\", "\\\\").replace('"', '\\"')
            pairs.append(f'"item_{rank}": "{escaped}"')
        print("JSON Output:\n{" + ", ".join(pairs) + "}")


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

    def output_pipeline(self, nb: int, plugin: ExportPlugin) -> None:
        """Consume nb elements from each processor and export them."""
        for proc in self._processors:
            batch: list[tuple[int, str]] = []
            for _ in range(nb):
                try:
                    batch.append(proc.output())
                except IndexError:
                    break
            if batch:
                plugin.process_output(batch)

    def print_processors_stats(self) -> None:
        """Print statistics for all processors."""
        print("== DataStream statistics ==")
        if not self._processors:
            print("No processor found, no data")
            return
        for proc in self._processors:
            name = proc.__class__.__name__.replace("Processor", " Processor")
            print(f"{name}: "
                  f"total {proc._total_processed} items processed, "
                  f"remaining {len(proc._data)} on processor")


def main() -> None:
    print("=== Code Nexus - Data Pipeline ===\n")
    print("Initialize Data Stream...\n")

    stream = DataStream()
    stream.print_processors_stats()

    print("\nRegistering Processors")
    stream.register_processor(NumericProcessor())
    stream.register_processor(TextProcessor())
    stream.register_processor(LogProcessor())

    batch_1: list[Any] = [
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
    print(f"\nSend first batch of data on stream: {batch_1}\n")
    stream.process_stream(batch_1)
    stream.print_processors_stats()

    print("\nSend 3 processed data from each processor to a CSV plugin:")
    stream.output_pipeline(3, CSVPlugin())
    print()
    stream.print_processors_stats()

    batch_2: list[Any] = [
        21,
        ["I love AI", "LLMs are wonderful", "Stay healthy"],
        [
            {"log_level": "ERROR", "log_message": "500 server crash"},
            {"log_level": "NOTICE",
             "log_message": "Certificate expires in 10 days"},
        ],
        [32, 42, 64, 84, 128, 168],
        "World hello",
    ]
    print(f"\nSend another batch of data: {batch_2}\n")
    stream.process_stream(batch_2)
    stream.print_processors_stats()

    print("\nSend 5 processed data from each processor to a JSON plugin:")
    stream.output_pipeline(5, JSONPlugin())
    print()
    stream.print_processors_stats()


if __name__ == "__main__":
    main()
