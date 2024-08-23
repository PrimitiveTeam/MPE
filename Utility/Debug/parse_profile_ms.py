import json
from collections import defaultdict
import os

def calculate_avg_duration(filename):
    with open(filename, 'r') as file:
        data = json.load(file)
    
    trace_events = data.get("traceEvents", [])
    
    name_durations = defaultdict(lambda: {'total_dur': 0, 'count': 0})
    
    for entry in trace_events:
        name = entry['name']
        duration = entry['dur']
        name_durations[name]['total_dur'] += duration
        name_durations[name]['count'] += 1
    
    avg_durations = {name: values['total_dur'] / values['count'] 
                     for name, values in name_durations.items()}
    
    return avg_durations

if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.abspath(__file__))
    
    relative_path = '../../Build/Debug/app_loop.json'
    
    filename = os.path.join(script_dir, relative_path)
    
    avg_durations = calculate_avg_duration(filename)
    
    for name, avg_duration in avg_durations.items():
        print(f"Average 'dur' value for '{name}': {avg_duration} ms")
