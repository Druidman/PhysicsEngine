# PhysicsSim
Name suggests that this is just another physics engine and it is partially right.
Why partially? 
Well... this isn't just a game engine with physics simulation the main purpose of this project is to make
a ai character that can do a backflip.

## How is it going?
**[Full story on website](https://physics-sim-website.vercel.app/)**
### Engine
It is still in very early development(currently only spinning cube is working)
![Image not found!](https://github.com/Druidman/PhysicsEngine/raw/main/readme_images/current_engine_state.png "Current engine state")

### Neural network
Since it is my first time making NN I started with MNIST dataset and right now it looks like this.
![Image not found!](https://github.com/Druidman/PhysicsEngine/raw/main/readme_images/nn_state.png "Current neural network state")
Later this will be adapted to take character and world parameters as a input and not image pixels

# Usage


## How to run (Linux)
### Engine
#### Download latest release
- [here](https://github.com/Druidman/PhysicsEngine/releases/tag/v0.0)
- [MIGHT BE REQUIRED] download glfw if you don't have it: `sudo apt install libglfw3-dev` (on debian)
- then unzip it: `unzip <file> -d PhysicsSim`
- add permissions for run inside `PhysicsSim/` folder: `chmod +x main`
- run: `./main`
#### Compile from source
- clone repo
- install glfw as you like xD
- use this to build: `g++ main.cpp vendor/glad/glad.c shaders/*.cpp buffers/*.cpp -o main -lglfw -lGL -g`
- run: `./main`
### Neural network
Follow this steps:
1. Clone repo and enter NeuralNetwork/ directory
2. Create venv: `python3 -m venv venv`
3. Activate venv: `source venv/bin/activate`
4. Install dependencies: `pip install -r requirements.txt`
5. Run the main file: `python3 main.py`

## How to run (windows)
**Idk since I don't have a windows**

## How to run (mac)
**Idk since I don't have a mac**