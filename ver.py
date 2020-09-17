import pandas as pd 
import numpy as np
import matplotlib.pyplot as plt

df=pd.read_csv('datos.dat')
df.plot(x='x0',y='y0')
plt.show()
