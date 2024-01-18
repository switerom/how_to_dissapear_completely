# The script for creating 240p previews(thumbnails)
# Froma JSON data search/"search_data.json" out of videos "rsc/vid"
# To a "rsc/img/prev" folder 

import json
from moviepy.editor import VideoFileClip
import os

# Create the 'prev' directory if it doesn't exist
if not os.path.exists('../rsc/img/prev'):
    os.makedirs('../rsc/img/prev')

# Specify the path to the JSON file
file_path = "../rsc/search/search_data.json"

# Check if the file exists
if not os.path.exists(file_path):
    raise FileNotFoundError(f"The file {file_path} does not exist.")

# If the file exists, open it and load the data
with open(file_path, encoding='utf-8') as f:
    data = json.load(f)

# Iterate over each item in the data
for item in data:
    word = item['word']
    for video in item['videos']:
        # Modify the path to the 'vid' directory
        video_file = os.path.join("..", "rsc/vid", video['video'])
        # Check if the video file exists
        if os.path.exists(video_file):
            clip = VideoFileClip(video_file)
            # Resize the clip to 240p
            clip_resized = clip.resize(height=240)
            video_duration = clip.duration
            for timestamp in video['timestamps']:
                # Check if timestamp exists
                if timestamp < video_duration:
                    # Get the base name of the video file without extension
                    video_base_name = os.path.splitext(os.path.basename(video_file))[0]
                    # Save a screenshot as a .jpg file in the "prev" folder
                    output_filename = f"{video_base_name}_{int(timestamp)}.jpg"
                    output_path = os.path.join("../rsc/img/prev", output_filename)
                    clip_resized.save_frame(output_path, t=timestamp)
                else:
                    print(f"Timestamp {timestamp} for ideo file {video_file} does not exist.")    
            clip.close()  # Close the VideoFileClip object after use
        else:
            print(f"Video file {video_file} does not exist.")
