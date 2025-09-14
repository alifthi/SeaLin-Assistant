# SeaLin-Assistant

A C-based Linux terminal assistant powered by local AI models that can execute shell commands and search the web to help users with their Linux system tasks.

## Overview

SeaLin-Assistant is an intelligent command-line tool that integrates AI capabilities directly into your Linux terminal. It uses the llama.cpp library to run local language models and can:

- Execute shell commands on your Linux system
- Search the web for information
- Provide intelligent responses based on command execution results
- Maintain conversation context throughout the session

## Features

- **Local AI Processing**: Uses GGUF format models (default: Qwen2.5-Coder-3B-Instruct)
- **Shell Command Execution**: Can run Linux commands and see their output
- **Web Search Integration**: Search capability for additional information
- **Interactive Chat Interface**: Conversational interface with the AI assistant
- **GPU Acceleration**: Supports GPU layers for faster inference

## Prerequisites

- Linux operating system
- GCC compiler with C99 support
- Make build system
- CUDA-compatible GPU (optional, for GPU acceleration)

## Dependencies

The project uses the following libraries (included in `vendor/`):
- **llama.cpp**: For running GGUF format language models
- **ggml**: Machine learning tensor library
- Standard C libraries: pthread, math

## Installation

### 1. Download a GGUF model under ./models

### 2. Clone the Repository
```bash
git clone https://github.com/alifthi/SeaLin-Assistant
cd SeaLin-Assistant
```

### 3. Build the Project
```bash
make
```

### 4. Install System-wide (Optional)
```bash
make install
```
This installs the binary to `/usr/local/bin/SeaLin-Assistant`

## Usage

### Running the Assistant
```bash
make run

# Or run directly
./build/SeaLin-Assistant

# If installed system-wide
SeaLin-Assistant
```

## Project Structure

```
linux-assistant-c/
├── src/                   # Source files
│   ├── main.c             # Main program entry point
│   ├── inference.c        # AI model inference logic
│   ├── states.c           # State management
│   └── utils.c            # Utility functions
├── include/               # Header files
│   ├── config.h           # Configuration constants
│   ├── inference.h        # Inference function declarations
│   ├── states.h           # State structure definitions
│   └── utils.h            # Utility function declarations
├── models/                # AI model files (GGUF format)
├── vendor/                # Third-party libraries
│   ├── include/           # Library headers
│   └── lib/               # Compiled libraries
├── build/                 # Build output directory
└── Makefile              # Build configuration
```

## Model Requirements

- **Format**: GGUF (GGML Universal Format)
- **Recommended**: Qwen2.5-Coder series for code generation
- **Size**: 3B parameters or larger recommended
- **Quantization**: Q8_0 or higher for better quality

### Performance Tuning

- Adjust `N_GPU_LAYERS` based on your GPU memory
- Modify `MAX_MESSAGE_LENGTH` for longer conversations
- Use smaller quantized models for faster inference

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request


## Acknowledgments

- Built with [llama.cpp](https://github.com/ggerganov/llama.cpp)
- Uses GGML for tensor operations
- Powered by Qwen2.5-Coder language model
