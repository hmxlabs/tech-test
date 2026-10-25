from __future__ import annotations

class PricingConfigLoader:
    def __init__(self) -> None:
        self.config_file: str | None = None

    def load_config(self) -> object:
        raise NotImplementedError()
