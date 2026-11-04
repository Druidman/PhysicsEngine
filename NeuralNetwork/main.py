from __future__ import annotations

# learn how to make neural networks starting from one with mnist db




## For easy understanding no freaky like vectors/matrices for now


from typing import List

from random import Random
import math
random = Random()

class Neuron:

  bias = random.random()
  connections: list[tuple[Neuron, float]] = []

  previous_layer: Layer
  current_layer: Layer

  z: float = 0

  def __init__(self, previous_layer: Layer, current_layer: Layer):
    self.previous_layer = previous_layer
    self.current_layer = current_layer

    # construct connections
    self.connections = [(x, random.random()) for x in self.previous_layer.neurons] if self.previous_layer else []


  # we define: 
  # a = w*a.... + b
  # z = act(a)

  def forward(self): 
    self.z = self.bias

    for conn in self.connections:
      self.z += conn[1] * conn[0].z

    self.z = self.activate(self.z)


  # apply activation func
  def activate(self, val):
    return 1 / (1 + math.exp(-val))


class LayerType:
  INPUT_LAYER = 0
  HIDDEN_LAYER = 1
  OUTPUT_LAYER = 2
 
class Layer:
  neurons: List[Neuron]
  type: LayerType
  def __init__(self, type: LayerType, neuron_count: int, previous_layer: Layer):
    self.neurons = [Neuron(previous_layer, self) for x in range(neuron_count)]
    self.type = type

  def forward(self):
    if self.type != LayerType.HIDDEN_LAYER:
      raise Exception('Cannot invoke forward pass on non hidden layer!')
    
    for neuron in self.neurons:
      neuron.forward()

  def inputData(self, data: list[float]):
    if self.type != LayerType.INPUT_LAYER:
      raise Exception('Cannot invoke inputData on non Input layer')
    
    for i, neuron in enumerate(self.neurons):
      neuron.z = data[i]

  def outputData(self):
    if self.type != LayerType.OUTPUT_LAYER:
      raise Exception('Cannot invoke outputData on non Output layer')
    
    for neuron in self.neurons:
      neuron.forward()

    return [x.z for x in self.neurons]
  



# create network
inputNeuronCount = 3
hiddenNeuronCount = 10
outputNeuronCount =  5

inputLayer = Layer(LayerType.INPUT_LAYER, inputNeuronCount, None)

hiddenLayers = []
for x in range(10):
  hiddenLayers.append(Layer(LayerType.HIDDEN_LAYER, hiddenNeuronCount, hiddenLayers[-1] if len(hiddenLayers) else None))

outputLayer = Layer(LayerType.OUTPUT_LAYER, outputNeuronCount, hiddenLayers[-1])


# input data to network

inputLayer.inputData([random.random() for x in range(inputNeuronCount)])

# pass network forward

for hiddenLayer in hiddenLayers:
  hiddenLayer.forward()

# get output data

print(outputLayer.outputData())








