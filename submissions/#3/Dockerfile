# Using a base image that has GCC compiler installed
FROM gcc:latest

# Set the working directory within the docker image
WORKDIR /app

# Copy the C++ file into the working directory
COPY . .

# Compile the C++ program
RUN g++ -o demo demo.cpp LargeFloat.cpp LargeFloatImplementation.cpp LargeInt.cpp LargeIntImplementation.cpp LargeMath.cpp utils.cpp -Wextra -Wall

# Command to run the executable
CMD ["./demo"]
