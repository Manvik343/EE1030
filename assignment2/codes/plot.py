import matplotlib.pyplot as plt

# Coordinates of the parallelogram
points = [(-6, 10), (-4, 6), (3, -8)]

# Unpack coordinates for plotting
x_coords, y_coords = zip(*points)

# Plot the points
plt.scatter(x_coords, y_coords, label="Points")

# Connect points to form the parallelogram
plt.plot([points[0][0], points[1][0]], [points[0][1], points[1][1]], label="AB")
plt.plot([points[1][0], points[2][0]], [points[1][1], points[2][1]], label="BC")

# Add labels to points
labels = ['A (-6, 10)', 'B (-4, 6)', 'C (3, -8)']
for i, (x, y) in enumerate(points):
    plt.text(x + 0.1, y + 0.1, labels[i])

# Set labels and title
plt.xlabel('X-axis')
plt.ylabel('Y-axis')

# Add legend
plt.legend()

# Show the plot
plt.grid(True)
plt.savefig("fig1.png")
