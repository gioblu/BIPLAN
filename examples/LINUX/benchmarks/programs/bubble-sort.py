def bubble_sort(arr):
    n = len(arr)
    for i in range(n - 1):
        swapped = False
        for j in range(n - i - 1):
            if arr[j] > arr[j + 1]:
                t = arr[j]
                arr[j] = arr[j + 1] 
                arr[j + 1] = t
                swapped = True
        if not swapped:
            break

arr = list("Reorder this please, now.")

for i in range(100000):
    bubble_sort(arr)
