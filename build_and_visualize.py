import subprocess
import os
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
import numpy as np

def compile_cpp():
    """Компилирует C++ код"""
    print("Компиляция C++ кода...")
    cpp_files = [
        "main.cpp",
        "Sorter.cpp",
        "SortTester.cpp",
        "ArrayGenerator.cpp"
    ]
    
    compile_command = ["g++", "-std=c++17", "-O2"] + cpp_files + ["-o", "sort_test"]
    result = subprocess.run(compile_command, capture_output=True, text=True)
    
    if result.returncode != 0:
        print("Ошибка компиляции:")
        print(result.stderr)
        exit(1)
    print("Компиляция успешно завершена")

def run_tests():
    """Запускает скомпилированную программу"""
    print("Запуск тестов сортировки...")
    subprocess.run(["./sort_test"])
    print("Тесты завершены")

def read_results(filename):
    """Читает результаты из файла"""
    sizes = []
    times = []
    with open(filename, 'r') as f:
        for line in f:
            size, time = map(float, line.strip().split())
            sizes.append(size)
            times.append(time)
    return sizes, times

def create_plots():
    """Создает графики результатов"""
    print("Создание графиков...")
    
    
    plt.style.use('seaborn-v0_8')
    sns.set_palette("husl")
    
    
    array_types = ['random', 'reversed', 'nearly_sorted']
    
    
    fig, axes = plt.subplots(1, 3, figsize=(18, 6))
    fig.suptitle('Сравнение алгоритмов сортировки', fontsize=16)
    
    for idx, array_type in enumerate(array_types):
        
        standard_file = f'standard_merge_{array_type}.txt'
        hybrid_file = f'hybrid_merge_{array_type}_th10.txt'
        
        standard_sizes, standard_times = read_results(standard_file)
        hybrid_sizes, hybrid_times = read_results(hybrid_file)
        
        
        df = pd.DataFrame({
            'Размер массива': standard_sizes + hybrid_sizes,
            'Время (мс)': standard_times + hybrid_times,
            'Алгоритм': ['Стандартный Merge Sort'] * len(standard_sizes) + 
                       ['Гибридный Merge Sort'] * len(hybrid_sizes)
        })
        
        
        sns.lineplot(data=df, x='Размер массива', y='Время (мс)', 
                    hue='Алгоритм', ax=axes[idx])
        
        
        axes[idx].set_title(f'Тип массива: {array_type}')
        axes[idx].grid(True, alpha=0.3)
        
        
        axes[idx].set_xlabel('Размер массива')
        axes[idx].set_ylabel('Время (мс)')
        
        
        axes[idx].legend(title='')
    
    
    plt.tight_layout()
    
    os.makedirs('plots', exist_ok=True)
    plt.savefig('plots/sorting_comparison.png', dpi=300, bbox_inches='tight')
    print("График сохранен в файл 'sorting_comparison.png'")

def cleanup():
    """Удаляет временные файлы"""
    print("Очистка временных файлов...")
    files_to_remove = [
        'sort_test',
        'standard_merge_random.txt',
        'standard_merge_reversed.txt',
        'standard_merge_nearly_sorted.txt',
        'hybrid_merge_random_th10.txt',
        'hybrid_merge_reversed_th10.txt',
        'hybrid_merge_nearly_sorted_th10.txt'
    ]
    
    for file in files_to_remove:
        if os.path.exists(file):
            os.remove(file)

def main():
    try:
        compile_cpp()
        run_tests()
        create_plots()
        cleanup()
        print("Все операции успешно завершены!")
    except Exception as e:
        print(f"Произошла ошибка: {str(e)}")

if __name__ == "__main__":
    main()
