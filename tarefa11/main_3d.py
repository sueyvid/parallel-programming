import os
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# ====== parâmetros ======
csv_file = "output.csv"     # arquivo gerado pelo C
Nx, Ny, Nz = 100, 100, 100  # mesma grade usada no C
plot_interval = 100         # desenhar a cada N steps
output_dir = "frames"       # pasta para salvar imagens

# ====== preparar diretório ======
os.makedirs(output_dir, exist_ok=True)

# ====== leitura do CSV ======
print("Lendo CSV...")
df = pd.read_csv(csv_file)

# Identifica quantos steps existem
steps = df["step"].max() + 1
print(f"Arquivo contém {steps} steps")

# ====== loop sobre os steps ======
for step in range(0, steps, plot_interval):
    print(f"Gerando gráfico do step {step}...")

    # Seleciona dados desse step
    df_step = df[df["step"] == step]

    # Converte para array 3D
    w = np.zeros((Nz, Ny, Nx))
    for _, row in df_step.iterrows():
        k, j, i = int(row.k), int(row.j), int(row.i)
        if 0 <= k < Nz and 0 <= j < Ny and 0 <= i < Nx:
            w[k, j, i] = row.value

    # pega fatia central no eixo Z
    slice2d = w[Nz//2, :, :]

    # cria grid para plotagem
    X, Y = np.meshgrid(np.linspace(0, 1, Nx), np.linspace(0, 1, Ny))

    # cria figura
    fig = plt.figure(figsize=(6, 5))
    ax = fig.add_subplot(111, projection="3d")
    ax.set_title(f"Step {step}")
    surf = ax.plot_surface(X, Y, slice2d, cmap="viridis")

    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_zlabel("Intensidade")

    # salva a figura
    filename = os.path.join(output_dir, f"step_{step:05d}.png")
    plt.savefig(filename)
    plt.close(fig)  # fecha a figura para liberar memória

print(f"Todas as imagens foram salvas na pasta '{output_dir}'")
