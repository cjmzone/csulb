def quicksort(arr):
    if len(arr) <= 1:
        return arr
    pivot = arr[len(arr) // 2]
    left = [x for x in arr if x < pivot]
    middle = [x for x in arr if x == pivot]
    right = [x for x in arr if x > pivot]
    return quicksort(left) + middle + quicksort(right)

def find_value_at_index_from_file(filename):
    with open(filename, 'r') as file:
        content = file.read().strip()
    
    content = content[1:-1].replace('{', '').replace('}', '').split(',')
    index = int(content[0].strip())
    array = list(map(int, content[1:]))
    sorted_array = quicksort(array)
    return sorted_array[index-1]

filename = input("Enter the filename: ")
result = find_value_at_index_from_file(filename)
print(result) 