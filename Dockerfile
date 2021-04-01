# C/C++ environment
FROM gcc:4.9

# Update/Install
RUN apt-get -y update && apt-get install -y
# Install compilation tools
RUN apt-get -y install execstack


# These commands copy your files into the specified directory in the image
# and set that as the working location
# COPY ./machine-code/ /usr/src/machine-code
# WORKDIR /usr/src/machine-code
WORKDIR /app

ARG name=app

# This command compiles your app using GCC, adjust for your source code
# RUN make
# RUN g++ *.cpp -o ${name}.exe
# RUN execstack -s ${name}.exe

# This command runs your application, comment out this line to compile only
CMD ["/bin/bash"]
# CMD ["./app.exe"]

LABEL Name=simplecompiler Version=0.0.1
