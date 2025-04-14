# Open Binaural Renderer (obr)
The `obr` binaural rendering library is designed to render immersive audio content.

## Features
The library is written using C++ and it utilizes [Bazel](https://bazel.build/) build system. A CMake configuration is also provided.

The library renders the following types of Audio Elements:

* Ambisonics (from 1st to 7th order).
* Channel-based (e.g. 5.1, 7.1.4). See [Loudspeaker Layouts](docs/loudspeaker_layouts.md) for the full list of supported loudspeaker layouts.
* Object-based. The API allows for controlling the position of the object in the 3D space. Currently only single channel, point-source objects are supported.

### Encoding to Ambisonics
* Handling of channel and object-based audio elements is done by encoding the required input channels into an intermediate Ambisonic bed and subsequently rendering the bed using a set of FIR filters matching its Ambisonic order.
* The calculation of spherical harmonic (SH) coefficients used during the encoding process is based on the [Resonance Audio](https://github.com/resonance-audio/resonance-audio/)'s [AssociatedLegendrePolynomialsGenerator](https://github.com/resonance-audio/resonance-audio/blob/master/resonance_audio/ambisonics/associated_legendre_polynomials_generator.h) class.

### Ambisonics to Binaural
* The binaural renderer is based on the principle of using Head Related Transfer Functions (HRTFs) and Binaural Room Impulse Responses (BRIRs) decomposed using SH coefficients.
* The FIR filters were designed as a combination of anechoic and reverberant filters.
* The FIR filtering (convolution) mechanism employed in this library is based on the [Resonance Audio](https://github.com/resonance-audio/resonance-audio/)'s [AmbisonicBinauralDecoder](https://github.com/resonance-audio/resonance-audio/blob/master/resonance_audio/ambisonics/ambisonic_binaural_decoder.h) class and its dependencies.
* The library uses asymmetric binaural processing, this means it employs dedicated filters for left and right ears.
* Binaural filter matrices are loaded from embedded assets.
* The rendering filters are selected depending on the Ambisonic order matching the input Audio Element, e.g. 7.1.4 rendering uses the highest available order of filters (7OA).
* The default length of the binaural filters is 8192 samples per SH channel @ 48 kHz sampling rate.

## Usage
### C++ API
The `ObrImpl` class is the main interface for the binaural renderer. It provides methods to configure audio elements, process audio buffers, and retrieve information about the renderer. See [obr_cli.cc](src/cli/obr_cli.cc) for an example of how to use the library. Listed below are the main methods required to configure the renderer and process audio data.

#### Constructor

In order to instantiate the renderer, the `ObrImpl` constructor needs to be called. It takes the following arguments:

* `buffer_size_per_channel`: The size of the audio processing buffer for each audio channel.
* `sampling_rate`: The sampling rate of the audio data.

```cpp
ObrImpl(int buffer_size_per_channel, int sampling_rate);
```

#### Configuration

In order to render immersive audio using `obr`, the renderer needs to be configured using the `AddAudioElement` method. The method accepts `AudioElementType` enums defined within the [audio_element_type.h](src/renderer/audio_element_type.h) file.

```cpp
 absl::Status AddAudioElement(AudioElementType type);
```

#### Audio processing callback

Once the renderer is configured, the rendering of audio data can be done using the `Process` method. The method uses [`AudioBuffer`](src/audio_buffer/audio_buffer.h) class for storing input and output audio data.

```cpp
  void Process(const AudioBuffer& input_buffer, AudioBuffer* output_buffer);
```

### Command Line Interface (CLI)
The command line interface provides a straightforward way to render audio files of certain types. The CLI is built as a standalone executable and can be run as follows:

```
 obr_cli
   --input_type=<type> (3OA, 7OA, 7.1.4, OBA)
   --oba_metadata_file=<full path to textproto file> (required for OBA)
   --input_file=<full path to wav file>
   --output_file=<full path to wav file>
   --buffer_size=<number of samples> (optional, default is 256)
```

## Testing
The library is tested using Google Test framework. The tests are located in `test` subdirectories.
