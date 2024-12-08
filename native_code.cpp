struct Layer {
        std::vector<float> weights;
        std::vector<float> biases;
        std::string type;
        std::vector<int> shape;
    };
    std::vector<Layer> layers;
    
    std::vector<float> conv2d(const std::vector<float>& input, const Layer& layer, 
                             const std::vector<int>& input_shape) {
        int height = input_shape[0];
        int width = input_shape[1];
        int channels = input_shape[2];
        int kernel_size = 3;  // Fixed as per your model
        int filters = layer.shape[0];
        
        std::vector<float> output((height) * (width) * filters);
        // Implement convolution operation
        // This is a simplified version - you'll need to implement the full conv2d
        return output;
    }
    
    std::vector<float> maxpool2d(const std::vector<float>& input, 
                                const std::vector<int>& input_shape) {
        int height = input_shape[0];
        int width = input_shape[1];
        int channels = input_shape[2];
        int pool_size = 2;  // Fixed as per your model
        
        int new_height = height / pool_size;
        int new_width = width / pool_size;
        
        std::vector<float> output(new_height * new_width * channels);
        // Implement max pooling
        return output;
    }
    
    std::vector<float> relu(const std::vector<float>& input) {
        std::vector<float> output(input.size());
        for(size_t i = 0; i < input.size(); i++) {
            output[i] = std::max(0.0f, input[i]);
        }
        return output;
    }
    
    std::vector<float> softmax(const std::vector<float>& input) {
        std::vector<float> output(input.size());
        float sum = 0;
        float max_val = *std::max_element(input.begin(), input.end());
        
        for(size_t i = 0; i < input.size(); i++) {
            output[i] = std::exp(input[i] - max_val);
            sum += output[i];
        }
        
        for(size_t i = 0; i < output.size(); i++) {
            output[i] /= sum;
        }
        return output;
    }
    
    std::vector<float> dense(const std::vector<float>& input, const Layer& layer) {
        std::vector<float> output(layer.shape[0]);
        // Implement dense layer operation
        return output;}

void loadWeights(const std::string& h5_path) {
        H5::H5File file(h5_path, H5F_ACC_RDONLY);
    }
    
    std::vector<float> predict(const std::vector<float>& input) {
        std::vector<float> current_output = input;
        std::vector<int> current_shape = {150, 150, 3};  // Initial shape
        
        for(const auto& layer : layers) {
            if(layer.type == "conv2d") {
                current_output = conv2d(current_output, layer, current_shape);
                current_output = relu(current_output);
            }
            else if(layer.type == "maxpool2d") {
                current_output = maxpool2d(current_output, current_shape);
                // Update shape after pooling
                current_shape[0] /= 2;
                current_shape[1] /= 2;
            }
            else if(layer.type == "dense") {
                current_output = dense(current_output, layer);
                current_output = relu(current_output);
            }
        } 
        return softmax(current_output);}


