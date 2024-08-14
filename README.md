# RNN-audio-analysis
RNN-LSTM model architecture for processing raw audio

  In this project we are introducing the usage of audio identification. Using the embedded system’s
capabilities from a model fixtured around audio datasets, we will build a simple RNN system to best
deploy onto a quantized model on an Arduino Nano33 BLE Sense board. Initially, the application of a
dense neural network model for the real sensor readings & keyword identification in conversation. As
part of this, we needed to look at sequential data for developing our understanding of RNN deployment.
The project aims to develop an RNN-LSTM model for audio analysis. Its primary goal is to
accurately identify specific keywords in audio data, aiding in real-time detection of keywords associated
with mental health conditions like depression and anxiety.

  For data collection, we gathered audio samples containing five specific keywords ("never",
"none", "all", "must", and "only"). The dataset comprises approximately 925 recording, with at least 50
recordings for each keyword class, as per the requirements. This code performs an additional split to
create a test dataset. After training the model and collecting the training history (history), it evaluates the
model's performance on the test dataset using model evaluation. The test accuracy and loss are then
plotted along with the training and validation metrics in results.
RNNs are tailored for sequential data processing, making them a pivotal choice for tasks like
speech recognition, music analysis, and environmental sound classification.
Their inherent capability to retain information from past inputs aids in understanding the
temporal dynamics within audio sequences. Despite their effectiveness, traditional RNNs often struggle
with long-term dependencies due to the vanishing gradient problem, where information gets diluted over
time. This limitation led to the advent of LSTM units.
LSTMs, a specialized variant of RNNs, integrates temporary memory capable of retaining
information. These cells possess gates that regulate the flow of information: the input gate decides what
new information to store, the forget gate determines what to discard from memory, and the output gate
decides what to pass to the next layer. This architecture enables LSTMs to capture nuanced temporal
patterns and prolonged dependencies within audio sequences, a critical aspect in discerning complex
sounds.
