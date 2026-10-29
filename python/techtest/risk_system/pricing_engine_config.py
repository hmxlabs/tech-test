from __future__ import annotations

from techtest.risk_system.pricing_engine_config_item import PricingEngineConfigItem


class PricingEngineConfig(list[PricingEngineConfigItem]):
    """A list of PricingEngineConfigItem."""
