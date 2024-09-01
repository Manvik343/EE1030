import ctypes
import matplotlib.pyplot as plt

# Load the shared library
ratio_lib = ctypes.CDLL('./ratio.so')

# Define argument and return types for the C function
ratio_lib.calculateRatio.argtypes = (ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_int))

# Coordinates of the points
points = [(-6, 10), (-4, 6), (3, -8)]

# Extract coordinates for points A, B, C
x1, y1 = points[0]
x2, y2 = points[1]
x3, y3 = points[2]

# Prepare to receive the ratio values
m = ctypes.c_int()
n = ctypes.c_int()

# Call the C function to calculate the ratio
ratio_lib.calculateRatio(ctypes.c_float(x1), ctypes.c_float(y1), ctypes.c_float(x2), ctypes.c_float(y2), ctypes.c_float(x3), ctypes.c_float(y3), ctypes.byref(m), ctypes.byref(n))

# Unpack coordinates for plotting
x_coords, y_coords = zip(*points)

# Plot the points
plt.scatter(x_coords, y_coords, label="Points")

# Connect points to form the lines
plt.plot([points[0][0], points[1][0]], [points[0][1], points[1][1]], label="AB")
plt.plot([points[1][0], points[2][0]], [points[1][1], points[2][1]], label="BC")

# Add labels to points
labels = ['A (-6, 10)', 'B (-4, 6)', 'C (3, -8)']
for i, (x, y) in enumerate(points):
    plt.text(x + 0.1, y + 0.1, labels[i])

# Display the calculated ratio on the plot in the bottom-left corner
plt.text(0.05, 0.05, f'Ratio AB:BC = {m.value}:{n.value}', transform=plt.gca().transAxes, fontsize=12, bbox=dict(facecolor='white', alpha=0.7), verticalalignment='bottom', horizontalalignment='left')

# Set labels and title
plt.xlabel('X-axis')
plt.ylabel('Y-axis')

# Add legend
plt.legend()

# Show the plot
plt.grid(True)
plt.savefig("fig1.png")


