import matplotlib.pyplot as plt
import csv
import numpy as np

def plot_complexity(csv_file):
    n = []
    duration = []

    # Читання даних з CSV
    with open(csv_file, 'r') as f:
        reader = csv.reader(f)
        next(reader)  # Пропускаємо заголовок
        for row in reader:
            n.append(float(row[0]))
            duration.append(float(row[1]))

    n_arr = np.array(n)

    # Розрахунок теоретичної кривої O(n log n)
    # log2(n) використовується для кращої відповідності алгоритмам сортування
    ref_curve = n_arr * np.log2(n_arr)

    # Масштабування кривої, щоб вона була співставна з вашим часом
    # Ми множимо на середнє відношення, щоб "притиснути" її до даних
    scale_factor = np.mean(duration) / np.mean(ref_curve)
    scaled_ref = ref_curve * scale_factor

    # Побудова графіка
    plt.figure(figsize=(12, 7))
    plt.plot(n_arr, duration, marker='o', label='Actual Time', color='blue')
    plt.plot(n_arr, scaled_ref, linestyle='--', label='O(n log n) Reference', color='red')

    plt.xlabel('Size (n)')
    plt.ylabel('Duration (ms)')
    plt.title('Push_swap Complexity Analysis')
    plt.legend()
    plt.grid(True, which='both', linestyle='--')

    plt.savefig('time_complexity_graph.png')
    print("Графік збережено як time_complexity_graph.png")

if __name__ == "__main__":
    plot_complexity('results.csv')
