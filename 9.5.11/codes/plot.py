import numpy as np
import matplotlib.pyplot as plt
from numpy import linalg as LA

import sys  # for path to external scripts
sys.path.insert(0, '/home/manvik/matgeo/codes/CoordGeo')  # Adjust the path as needed

# Local imports
from line.funcs import *
from triangle.funcs import *
from conics.funcs import *

# If using termux
import subprocess
import shlex

# Setting up plot
fig, ax = plt.subplots()

# Parabola 1: x^2 = 4y (Standard)
y1 = np.linspace(-5, 5, 100)
x1 = np.sqrt(4 * y1)

# Plot both branches of parabola 1 (x^2 = 4y)
plt.plot(x1, y1, label='$x^2 = 4y$', color='r')
plt.plot(-x1, y1, color='r')  # Negative branch

# Parabola 2: y^2 = 4x (Standard)
x2 = np.linspace(0, 5, 100)
y2 = np.sqrt(4 * x2)

# Plot both branches of parabola 2 (y^2 = 4x)
plt.plot(x2, y2, label='$y^2 = 4x$', color='b')
plt.plot(x2, -y2, color='b')  # Negative branch

# Plotting the four lines: x=0, x=4, y=0, y=4
plt.axvline(x=0, color='g', linestyle='--', label='x=0')
plt.axvline(x=4, color='g', linestyle='--', label='x=4')
plt.axhline(y=0, color='m', linestyle='--', label='y=0')
plt.axhline(y=4, color='m', linestyle='--', label='y=4')

# Customizing the plot
ax.spines['top'].set_color('none')
ax.spines['right'].set_color('none')
ax.spines['left'].set_position('zero')
ax.spines['bottom'].set_position('zero')

# Labels and grid
plt.xlabel('x')
plt.ylabel('y')
plt.legend(loc='best')
plt.grid(True)  # Enable grid
plt.axis('equal')  # Equal scaling for x and y axes

plt.savefig('/home/manvik/Documents/EE1030/9.5.11/figs/plot.png')


