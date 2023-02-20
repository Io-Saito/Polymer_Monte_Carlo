# %%
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np

# %%
df = pd.read_csv("/Users/io/Project/Polymer_Monte_Carlo/Step2/finish.csv")
df_chains = [df.groupby("chain").get_group(x) for x in df['chain'].unique()]
timestep = df["timestep"].unique()

# %%
arr = np.arange(0, 510, 10)

# %%
arr

# %%
fig = plt.figure(figsize=(16, 16))
cordinate = fig.add_subplot(111, projection='3d')


def run(i):
    plt.rcParams['font.family'] = 'sans-serif'
    plt.rcParams['xtick.direction'] = 'in'
    plt.rcParams['ytick.direction'] = 'in'
    plt.rcParams['xtick.major.width'] = 1.0
    plt.rcParams['ytick.major.width'] = 1.0
    plt.rcParams['font.size'] = 25
    plt.rcParams['axes.linewidth'] = 1.0

    for y in df_chains:
        chain = y[y["timestep"] == i]
        cordinate.plot(chain["x"], chain["y"],
                       chain["z"], marker='o', linestyle='solid')
    cordinate.set_xlim(195, 205)
    cordinate.set_ylim(195, 205)
    cordinate.set_zlim(195, 205)
    cordinate.set_xlabel('X ')
    cordinate.set_ylabel('Y ')
    cordinate.set_zlabel('Z ')
    cordinate.set_title('Visualization')


ani = FuncAnimation(
    fig, run, frames=arr, interval=10, repeat=False)
ani.save(f"test.gif")


# %%