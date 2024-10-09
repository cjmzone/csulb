import math
import re

# Function to calculate Euclidean distance between two points
def euclidean_distance(p1, p2):
    return math.sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)

# Brute force function to find the smallest distance between any two points
def find_closest_distance(points, start, end):
    min_distance = float('inf')
    for i in range(start, end):
        for j in range(i + 1, end + 1):
            distance = euclidean_distance(points[i], points[j])
            min_distance = min(min_distance, distance)
    return min_distance

# Recursive function to divide the set and find the smallest distance
def closest_recursive(points, start, end):
    if end - start <= 3:  # Base case: use brute force when small number of points
        return find_closest_distance(points, start, end)
    
    mid = (start + end) // 2
    left_distance = closest_recursive(points, start, mid)
    right_distance = closest_recursive(points, mid + 1, end)
    
    return min(left_distance, right_distance)

# Function to read points from file in the format: {{x1, y1}, {x2, y2}, ...}
def read_points_from_file(file_path):
    with open(file_path, 'r') as file:
        data = file.read()
    
    # Use a regular expression to extract points in the format {x, y}
    point_pattern = re.compile(r'\{([\d\.\-]+),\s*([\d\.\-]+)\}')
    points = [(float(x), float(y)) for x, y in point_pattern.findall(data)]
    
    return points

def main(file_path):
    points = read_points_from_file(file_path)
    
    if len(points) < 2:
        print("Not enough points to calculate distances.")
        return

    # Sort points by x-coordinate (optional but helps if we later extend this for divide and conquer)
    points.sort(key=lambda point: point[0])
    
    min_distance = closest_recursive(points, 0, len(points) - 1)
    
    # Print the minimum distance rounded to 3 decimal places
    print(f"Minimum distance: {min_distance:.3f}")

# Example usage:
if __name__ == "__main__":
    file_path = input("Enter file path: ")
    main(file_path)
