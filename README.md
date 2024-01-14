# how_to_dissapear_completely

Project desription:

From one side it's more like a mocumentary movie, from another side it's detective game. Gameplay based on watching videos in random order which are all part of one big story that needs to be assembled as a complexed puzzle that consits of different types of nodes, such as screenshots, notes, dates which need to be connected together by proper threads.
Besides assembling full picture out of given details, player also should make detuctive assumptions to fill missing "puzzles".

Written in C++ (17 Standard)

Dependencies:

- Visual Studio Community 2022 v17
- SFML (game engine)(download "Visual C++ 17 (2022) - 64-bit" version): https://www.sfml-dev.org/download/sfml/2.6.0/
    in order to work, instructions must be followed:
        https://www.sfml-dev.org/tutorials/2.6/start-vc.php
    
- sfeMovie (extension for SFML to play video with sound): http://sfemovie.yalir.org/latest/
    in order to work, instructions must be followed:
        http://sfemovie.yalir.org/latest/start.php
- simple-yet-powerful-srt-subtitle-parser-cpp (srt parser): https://github.com/saurabhshri/simple-yet-powerful-srt-subtitle-parser-cpp
        Nothing should be done. It already included in source code. It depends only on a header file, that was modified in order to work with wide string characters.
- json/JSON for modern c++ (json parser): https://github.com/nlohmann/json
     in order to work, instructions must be followed:
        https://github.com/nlohmann/json?tab=readme-ov-file#integration

Video files not included in this repository (later link will be created). In order to work video files must be placed in "rsc/vid" folder.
