import os
import matplotlib.pyplot as plt

def extract_stats_to_dict(file_path):
    """
    Extracts relevant information from a stats.txt file into a dictionary.

    Parameters:
        file_path (str): Path to the stats.txt file.

    Returns:
        dict: A dictionary where the first word of each line is the key, and
              the second word is the value (if it's a number).
    """
    stats_dict = {}
    try:
        with open(file_path, 'r') as file:
            # Ignore the first line
            # next(file)

            # Process the rest of the lines
            for line in file:
                words = line.split()
                if len(words) >= 2:  # Ensure there are at least two words
                    key = words[0]
                    value = words[1]
                    # Check if the value is a number
                    if value.replace('.', '', 1).isdigit():
                        stats_dict[key] = float(value) if '.' in value else int(value)
    except FileNotFoundError:
        print(f"Error: File '{file_path}' not found.")
    except Exception as e:
        print(f"Error: {e}")

    return stats_dict

def collect_data_from_configs(configuration, folder, stat_files):
    """
    Collects performance data from configuration folders.

    Parameters:
        configurations (list): List of configuration folder names.
        stat_files (list): List of stats file names to process.

    Returns:
        dict: A nested dictionary where each key is a parameter, and the value is a dictionary
              with benchmark names as keys and their performance data as lists.
    """
    collected_data = {}

    configurations = os.listdir(os.path.join(folder, configuration))

    for config in configurations:
        
        for stat_file in stat_files:
            stat_path = os.path.join(folder, configuration, config, stat_file)
            stats = extract_stats_to_dict(stat_path)

            for key, value in stats.items():
                if key not in collected_data:
                    collected_data[key] = {}
                if stat_file not in collected_data[key]:
                    collected_data[key][stat_file] = []

                collected_data[key][stat_file].append(value)

    return collected_data

def plot_performance_graph(data, configurations, title="Comparação de ", xlabel="Configs", ylabel="Performance", save_path=None):
    """
    Plots a line graph to compare performance across different configurations for various benchmarks.

    Parameters:
        data (dict): A dictionary where keys are benchmark names (str), and values are lists of performance values corresponding to configurations.
        configurations (list): A list of configuration names (str) for the x-axis.
        title (str): The title of the graph.
        xlabel (str): Label for the X-axis.
        ylabel (str): Label for the Y-axis.
        save_path (str): File path to save the graph image. If None, the graph is not saved.
    """
    for benchmark, performance in data.items():
        plt.plot(configurations, performance, label=benchmark)

    # Adding graph details
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.legend()
    plt.grid(True)

    if save_path:
        plt.savefig(save_path, format='png', dpi=300)
        print(f"Graph saved to {save_path}")

    # Show the plot
    #plt.show()
    plt.close()
    

# Example usage



stats_folder = "Stats"
configuration = "PipelineWidht" + "-stats"
stat_files = ["graphstats.txt", "matricesstats.txt", "quicksortstats.txt"]

# Collect data
data = collect_data_from_configs(configuration, stats_folder, stat_files)



configurations = os.listdir(os.path.join(stats_folder, configuration))

# Plot for each parameter
for parameter, benchmarks in data.items():
    plot_performance_graph(
        data=benchmarks,
        configurations=configurations,
        title=f"Performance Comparison for {parameter}",
        xlabel="Configurations",
        ylabel="Performance",
        save_path=f"Graphs/{parameter.replace(':','-')}_performance_comparison.png"
    )
