FROM tidair/smurf-processor-base:R1.0.0

WORKDIR /usr/local/src
RUN git clone https://github.com/jesusvasquez333/smurf-processor-example.git
WORKDIR smurf-processor-example
RUN mkdir build
WORKDIR build
RUN cmake .. && make
WORKDIR ..
ENV PYTHONPATH /usr/local/src/smurf-processor-example/lib:${PYTHONPATH}
ENV PATH /usr/local/src/smurf-processor-example/scripts/control-server:${PATH}