### Prerequisites
- g++ compiler
- SDL2
- SDL2_image

### Run instructions
Open terminal and navigate to game folder.

Run the following commands:

```
make
```


```
make run
```

This should open another window consisting of the game's menuscreen
### Remove compiled game files
If for any reason you would like to removed the compiled game files: 

```
make clean
```

In the game directory, will remove the game's compiled (.o) files.
### Error handling 
#### ./game: No such file or directory
Check that the game compiled successfully, by typing
```make``` once more. 


#### SDL functions not found
Check that you have a proper installation of SDL2 installed.

For further information regarding installation of SDL2, click <a href="https://www.libsdl.org/download-2.0.php"> here</a>.

#### IMG_LOAD function not found
Check that you have a proper installation of SDL2_image installed.

For further information regarding installation of SDL2_image, click <a href="https://www.libsdl.org/projects/SDL_image/"> here</a>.
