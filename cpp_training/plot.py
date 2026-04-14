import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("simulation_log.csv")

plt.figure(figsize=(10, 6))

plt.plot(df["TargetX"], df["TargetY"], 'r--', label="Target", linewidth=2)

plt.plot(df["InterceptorX"], df["InterceptorY"], 'b-', label="Interceptor", linewidth=2)

# Punkte für den Start markieren
plt.plot(df["TargetX"].iloc[0], df["TargetY"].iloc[0], 'ro', markersize=8)
plt.plot(df["InterceptorX"].iloc[0], df["InterceptorY"].iloc[0], 'bo', markersize=8)

# Formatierung
plt.title("Luftverteidigungssimulation: Trajektorien")
plt.xlabel("X-Position [m]")
plt.ylabel("Y-Position [m]")
plt.legend()
plt.grid(True)
plt.axis("equal")

# Anzeigen
plt.show()