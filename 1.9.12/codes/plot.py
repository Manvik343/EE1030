import sys
sys.path.insert(0, '/home/manvik/matgeo/codes/CoordGeo')  # path to my scripts
import numpy as np
import matplotlib.pyplot as plt
import ctypes

# Load the shared library
geometry = ctypes.CDLL('./geometry.so')

# Define argument and return types for C functions
geometry.distance.restype = ctypes.c_double
geometry.distance.argtypes = [ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double]
geometry.midpoint.argtypes = [ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.c_double, ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_double)]

# Calculate distance and midpoint using C functions
def calculate(A, B):
    dist = geometry.distance(A[0], A[1], B[0], B[1])
    mx, my = ctypes.c_double(), ctypes.c_double()
    geometry.midpoint(A[0], A[1], B[0], B[1], ctypes.byref(mx), ctypes.byref(my))
    return dist, (mx.value, my.value)

# Generate the plot
def plot(A, B, distance, midpoint):
    plt.figure(figsize=(6, 6))
    
    # Prepare coordinates for plotting
    x_coords = [A[0], B[0], midpoint[0]]  # x-coordinates for A, B, and midpoint
    y_coords = [A[1], B[1], midpoint[1]]  # y-coordinates for A, B, and midpoint

    # Plot points A, B, and midpoint M
    plt.scatter(x_coords, y_coords, color=['red', 'blue', 'green'], label="Points")
    
    # Connect points A and B with a line
    plt.plot([A[0], B[0]], [A[1], B[1]], label="AB", color='black')

    # Labels for the points
    labels = [f'A {A}', f'B {B}', f'M {midpoint}']
    
    # Add labels to points A, B, and M
    for i, (x, y) in enumerate(zip(x_coords, y_coords)):
        plt.text(x + 0.1, y + 0.1, labels[i], fontsize=9)

    # Display the calculated distance on the plot (now in the bottom-left corner)
    plt.text(0.05, 0.05, f'Distance AB: {distance:.2f}', transform=plt.gca().transAxes, fontsize=12,
             bbox=dict(facecolor='white', alpha=0.7), verticalalignment='bottom', horizontalalignment='left')

    # Set axis labels and title
    plt.title('Segment AB and its Midpoint')
    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')
    plt.legend()
    plt.grid(True)
    plt.axis('equal')
    
    plt.savefig('/home/manvik/Documents/EE1030/1.9.12/figs/plot.png')

def main():
    A, B = np.array([-6, 7]), np.array([-1, -5])
    distance, midpoint = calculate(A, B)
    
    # Optional: Save results to a file (if needed)
    with open('results.txt', 'w') as file:
        file.write(f"{A[0]}, {A[1]}, {B[0]}, {B[1]}, {distance}, {midpoint[0]}, {midpoint[1]}\n")

    plot(A, B, distance, midpoint)

if __name__ == "__main__":
    main()

