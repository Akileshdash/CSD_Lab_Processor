# 2025-09-26T18:47:51.035367
import vitis

client = vitis.create_client()
client.set_workspace(path="Processor_26_Sep_2025")

comp = client.get_component(name="CortexM0_IP")
comp.run(operation="C_SIMULATION")

comp.run(operation="C_SIMULATION")

comp.run(operation="SYNTHESIS")

vitis.dispose()

