from abc import ABC, abstractmethod
from typing import Any


class DataProcessor(ABC):
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
        pass


class NumericProcessor(DataProcessor):
    def __init__(self):
        self._data = []
        self._rank = 0

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
        else:
            self._data.append(str(data))

    def output(self) -> tuple[int, str]:
        """Extract the oldest stored numeric data and its rank."""
        if not self._data:
            raise IndexError("No data to output")
        item = self._data.pop(0)
        rank = self._rank
        self._rank += 1
        return (rank, item)


class TextProcessor(DataProcessor):
    def __init__(self):
        self._data = []
        self._rank = 0

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
        else:
            self._data.append(data)

    def output(self) -> tuple[int, str]:
        """Extract the oldest stored text data and its rank."""
        if not self._data:
            raise IndexError("No data to output")
        item = self._data.pop(0)
        rank = self._rank
        self._rank += 1
        return (rank, item)


class LogProcessor(DataProcessor):
    def __init__(self):
        self._data = []
        self._rank = 0

    def validate(self, data: Any) -> bool:
        """Check if the data is a dict with string keys/values or a list of """
        """such dicts."""
        if isinstance(data, dict):
            return all(isinstance(k, str) and isinstance(v, str)
                       for k, v in data.items())
        if isinstance(data, list):
            return all(self.validate(item) for item in data)
        return False

    def ingest(self, data: dict[str, str] | list[dict[str, str]]) -> None:
        """Process and store log data."""
        if not self.validate(data):
            raise ValueError("Improper log data")
        if isinstance(data, list):
            for item in data:
                log_str = f"{item['log_level']}: {item['log_message']}"
                self._data.append(log_str)
        else:
            log_str = f"{data['log_level']}: {data['log_message']}"
            self._data.append(log_str)

    def output(self) -> tuple[int, str]:
        """Extract the oldest stored log data and its rank."""
        if not self._data:
            raise IndexError("No data to output")
        item = self._data.pop(0)
        rank = self._rank
        self._rank += 1
        return (rank, item)
