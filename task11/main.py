import numpy as np
import matplotlib.pyplot as plt

# Parâmetros
Nx, Ny = 100, 100   # tamanho da grade
steps = 200         # número de passos no tempo
nu = 0.01           # viscosidade
dt = 0.0005         # passo no tempo
h = 1.0 / Nx        # espaçamento

# Inicialização: fluido parado (todos zeros)
w = np.zeros((Ny, Nx))

# ---- Caso 1: campo constante ou parado ----
# Se quiser testar campo constante, descomente:
# w[:] = 0.5

# ---- Caso 2: perturbação no centro ----
w[Ny//2, Nx//2] = 1.0

plt.ion()
fig, ax = plt.subplots()

# cria a imagem e a colorbar só uma vez
im = ax.imshow(w, cmap="viridis", origin="lower", extent=[0,1,0,1])
cbar = plt.colorbar(im, ax=ax)
ax.set_title("Step 0")

for n in range(steps):
    w_new = np.copy(w)

    # Diferenças finitas (laplaciano com condições periódicas)
    for j in range(Ny):
        for i in range(Nx):
            ip, im_ = (i+1)%Nx, (i-1+Nx)%Nx
            jp, jm = (j+1)%Ny, (j-1+Ny)%Ny

            lap = (w[j,ip] + w[j,im_] + w[jp,i] + w[jm,i] - 4*w[j,i]) / (h*h)
            w_new[j,i] = w[j,i] + dt * nu * lap

    w = w_new

    if n % 10 == 0:
        im.set_data(w)        # atualiza a imagem
        ax.set_title(f"Step {n}")
        plt.pause(0.1)

plt.ioff()
plt.show()
