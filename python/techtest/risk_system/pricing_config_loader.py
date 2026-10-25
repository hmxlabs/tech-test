from __future__ import annotations

from typing import Optional

from techtest.risk_system.pricing_engine_config import PricingEngineConfig


class PricingConfigLoader:
    def __init__(self) -> None:
        self.config_file: Optional[str] = None

    def load_config(self) -> PricingEngineConfig:
        raise NotImplementedError()
