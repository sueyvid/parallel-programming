import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# ====== parâmetros ======
csv_file = "output.csv"   # arquivo gerado pelo C
Nx, Ny, Nz = 50, 50, 50  # mesma grade usada no C
plot_interval = 10       # desenhar a cada N steps

# ====== leitura do CSV ======
print("Lendo CSV...")
df = pd.read_csv(csv_file)

# Identifica quantos steps existem
steps = df["step"].max() + 1
print(f"Arquivo contém {steps} steps")

# ====== preparação do gráfico ======
plt.ion()
fig = plt.figure(figsize=(6,5))
ax = fig.add_subplot(111, projection="3d")

# Loop sobre os steps
for step in range(0, steps, plot_interval):
    print(f"Plotando step {step}...")

    # Seleciona dados desse step
    df_step = df[df["step"] == step]

    # Converte para array 3D
    w = np.zeros((Nz, Ny, Nx))
    for _, row in df_step.iterrows():
        k, j, i = int(row.k), int(row.j), int(row.i)
        if 0 <= k < Nz and 0 <= j < Ny and 0 <= i < Nx:
            w[k, j, i] = row.value

    # pega fatia central no eixo Z
    slice2d = w[Nz//2,:,:]

    # cria grid para plotagem
    X, Y = np.meshgrid(np.linspace(0,1,Nx), np.linspace(0,1,Ny))

    # atualiza gráfico
    ax.clear()
    ax.set_title(f"Step {step}")
    surf = ax.plot_surface(X, Y, slice2d, cmap="viridis")

    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_zlabel("Intensidade")

    plt.pause(10)

plt.ioff()
plt.show()
