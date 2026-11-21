from __future__ import annotations

# learn how to make neural networks starting from one with mnist db




## For easy understanding no freaky like vectors/matrices for now

import pyarrow.parquet as pq
import pandas, io
from typing import List
from PIL import Image
from random import Random
import math
import matplotlib.pyplot as plt



random = Random()

# some constant
LEARNING_RATE = 0.1
class Neuron:

  

  def __init__(self, current_layer: Layer):
    self.bias = 0.0

    self.connections: dict[Neuron, float] = {}
  
    self.a: float = 0
    self.z: float = 0
  
    self.gradient: float = 0
    self.current_layer = current_layer
    
    # construct connections

    
    if self.current_layer.previous_layer:
      std = 1 / math.sqrt(len(current_layer.previous_layer.neurons))
      
      for neuron in self.current_layer.previous_layer.neurons:
        
        self.connections[neuron] = random.uniform(-std, std)
        

    
  # we define: 
  # z = w*a.... + b
  # a = sig(z)

  def forward(self): 
    self.z = self.bias

    
    for conn in self.connections:
      
      self.z += self.connections[conn] * conn.a
   
    self.a = self.sigmoid(self.z)


  # activation func
  def sigmoid(self, val):
    return 1 / (1 + math.exp(-val))


class LayerType:
  INPUT_LAYER = 0
  HIDDEN_LAYER = 1
  OUTPUT_LAYER = 2
 
class Layer:




  def __init__(self, type: LayerType, neuron_count: int, previous_layer: Layer):
    
    
    
    self.next_layer: Layer | None = None
    self.previous_layer = previous_layer
    self.type = type

    self.neurons = [Neuron(self) for x in range(neuron_count)]
    
    

  def forward(self):
    if self.type != LayerType.HIDDEN_LAYER:
      raise Exception('Cannot invoke forward pass on non hidden layer!')
    
    for neuron in self.neurons:
      neuron.forward()

  def inputData(self, data: list[float]):
    if self.type != LayerType.INPUT_LAYER:
      raise Exception('Cannot invoke inputData on non Input layer')
    
    for i, neuron in enumerate(self.neurons):
      neuron.a = data[i]
      

  def outputData(self):
    if self.type != LayerType.OUTPUT_LAYER:
      raise Exception('Cannot invoke outputData on non Output layer')
    
    for neuron in self.neurons:
      neuron.forward()

    return [x.a for x in self.neurons]
  
class DataSample:

  def __init__(self, image, label):
    self.image = image
    self.label = label

def calculate_cost(output: list[float], desired_output: list[float]):
  if (len(output) != len(desired_output)):
    raise Exception('Unmatched output and desired output formats')

  return sum([pow((output[i] - desired_output[i]), 2) for i in range(len(output))])

def calc_last_layer_neuron_gradient(neuron: Neuron, y: float):
  A = neuron.a
  return A * (1-A) * 2 * (A - y)


def calc_hidden_layer_neuron_gradient(neuron: Neuron):
  A = neuron.a
  nextLayer = neuron.current_layer.next_layer

  if not nextLayer:
    print('Called calc_hidden_layer_neuron_gradient on non hidden layer neuron (No next layer)')
    exit()

  # NOTE - optimization
  # Super inefficient correct connection lookup

  return A * (1-A) * sum([n.connections[neuron] * n.gradient for n in nextLayer.neurons])


def calc_weight_gradient(fromNeuron: Neuron, toNeuron: Neuron):
  return fromNeuron.a * toNeuron.gradient

def calc_bias_gradient(neuron: Neuron):
  return 1 * neuron.gradient
# Load training data

print('Loading training data...')
trainDataFrame: pandas.DataFrame = pq.read_table('train.parquet').to_pandas()
trainData: list[DataSample] = []

print('Parsing training data...')
for i in range(len(trainDataFrame)):
  trainData.append(DataSample(Image.open(io.BytesIO(trainDataFrame.iloc[i]['image']['bytes'])), trainDataFrame.iloc[i]['label']))

print('Loading testing data...')
testDataFrame: pandas.DataFrame = pq.read_table('test.parquet').to_pandas()
testData: list[DataSample] = []

print('Parsing testing data...')
for i in range(len(testDataFrame)):
  testData.append(DataSample(Image.open(io.BytesIO(testDataFrame.iloc[i]['image']['bytes'])), testDataFrame.iloc[i]['label']))

