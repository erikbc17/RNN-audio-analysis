#include <Arduino_APDS9960.h>
#include "model_data.h"  // Include your model data file
#include "tensorflow/lite/micro/micro_error_reporter.h" // inference removal of errors
#include "tensorflow/lite/micro/micro_interpreter.h" // inference removal of errors
#include "tensorflow/lite/schema/schema_generated.h" //inference removal of errors
#include "tensorflow/lite/version.h" // reasing version in h model

// Define input and output shapes
constexpr int kInputTensorSize = 1 * 32 * 13;  // Input shape [1 32 13] (FROM JUPYTER FILE)
constexpr int kOutputTensorSize = 1 * 5;       // Output shape [1 5]

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Initialize TensorFlow Lite interpreter
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  model = tflite::GetModel(model_data);  // Load model data from model_data file
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    error_reporter->Report("Model schema mismatch!");
    return;
  }

  // Create an interpreter instance
  static tflite::MicroMutableOpResolver<4> resolver;
  // Add built-in operators to the resolver - adjust as needed

  static constexpr int kTensorArenaSize = 10 * 1024;
  static uint8_t tensor_arena[kTensorArenaSize];

  interpreter = new tflite::MicroInterpreter(model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
  interpreter->AllocateTensors();

  // Assign input and output tensors
  input = interpreter->input(0);
  output = interpreter->output(0);

  // Validate input and output sizes
  if (input->dims->data[0] != kInputTensorSize || output->dims->data[0] != kOutputTensorSize) {
    error_reporter->Report("Input/output tensor size mismatch!");
    return;
  }

  // Initialize sensor - for example, if using APDS9960
  if (!APDS9960.begin()) {
    error_reporter->Report("Error initializing sensor!");
    return;
  }
}

void loop() {
  // Placeholder for audio sensor readings
  float audio_data[kInputTensorSize];  // Adjust the array size as needed

  // Read audio samples from the microphone
  if (APDS9960.readProximity() > 50) {  // Adjust threshold as needed
    // If proximity detected (microphone near), collect audio samples
    for (int i = 0; i < kInputTensorSize; i++) {
      audio_data[i] = APDS9960.readMicrophone();
    }

    // Fill the input tensor with audio sensor data
    for (int i = 0; i < kInputTensorSize; ++i) {
      input->data.f[i] = audio_data[i];
    }

    // Perform inferences RTS
    interpreter->Invoke();

    
    }

    // Determine the detected keyword based on output data
    int detected_keyword = -1;
    float max_probability = -1.0f;
    for (int i = 0; i < kOutputTensorSize; ++i) {
      if (output_data[i] > max_probability) {
        detected_keyword = i;
        max_probability = output_data[i];
      }
    }

    // Print detected keyword on serial monitor when they are detected
    switch (detected_keyword) {
      case 0:
        Serial.println("Detected keyword: 'never'");
        break;
      case 1:
        Serial.println("Detected keyword: 'none'");
        break;
      case 2:
        Serial.println("Detected keyword: 'all'");
        break;
      case 3:
        Serial.println("Detected keyword: 'must'");
        break;
      case 4:
        Serial.println("Detected keyword: 'only'");
        break;
      default:
        Serial.println("No keyword detected");
        break;
    }

    delay(5000); // 5 second Delay for next inference
  }
}
