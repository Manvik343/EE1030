import ctypes
import matplotlib.pyplot as plt

# Load the shared library
lib = ctypes.CDLL('./distance_midpoint.so')

# Define argument and return types for the C functions
lib.distance.argtypes = [ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double]
lib.distance.restype = ctypes.c_double

lib.midpoint.argtypes = [ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double, 
                         ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double)]
lib.midpoint.restype = None

# Coordinates of points A and B
x1, y1 = -6, 7  # Point A
x2, y2 = -1, -5  # Point B

# Prepare variables to hold the midpoint values
mx = ctypes.c_double()
my = ctypes.c_double()

# Call the C function to calculate the midpoint
lib.midpoint(ctypes.c_double(x1), ctypes.c_double(y1), ctypes.c_double(x2), ctypes.c_double(y2), 
             ctypes.byref(mx), ctypes.byref(my))

# Retrieve the midpoint from the C function
M = (mx.value, my.value)
print(f"Midpoint calculated by C: {M}")  # Debugging print statement

# Call the C function to calculate the distance between A and B
distance_AB = lib.distance(ctypes.c_double(x1), ctypes.c_double(y1), ctypes.c_double(x2), ctypes.c_double(y2))
print(f"Distance AB calculated by C: {distance_AB:.2f}")

# Plot points A, B, and midpoint M
x_coords = [x1, x2, M[0]]  # x1, x2 for A and B, M[0] for midpoint
y_coords = [y1, y2, M[1]]  # y1, y2 for A and B, M[1] for midpoint

# Labels for the points
labels = ['A (-6, 7)', 'B (-1, -5)', f'M {M}']

# Plot points
plt.scatter(x_coords, y_coords, color=['red', 'blue', 'green'], label="Points")

# Connect points A and B with a line
plt.plot([x1, x2], [y1, y2], label="AB", color='black')

# Add labels to points A, B, and M
for i, (x, y) in enumerate(zip(x_coords, y_coords)):
    plt.text(x + 0.1, y + 0.1, labels[i], fontsize=9)

# Display the calculated distance on the plot
plt.text(0.05, 0.05, f'Distance AB: {distance_AB:.2f}', transform=plt.gca().transAxes, fontsize=12,
         bbox=dict(facecolor='white', alpha=0.7), verticalalignment='bottom', horizontalalignment='left')

# Set axis labels and title
plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.legend()
plt.grid(True)

# Save and display the plot
plt.savefig("fig1.png")
plt.show()

