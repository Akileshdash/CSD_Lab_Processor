# 2025-09-26T13:55:32.468775
import vitis

client = vitis.create_client()
client.set_workspace(path="Processor_26_Sep_2025")

comp = client.create_hls_component(name = "CortexM0_IP",cfg_file = ["hls_config.cfg"],template = "empty_hls_component")

comp = client.get_component(name="CortexM0_IP")
comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

vitis.dispose()