print('Finished parsing.')



# create network
inputNeuronCount = 28*28 # 28x28 image
hiddenNeuronCount = 12 # just bc
outputNeuronCount =  10 # 0-9

inputLayer = Layer(LayerType.INPUT_LAYER, inputNeuronCount, None)

hiddenLayers: list[Layer] = []
for x in range(2):
  hiddenLayers.append(Layer(LayerType.HIDDEN_LAYER, hiddenNeuronCount, hiddenLayers[-1] if len(hiddenLayers) > 0 else inputLayer))

outputLayer = Layer(LayerType.OUTPUT_LAYER, outputNeuronCount, hiddenLayers[-1])

layers = [inputLayer, *hiddenLayers, outputLayer]
for i, layer in enumerate(layers):
  layer.next_layer = layers[i+1] if i<len(layers) - 1 else None


def runNetwork(sample: DataSample):
  #normalize
  inputData = [x/255 for x in list(sample.image.getdata())]
  # simple data making
  desiredOutput = [0,0,0,0,0,0,0,0,0,0]
  desiredOutput[sample.label] = 1

  # print('Starting forward pass...')
  # input data to network
  inputLayer.inputData(inputData)
  

  # pass network forward
  for hiddenLayer in hiddenLayers:
    hiddenLayer.forward()
    

  # get output data
  output = outputLayer.outputData()
  return output, desiredOutput, calculate_cost(output, desiredOutput)

# Train

print('Training the network...')
graphData = []
costSum = 0
for i,sample in enumerate(trainData):
  # print(f'Starting training on sample: {i}')
  
  output, desiredOutput, cost = runNetwork(sample)
  

  # learn
  # print('Starting backpropagation...')
  costSum += cost
  if i%100 == 0:
    avgCostForLast100 = costSum/100
    graphData.append((avgCostForLast100, i))
    print(f'Avg Cost for last 100 samples: {avgCostForLast100} after: {i} samples')
    costSum = 0

  ## We have cost/loss so now we only need to compute gradients for each weight and bias with respect to the cost: dCost / (dW or dB)

  ## Just in case check lengths
  if len(layers[-1].neurons) != len(desiredOutput):
    print('Desired output length does not match the size of the last layer')
    exit()

  # Calculate gradients for each weight and bias
  ## Format of: Neuron1 to Neuron2 => float
  weightGradients: dict[(Neuron, Neuron), float] = {}
  ## Format of: Neuron
  biasGradients: dict[Neuron] = {}
  ## Intentionaly skip input layer because there is nothing to compute
  
  for lInd in range(len(layers) -1, 0, -1):
    for j,neuron in enumerate(layers[lInd].neurons):
      # calc neuron gradient
      if lInd == len(layers) - 1: # last layer
        neuron.gradient = calc_last_layer_neuron_gradient(neuron, desiredOutput[j])
      else: # hidden layer
        neuron.gradient = calc_hidden_layer_neuron_gradient(neuron)

      # calc bias gradient
      biasGradients[neuron] = calc_bias_gradient(neuron)

      # calc weights gradient
      for connKey in neuron.connections:
        weightGradients[(connKey, neuron)] = calc_weight_gradient(connKey, neuron)

  
  # APPLY LEARNING
  # print('Applying gradients...')

  # apply weight gradients
  ## minus because gradient refers to how function will increase and we want to decrease the cost so -

  for weightGradientKey in weightGradients: 
    
    weightGradientKey[1].connections[weightGradientKey[0]] -= weightGradients[weightGradientKey] * LEARNING_RATE
  
  # apply bias gradients
  for biasGradientKey in biasGradients:
    
    biasGradientKey.bias -= biasGradients[biasGradientKey] * LEARNING_RATE

  # print(f'Sample {i} done')
  

# finished training so dump the network into a file


x = [j[1] for j in graphData]
y = [j[0] for j in graphData]

fig, ax = plt.subplots()
ax.plot(x, y)
plt.show()
  
  
# print('Testing the network...')
# accuracy = 100
# print([x.label for x in testData[2000:2010]])
# for i,sample in enumerate(testData[:10]):
#   output, desiredOutput, cost = runNetwork(sample)
#   print(cost)













