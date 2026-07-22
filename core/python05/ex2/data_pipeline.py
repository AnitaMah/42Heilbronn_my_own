from typing import Protocol, runtime_checkable, List, Tuple, Any, Dict


@runtime_checkable
class ExportPlugin(Protocol):
    def process_output(self, data: List[Tuple[int, str]]) -> None:
        pass


class CSVPlugin:
    def process_output(self, data: List[Tuple[int, str]]) -> None:
        csv_data = [f"{value}" for _, value in data]
        print("CSV Output:\n" + ", ".join(csv_data))


class JSONPlugin:
    def process_output(self, data: List[Tuple[int, str]]) -> None:
        json_data = {f"item_{rank}": value for rank, value in data}
        print("JSON Output:\n" + str(json_data))


class DataStream:
    def __init__(self) -> None:
        self._processors: List[Any] = []        
    
    def register_processor(self, processor: Any) -> None:
        self._processors.append(processor)

    def output_pipeline(self, nb: int, plugin: ExportPlugin) -> None:

        for proc in self._processors:
            batch = []
            for _ in range(nb):
                try:
                    batch.append(proc.output())
                except IndexError:
                    break
            if batch:
                plugin.process_output(batch)

    def print_statistics(self) -> None:
        """Print statistics for all processors."""
        print("== DataStream statistics ==")
        for proc in self._processors:
            print(f"{proc.__class__.__name__}: "
                  f"total {proc.total_processed} items processed, "
                  f"remaining {proc.remaining} on processor")


class NumericProcessor:
    def __init__(self, data: List[Any]) -> None:
        self.data = data
        self.index = 0
        self.total_processed = 0
        self.remaining = len(data)

    def output(self) -> Tuple[int, str]:
        if self.index < len(self.data):
            value = self.data[self.index]
            self.index += 1
            self.total_processed += 1
            self.remaining -= 1
            return (self.index, str(value))
        raise IndexError("No more data")


class TextProcessor:
    def __init__(self, data: List[Any]) -> None:
        self.data = data
        self.index = 0
        self.total_processed = 0
        self.remaining = len(data)

    def output(self) -> Tuple[int, str]:
        if self.index < len(self.data):
            value = self.data[self.index]
            self.index += 1
            self.total_processed += 1
            self.remaining -= 1
            return (self.index, str(value))
        raise IndexError("No more data")


class LogProcessor:
    def __init__(self, data: List[Dict[str, str]]) -> None:
        self.data = data
        self.index = 0
        self.total_processed = 0
        self.remaining = len(data)

    def output(self) -> Tuple[int, str]:
        if self.index < len(self.data):
            log_entry = self.data[self.index]
            level = log_entry['log_level']
            message = log_entry['log_message']
            formatted_log = f"{level}: {message}"

            self.index += 1
            self.total_processed += 1
            self.remaining -= 1
            return (self.index, formatted_log)
        raise IndexError("No more data")


def main() -> None:
    numeric_data = [3.14, -1, 2.71, 42, 21, 32, 42, 64, 84, 128, 168]
    text_data = [
        "Hello world",
        "Hi",
        "five",
        "I love AI",
        "LLMs are wonderful",
        "Stay healthy",
        "World hello"
    ]
    log_data = [
        {
            "log_level": "WARNING",
            "log_message": "Telnet access! Use ssh instead"
        },
        {
            "log_level": "INFO",
            "log_message": "User wil is connected"
        },
        {
            "log_level": "ERROR",
            "log_message": "500 server crash"
        },
        {
            "log_level": "NOTICE",
            "log_message": "Certificate expires in 10 days"
        }
    ]

    print("=== Code Nexus - Data Pipeline ===\n")
    print("Initialize Data Stream...\n")

    stream = DataStream()
    print("== DataStream statistics ==")
    if not stream._processors:
        print("No processor found, no data")

    print("\nRegistering Processors")
    stream.register_processor(NumericProcessor(numeric_data))
    stream.register_processor(TextProcessor(text_data))
    stream.register_processor(LogProcessor(log_data))

    batch_1 = (
        numeric_data[:3]
        + text_data[:3]
        + [log_data[0], log_data[1]]
        + numeric_data[3:4]
        + text_data[3:4]
    )
    print(f"\nSend first batch of data on stream: {batch_1}\n")
    stream.print_statistics()

    print("\nSend 3 processed data from each processor to a CSV plugin:")
    stream.output_pipeline(3, CSVPlugin())
    print()
    stream.print_statistics()

    batch_2 = (
        [21]
        + text_data[4:7]
        + [log_data[2], log_data[3]]
        + numeric_data[4:10]
        + text_data[6:7]
    )
    print(f"\nSend another batch of data: {batch_2}\n")
    stream.print_statistics()

    print("\nSend 5 processed data from each processor to a JSON plugin:")
    stream.output_pipeline(5, JSONPlugin())
    print()
    stream.print_statistics()


if __name__ == "__main__":
    main()
