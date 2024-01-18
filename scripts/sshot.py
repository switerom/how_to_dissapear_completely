import json
from moviepy.editor import VideoFileClip
import os

# Create the 'prev' directory if it doesn't exist
if not os.path.exists('../rsc/img/prev'):
    os.makedirs('../rsc/img/prev')

# Open the JSON file and load the data
with open("../rsc/search/search_data.json") as f:
    data = json.load(f)

# Iterate over each item in the data
for item in data:
    word = item['word']
    for video in item['videos']:
        # Modify the path to the 'vid' directory
        video_file = os.path.join("..", "rsc/vid", video['video'])
        clip = VideoFileClip(video_file)
        for timestamp in video['timestamps']:
            # Get the base name of the video file without extension
            video_base_name = os.path.splitext(os.path.basename(video_file))[0]
            # Save a screenshot as a .jpg file in the "prev" folder
            output_filename = f"{video_base_name}_{int(timestamp)}.jpg"
            output_path = os.path.join("../rsc/img/prev", output_filename)
            clip.save_frame(output_path, t=timestamp)
        clip.close()  # Close the VideoFileClip object after use