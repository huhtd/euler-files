import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import csv


data = pd.read_csv('results/all.txt', delimiter=',')

pivot = data.pivot(index=['n', 'p', 't'], columns='key', values='value')
print(pivot)

strongscaling = pivot.groupby(['n', 'p']).median()
print(strongscaling)

# HACK: copies the time P=1, N=x into all P, N=x
# TODO: Find a more elegant solution
strongscaling['n0'] = 0
for i in strongscaling.index.get_level_values(0):
    strongscaling['n0'].loc[i] = strongscaling['time'].loc[i, 1]
strongscaling['speedup'] = strongscaling['n0'] / strongscaling['time']
print(strongscaling)

strongscaling['time'].unstack(level=0).plot(
    kind='line',
    title='Time',
    ylabel="time in sec",
    xlabel="#processors",
    legend=True,
    logy=True
)
plt.savefig("time.pdf")

strongscaling['speedup'].unstack(level=0).plot(
    kind='line',
    title='Speedup',
    ylabel="Speed-up",
    xlabel="#processors",
    legend=True
)
plt.savefig("speedup.pdf")

weakscaling = pivot.groupby(['n', 'p']).median()

